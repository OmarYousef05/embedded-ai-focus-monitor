#include <Arduino_BMI270_BMM150.h>

const int PULSE_PIN = A0;
const int WINDOW_SIZE = 200;
const int SAMPLE_DELAY_MS = 50;

void setup() {
  Serial.begin(115200);

  if (!IMU.begin()) {
    Serial.println("IMU failed");
    while (1);
  }

  delay(2000);
  Serial.println("pulse_avg,pulse_var,motion_change_avg,motion_change_max");
}

void loop() {
  int pulseMin = 1023;
  int pulseMax = 0;
  long pulseSum = 0;

  float motionSum = 0.0;
  float motionMax = 0.0;

  float lastAx = 0.0;
  float lastAy = 0.0;
  float lastAz = 0.0;

  bool hasLast = false;
  int validMotionSamples = 0;

  for (int i = 0; i < WINDOW_SIZE; i++) {
    int pulse = analogRead(PULSE_PIN);

    pulseSum += pulse;
    if (pulse < pulseMin) pulseMin = pulse;
    if (pulse > pulseMax) pulseMax = pulse;

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
  float motionChangeAvg = motionSum / (float)validMotionSamples;

  Serial.print(pulseAvg);
  Serial.print(",");
  Serial.print(pulseVar);
  Serial.print(",");
  Serial.print(motionChangeAvg, 5);
  Serial.print(",");
  Serial.println(motionMax, 5);
}
