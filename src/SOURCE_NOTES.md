# Source Code

This directory contains the Arduino firmware, sensor test programs, feature collection code, and Web Bluetooth dashboard for the Embedded Focus Monitoring System.

## Files

### FocusMonitor_Final.ino
Final embedded application for real-time focus monitoring.

Includes:
- Pulse sensor reading
- IMU motion sensing
- Feature extraction
- Embedded AI inference
- Stable focus/distracted decision logic
- BLE communication with dashboard

---

### Feature_Collection.ino
Data collection program used to generate training samples.

Outputs CSV rows containing:

```text
pulse_avg,pulse_var,motion_change_avg,motion_change_max
```

These features are used to train the focus-state classification model.

---

### IMU_Test.ino
Standalone IMU test script.

Used to verify:
- accelerometer readings
- desk motion detection
- tapping and typing activity response

---

### PulseSensor_Test.ino
Standalone pulse sensor test script.

Used to verify:
- analog pulse readings
- sensor contact quality
- signal behavior with and without finger contact

---

### dashboard.html
Web Bluetooth dashboard for live system monitoring.

Displays:
- focus classification
- confidence score
- pulse sensor values
- motion sensor values
- model run count
- raw embedded inference output

---

## Hardware Target

- Arduino Nano 33 BLE Sense Rev2
- HW-827 pulse sensor
- Built-in IMU
- Web Bluetooth dashboard

---

## Main Workflow

```text
Sensor Testing → Feature Collection → Model Training → Embedded Deployment → Live Dashboard
```
