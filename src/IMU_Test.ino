#include <OmarYousef-project-1_inferencing.h>
#include <Arduino_BMI270_BMM150.h>
#include <ArduinoBLE.h>

const int PULSE_PIN = A0;

const int WINDOW_SIZE = 100;
const int SAMPLE_DELAY_MS = 25;

const float MIN_CONFIDENCE = 0.60;
const float MIN_SCORE_MARGIN = 0.15;
const int REQUIRED_STABLE_COUNT = 2;

BLEService focusService("19b10000-e8f2-537e-4f6c-d104768a1214");

BLEStringCharacteristic focusCharacteristic(
  "19b10001-e8f2-537e-4f6c-d104768a1214",
  BLERead | BLENotify,
  220
);

String stableState = "UNKNOWN";
String lastPrediction = "UNKNOWN";

int stableCount = 0;
unsigned long runCount = 0;

String normalizeLabel(String label) {
  label.toLowerCase();
  label.trim();

  if (label == "focused" || label == "focus") {
    return "FOCUSED";
  }

  if (
    label == "distracted" ||
    label == "unfocused" ||
    label == "not_focused" ||
    label == "not focused"
  ) {
    return "DISTRACTED";
  }

  return "UNKNOWN";
}

void sendToUI(
  String instantState,
  String stableState,
  float confidence,
  float focusedScore,
  float distractedScore,
  int estimatedBpm,
  float pulseAvg,
  float pulseVar,
  float motionChangeAvg,
  float motionMax,
  unsigned long runCount
) {
  String uiState;

  if (instantState == "PUT FINGER ON SENSOR" || stableState == "PUT FINGER ON SENSOR") {
    uiState = "PUT FINGER ON SENSOR";
  } else {
    uiState = stableState;
  }

  String json = "{";
  json += "\"i\":\"" + instantState + "\",";
  json += "\"s\":\"" + stableState + "\",";
  json += "\"state\":\"" + uiState + "\",";
  json += "\"c\":" + String(confidence, 3) + ",";
  json += "\"fs\":" + String(focusedScore, 3) + ",";
  json += "\"ds\":" + String(distractedScore, 3) + ",";
  json += "\"b\":" + String(estimatedBpm) + ",";
  json += "\"pa\":" + String(pulseAvg, 1) + ",";
  json += "\"pv\":" + String(pulseVar, 1) + ",";
  json += "\"ma\":" + String(motionChangeAvg, 5) + ",";
  json += "\"mx\":" + String(motionMax, 5) + ",";
  json += "\"r\":" + String(runCount);
  json += "}";

  BLE.poll();
  focusCharacteristic.writeValue(json);
  BLE.poll();
}

void setup() {
  Serial.begin(115200);
  delay(2000);

  Serial.println();
  Serial.println("====================================");
  Serial.println(" Embedded AI Focus Monitor");
  Serial.println(" Nano 33 BLE Sense Rev2 + HW-827");
  Serial.println(" Pulse + IMU + Edge Impulse");
  Serial.println("====================================");

  pinMode(PULSE_PIN, INPUT);

  if (!IMU.begin()) {
    Serial.println("ERROR: IMU failed");
    while (1);
  }

  Serial.println("IMU ready");

  if (!BLE.begin()) {
    Serial.println("ERROR: BLE failed");
    while (1);
  }

  BLE.setDeviceName("FocusMonitor");
  BLE.setLocalName("FocusMonitor");
  BLE.setAdvertisedService(focusService);

  focusService.addCharacteristic(focusCharacteristic);
  BLE.addService(focusService);

  focusCharacteristic.writeValue("{\"state\":\"STARTING\"}");
  BLE.advertise();

  Serial.println("BLE ready");
  Serial.println("Device name: FocusMonitor");
}

