#include <Arduino_BMI270_BMM150.h>

void setup() {
  Serial.begin(115200);

  if (!IMU.begin()) {
    Serial.println("IMU failed");
    while (1);
  }

  Serial.println("IMU ready");
}

void loop() {
  float ax, ay, az;

  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(ax, ay, az);

    float motion = sqrt(ax * ax + ay * ay + az * az);
    Serial.println(motion);
  }

  delay(20);
}
