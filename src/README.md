# Source code guide

This directory will contain the reviewed firmware and dashboard source for the **Embedded AI Focus Monitor**. The actual implementation files have not yet been supplied, so no placeholder code is included.

## Intended structure

```text
src/
├── FocusMonitor_Final.ino
├── Feature_Collection.ino
├── IMU_Test.ino
├── PulseSensor_Test.ino
└── dashboard.html
```

## Planned file responsibilities

| File | Intended contents |
|---|---|
| `FocusMonitor_Final.ino` | Final integrated Arduino firmware for sensor acquisition, embedded classification, and output communication. |
| `Feature_Collection.ino` | Arduino workflow used to collect or prepare the project’s sensor feature data. |
| `IMU_Test.ino` | Focused test sketch for checking accelerometer and gyroscope readings. |
| `PulseSensor_Test.ino` | Focused test sketch for checking HW-827 pulse sensor activity. |
| `dashboard.html` | Web Bluetooth monitoring interface for classifications, confidence, pulse activity, and motion readings. |

These descriptions define the intended organization only. Actual code files will be added after they are supplied and reviewed.

## File guidance

- Keep Arduino sketch names consistent with the names above.
- Keep hardware pins, sampling behavior, model inputs, and Bluetooth details faithful to the reviewed implementation.
- Do not add generated model libraries or build artifacts unless repository requirements are documented.
- Update this guide and the root README whenever the source layout changes.