void loop() {
  BLE.poll();
  runCount++;

  int pulseMin = 1023;
  int pulseMax = 0;
  long pulseSum = 0;

  int peakCount = 0;
  bool wasAboveThreshold = false;

  float motionSum = 0.0;
  float motionMax = 0.0;

  float lastAx = 0.0;
  float lastAy = 0.0;
  float lastAz = 0.0;

  bool hasLast = false;
  int validMotionSamples = 0;

  Serial.println();
  Serial.println("Collecting sensor window.");

  for (int i = 0; i < WINDOW_SIZE; i++) {
    BLE.poll();

    int pulse = analogRead(PULSE_PIN);

    pulseSum += pulse;
    if (pulse < pulseMin) pulseMin = pulse;
    if (pulse > pulseMax) pulseMax = pulse;

    int dynamicThreshold = pulseMin + ((pulseMax - pulseMin) * 65 / 100);

    if (pulse > dynamicThreshold && !wasAboveThreshold && (pulseMax - pulseMin) > 20) {
      peakCount++;
      wasAboveThreshold = true;
    }

    if (pulse < dynamicThreshold) {
      wasAboveThreshold = false;
    }

    float ax, ay, az;

    if (IMU.accelerationAvailable()) {
      IMU.readAcceleration(ax, ay, az);

      if (hasLast) {
        float motionChange =
          abs(ax - lastAx) +
          abs(ay - lastAy) +
          abs(az - lastAz);

        motionSum += motionChange;

        if (motionChange > motionMax) {
          motionMax = motionChange;
        }

        validMotionSamples++;
      }

      lastAx = ax;
      lastAy = ay;
      lastAz = az;
      hasLast = true;
    }

    delay(SAMPLE_DELAY_MS);
  }

  float pulseAvg = pulseSum / (float)WINDOW_SIZE;
  float pulseVar = pulseMax - pulseMin;
  float motionChangeAvg = 0.0;

  if (validMotionSamples > 0) {
    motionChangeAvg = motionSum / (float)validMotionSamples;
  }

  float windowSeconds = (WINDOW_SIZE * SAMPLE_DELAY_MS) / 1000.0;
  int estimatedBpm = (int)((peakCount / windowSeconds) * 60.0);

  if (estimatedBpm < 40 || estimatedBpm > 180 || pulseVar < 20) {
    estimatedBpm = 0;
  }

  bool fingerNotDetected =
    pulseAvg < 480 ||
    pulseAvg > 560 ||
    pulseVar < 10 ||
    pulseVar > 250;

  if (fingerNotDetected) {
    stableState = "PUT FINGER ON SENSOR";
    lastPrediction = "PUT FINGER ON SENSOR";
    stableCount = 0;

    Serial.println("Stable State: PUT FINGER ON SENSOR");

    sendToUI(
      "PUT FINGER ON SENSOR",
      "PUT FINGER ON SENSOR",
      0.0,
      0.0,
      0.0,
      estimatedBpm,
      pulseAvg,
      pulseVar,
      motionChangeAvg,
      motionMax,
      runCount
    );

    return;
  }

  float features[] = {
    pulseAvg,
    pulseVar,
    motionChangeAvg,
    motionMax
  };

  signal_t signal;
  numpy::signal_from_buffer(features, 4, &signal);

  ei_impulse_result_t result = { 0 };
  EI_IMPULSE_ERROR res = run_classifier(&signal, &result, false);

  if (res != EI_IMPULSE_OK) {
    Serial.print("Classifier failed: ");
    Serial.println(res);
    return;
  }

  String predictedState = "UNKNOWN";
  float focusedScore = 0.0;
  float distractedScore = 0.0;
  float bestScore = 0.0;

  for (size_t ix = 0; ix < EI_CLASSIFIER_LABEL_COUNT; ix++) {
    String label = normalizeLabel(result.classification[ix].label);
    float score = result.classification[ix].value;

    if (label == "FOCUSED") {
      focusedScore = score;
    }

    if (label == "DISTRACTED") {
      distractedScore = score;
    }

    if (score > bestScore) {
      bestScore = score;
      predictedState = label;
    }
  }

  bool looksFocused =
    pulseVar >= 20 &&
    pulseVar <= 110 &&
    motionChangeAvg < 0.004;

  bool looksStronglyDistracted =
    motionChangeAvg > 0.006 ||
    motionMax > 0.020 ||
    pulseVar > 130;

  String physicalState = "UNKNOWN";

  if (looksFocused) {
    physicalState = "FOCUSED";
  }

  if (looksStronglyDistracted) {
    physicalState = "DISTRACTED";
  }

  if (bestScore < MIN_CONFIDENCE) {
    if (physicalState != "UNKNOWN") {
      predictedState = physicalState;
    } else {
      predictedState = "UNCERTAIN";
    }
  }

  if (predictedState == "FOCUSED" && looksStronglyDistracted) {
    predictedState = "DISTRACTED";
  }

  if (predictedState == "DISTRACTED" && looksFocused && bestScore < 0.75) {
    predictedState = "FOCUSED";
  }

  if (predictedState == "UNCERTAIN") {
    stableCount = 0;
  } else if (predictedState == lastPrediction) {
    stableCount++;
  } else {
    stableCount = 1;
    lastPrediction = predictedState;
  }

  if (stableCount >= REQUIRED_STABLE_COUNT && predictedState != "UNCERTAIN") {
    stableState = predictedState;
  }

  Serial.println();
  Serial.println("---- Final Decision ----");
  Serial.print("Stable State: ");
  Serial.println(stableState);
  Serial.print("Instant Prediction: ");
  Serial.println(predictedState);
  Serial.print("Confidence: ");
  Serial.println(bestScore, 3);
  Serial.print("Focused Score: ");
  Serial.println(focusedScore, 3);
  Serial.print("Distracted Score: ");
  Serial.println(distractedScore, 3);
  Serial.print("Estimated BPM: ");
  Serial.println(estimatedBpm);
  Serial.print("pulse_avg: ");
  Serial.println(pulseAvg, 1);
  Serial.print("pulse_var: ");
  Serial.println(pulseVar, 1);
  Serial.print("motion_change_avg: ");
  Serial.println(motionChangeAvg, 5);
  Serial.print("motion_change_max: ");
  Serial.println(motionMax, 5);
  Serial.print("Run: ");
  Serial.println(runCount);
  Serial.println("------------------------");

  sendToUI(
    predictedState,
    stableState,
    bestScore,
    focusedScore,
    distractedScore,
    estimatedBpm,
    pulseAvg,
    pulseVar,
    motionChangeAvg,
    motionMax,
    runCount
  );
}
