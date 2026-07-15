# Source code

This directory contains the source files supplied for the **Embedded AI Focus Monitor**. The descriptions below reflect direct inspection of the current files; no implementation details have been invented.

## Current files

| File | Verified contents |
|---|---|
| [`IMU_Test.ino`](IMU_Test.ino) | Integrated firmware containing the Edge Impulse inferencing header, pulse and IMU feature collection, classification and decision logic, Arduino BLE service, and JSON telemetry output. Despite its filename, this is the most complete integrated sketch currently supplied. |
| [`FocusMonitor_Final.ino`](FocusMonitor_Final.ino) | Feature-window collection sketch that reads pulse activity and IMU acceleration changes, then prints `pulse_avg`, `pulse_var`, `motion_change_avg`, and `motion_change_max` as CSV. |
| [`PulseSensor_Test.ino`](PulseSensor_Test.ino) | Standalone IMU acceleration/motion-magnitude test. Despite its filename, it currently tests the IMU rather than the pulse sensor. |
| [`PulseSensor_Basic_Test.ino`](PulseSensor_Basic_Test.ino) | Basic pulse-sensor test recovered from the code previously placed in this README. It reads analog input `A0` and prints each sample over Serial. |
| [`SOURCE_NOTES.md`](SOURCE_NOTES.md) | Source overview supplied as Markdown. It was uploaded with an `.html` extension but does not contain a runnable dashboard implementation. |

## Important source note

The original uploaded filenames do not consistently match their implementations. They have been retained to avoid silently changing user-supplied firmware references. The pulse-test code previously stored in this README is now preserved as `PulseSensor_Basic_Test.ino`. A runnable Web Bluetooth dashboard source file is not currently present.

## Hardware and libraries referenced by the code

- Arduino Nano 33 BLE Sense Rev2
- HW-827 pulse sensor connected through analog input `A0`
- `Arduino_BMI270_BMM150`
- `ArduinoBLE`
- The project’s generated Edge Impulse inferencing header

## Suggested review order

1. Inspect `PulseSensor_Basic_Test.ino` for basic pulse acquisition.
2. Inspect `PulseSensor_Test.ino` for the basic IMU reading test.
3. Inspect `FocusMonitor_Final.ino` for feature-window generation and CSV output.
4. Inspect `IMU_Test.ino` for the integrated classifier and BLE telemetry path.
5. Add and review the actual dashboard HTML when it becomes available.

Do not rename sketches or change model, pin, threshold, timing, or BLE settings without validating the firmware build and deployment workflow.
