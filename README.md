<div align="center">

![Embedded AI Focus Monitor](https://capsule-render.vercel.app/api?type=waving&height=230&color=0:071426,45:0B2942,75:4F46E5,100:22D3EE&text=Embedded%20AI%20Focus%20Monitor&fontColor=E6F7FF&fontSize=42&fontAlignY=38&desc=Pulse%20%2B%20motion%20signals%20%E2%80%A2%20On-device%20TinyML%20%E2%80%A2%20Live%20Bluetooth%20monitoring&descAlignY=58&descSize=16&animation=fadeIn)

<a href="#project-snapshot"><img src="https://readme-typing-svg.demolab.com?font=JetBrains+Mono&weight=600&size=18&duration=3200&pause=900&color=22D3EE&center=true&vCenter=true&width=760&lines=Real-time+focus-state+classification;Arduino+Nano+33+BLE+Sense+Rev2;Edge+Impulse+%7C+Pulse+%2B+IMU+%7C+Web+Bluetooth" alt="Typing introduction" /></a>

[![Platform](https://img.shields.io/badge/Platform-Arduino%20Nano%2033%20BLE%20Sense%20Rev2-00979D?style=for-the-badge&logo=arduino&logoColor=white)](#hardware-platform)
[![AI](https://img.shields.io/badge/AI-Edge%20Impulse-6C5CE7?style=for-the-badge)](#edge-impulse-model-training)
[![Inference](https://img.shields.io/badge/Inference-On--Device-22D3EE?style=for-the-badge&labelColor=071426)](#performance-results)
[![Interface](https://img.shields.io/badge/Interface-Web%20Bluetooth-4F46E5?style=for-the-badge&logo=bluetooth&logoColor=white)](#live-dashboard)

### Real-time focus-state classification using pulse and motion signals on Arduino Nano 33 BLE Sense

</div>

## Project introduction

**Embedded AI Focus Monitor** is a real-time, non-wearable focus-state monitoring prototype that combines physiological and motion-based sensor data. Pulse readings and IMU motion analysis feed an embedded machine-learning model trained with Edge Impulse and deployed directly to an Arduino Nano 33 BLE Sense Rev2.

The system classifies the current state as **focused** or **distracted**, then presents the prediction, confidence, pulse activity, and motion readings through a live Web Bluetooth dashboard.

> [!NOTE]
> This is an educational embedded AI prototype. Its classifications are engineering outputs derived from limited sensor signals—not medical conclusions or perfect measurements of attention.

## Project snapshot

<table>
  <tr>
    <td width="24%"><strong>Hardware</strong></td>
    <td>Arduino Nano 33 BLE Sense Rev2 and HW-827 pulse sensor</td>
  </tr>
  <tr>
    <td><strong>Signals</strong></td>
    <td>Pulse, accelerometer, gyroscope, and desk movement</td>
  </tr>
  <tr>
    <td><strong>Model</strong></td>
    <td>Edge Impulse embedded classifier</td>
  </tr>
  <tr>
    <td><strong>Classes</strong></td>
    <td>Focused and distracted</td>
  </tr>
  <tr>
    <td><strong>Interface</strong></td>
    <td>Web Bluetooth dashboard</td>
  </tr>
  <tr>
    <td><strong>Accuracy</strong></td>
    <td><strong>92.1%</strong> on evaluated sessions</td>
  </tr>
  <tr>
    <td><strong>Inference</strong></td>
    <td>Real-time execution directly on the embedded device</td>
  </tr>
</table>

## Why the project was built

This project explores how a compact embedded platform can acquire multiple real-time signals, run a lightweight classifier locally, and communicate useful output without relying on continuous cloud inference. It brings together sensor integration, TinyML deployment, Bluetooth communication, and dashboard design in one practical university engineering prototype.

## How it works

1. The pulse sensor and built-in IMU collect physiological and motion signals.
2. Recent sensor readings are grouped into feature windows.
3. The deployed embedded model processes the features.
4. The current state is classified as focused or distracted.
5. The classification result, confidence, and sensor activity are transmitted to the dashboard.
6. The dashboard displays the live monitoring output.

## System architecture

<p align="center">
  <img src="assets/diagrams/system-architecture.png" alt="Embedded multimodal focus monitoring system architecture" width="100%" />
</p>

<p align="center"><sub>Pulse and IMU inputs move through feature extraction, embedded classification, decision logic, and the optional Web Bluetooth interface.</sub></p>

<details>
<summary><strong>View the conceptual workflow</strong></summary>

```mermaid
flowchart LR
    A[Pulse Sensor<br/>and IMU] --> B[Sensor Data<br/>Acquisition]
    B --> C[Feature Window<br/>Creation]
    C --> D[Embedded Feature<br/>Processing]
    D --> E[Edge Impulse<br/>Classifier]
    E --> F{Focused or<br/>Distracted}
    F --> G[Bluetooth<br/>Communication]
    G --> H[Live Web<br/>Dashboard]

    classDef sensor fill:#0b2942,stroke:#22d3ee,color:#e6f7ff,stroke-width:2px;
    classDef ai fill:#312e81,stroke:#a78bfa,color:#ffffff,stroke-width:2px;
    classDef output fill:#082f49,stroke:#67e8f9,color:#ffffff,stroke-width:2px;
    class A,B,C sensor;
    class D,E,F ai;
    class G,H output;
```

> This workflow is a conceptual project overview and does not represent the complete internal implementation.

</details>

## Sensor feature extraction

The classifier uses information derived from the project’s available pulse and motion signals, including:

- Pulse sensor activity
- Desk vibration and movement
- Accelerometer changes
- Gyroscope movement
- Missing pulse contact
- Typing and table-tapping activity

These signals can provide useful patterns for this prototype, but they do not provide a medical diagnosis or a perfect measure of human attention.

<p align="center">
  <img src="assets/results/sensor-output.png" alt="Live sensor signal output" width="88%" />
</p>

<p align="center"><sub>Captured sensor output during project testing.</sub></p>

## Edge Impulse model training

The two-class model was trained using **Edge Impulse** and optimized for deployment on Arduino hardware. Feature visualization was used to inspect separation between focused and distracted activity states. The supplied firmware performs inference directly on the embedded device.

<table>
  <tr>
    <td width="62%" align="center"><img src="assets/edge-impulse/feature-visualization.png" alt="Edge Impulse feature visualization" /></td>
    <td width="38%" align="center"><img src="assets/edge-impulse/model-training.png" alt="Edge Impulse neural-network training configuration" /></td>
  </tr>
  <tr>
    <td align="center"><sub><strong>Feature visualization</strong> — inspected separation between focused and distracted samples.</sub></td>
    <td align="center"><sub><strong>Model training</strong> — two-class neural-network configuration.</sub></td>
  </tr>
</table>

## Hardware platform

<table>
  <tr>
    <td width="33%" align="center"><strong>Arduino Nano 33 BLE Sense Rev2</strong><br/><sub>Embedded inference, acquisition, and communication platform</sub></td>
    <td width="33%" align="center"><strong>HW-827 Pulse Sensor</strong><br/><sub>Pulse activity input for the monitoring pipeline</sub></td>
    <td width="33%" align="center"><strong>Built-in IMU</strong><br/><sub>Accelerometer and gyroscope motion signals</sub></td>
  </tr>
  <tr>
    <td align="center"><strong>USB Power</strong><br/><sub>Power delivery during development and operation</sub></td>
    <td align="center"><strong>Real-time Acquisition</strong><br/><sub>Continuous pulse and motion signal collection</sub></td>
    <td align="center"><strong>Bluetooth</strong><br/><sub>Communication with the live web interface</sub></td>
  </tr>
</table>

<p align="center">
  <img src="assets/hardware/hardware-schematic.png" alt="Focus and distraction detection system hardware schematic" width="92%" />
</p>

<p align="center"><sub>Project hardware schematic showing the pulse-sensor connection, Arduino platform, power arrangement, and built-in IMU.</sub></p>

## Live dashboard

The Web Bluetooth dashboard is designed as the real-time observation layer for the embedded system.

<table>
  <tr>
    <td width="33%"><strong>Focused State Monitoring</strong><br/><sub>Displays the model’s focused-state output.</sub></td>
    <td width="33%"><strong>Distracted State Detection</strong><br/><sub>Shows when the distracted class is predicted.</sub></td>
    <td width="33%"><strong>Confidence Scores</strong><br/><sub>Presents model confidence with each classification.</sub></td>
  </tr>
  <tr>
    <td><strong>Pulse Sensor Activity</strong><br/><sub>Visualizes incoming pulse activity.</sub></td>
    <td><strong>Motion Sensor Readings</strong><br/><sub>Surfaces accelerometer and gyroscope activity.</sub></td>
    <td><strong>Embedded Inference Output</strong><br/><sub>Reports live results received from the device.</sub></td>
  </tr>
</table>

<table>
  <tr>
    <td width="50%" align="center"><img src="assets/dashboard/focused-state.png" alt="Focused-state dashboard output" /></td>
    <td width="50%" align="center"><img src="assets/dashboard/distracted-state.png" alt="Distracted-state dashboard output" /></td>
  </tr>
  <tr>
    <td align="center"><sub><strong>Focused state</strong> — classification, confidence, and live readings.</sub></td>
    <td align="center"><sub><strong>Distracted state</strong> — classification, confidence, and live readings.</sub></td>
  </tr>
</table>

## Key features

- Real-time focus-state classification
- Embedded on-device AI inference
- Pulse and IMU sensor fusion
- Arduino deployment
- Live Bluetooth-connected dashboard
- Confidence score visualization
- Real-time sensor processing
- Lightweight embedded machine-learning model

## Performance results

<table>
  <tr>
    <td align="center" width="33%"><strong>92.1%</strong><br/><sub>Accuracy</sub></td>
    <td align="center" width="33%"><strong>94.4%</strong><br/><sub>Precision</sub></td>
    <td align="center" width="33%"><strong>89.5%</strong><br/><sub>Recall</sub></td>
  </tr>
</table>

| Result | Confirmed value |
|---|---|
| Accuracy | 92.1% |
| Precision | 94.4% |
| Recall | 89.5% |
| Real-Time Inference | Yes |
| Deployment Platform | Arduino Nano 33 BLE Sense Rev2 |
| Classification | Focused versus Distracted |
| Sensors | Pulse and IMU |

No unconfirmed latency, model-size, memory-use, sample-count, or F1-score values are reported here.

<p align="center">
  <img src="assets/results/confusion-matrix.png" alt="Test-session confusion matrix for instant predictions" width="72%" />
</p>

<p align="center"><sub>Recorded test-session confusion matrix for instant predictions.</sub></p>

## Image gallery

| Project view | What it shows |
|---|---|
| [System architecture](assets/diagrams/system-architecture.png) | Complete signal-to-dashboard workflow |
| [Hardware schematic](assets/hardware/hardware-schematic.png) | Pulse sensor, Arduino, power, and built-in IMU arrangement |
| [Feature visualization](assets/edge-impulse/feature-visualization.png) | Edge Impulse feature explorer |
| [Model training](assets/edge-impulse/model-training.png) | Neural-network training configuration |
| [Focused dashboard](assets/dashboard/focused-state.png) | Focused classification and live telemetry |
| [Distracted dashboard](assets/dashboard/distracted-state.png) | Distracted classification and live telemetry |
| [Sensor output](assets/results/sensor-output.png) | Captured live sensor signal |
| [Confusion matrix](assets/results/confusion-matrix.png) | Test-session instant-prediction outcomes |

## Video demonstrations

<table>
  <tr>
    <td width="50%" align="center"><strong>Complete System Demonstration</strong><br/><sub>End-to-end sensor, inference, and dashboard workflow</sub><br/><br/><code>Video coming after review</code></td>
    <td width="50%" align="center"><strong>Focused State Monitoring</strong><br/><sub>Live focused-state classification view</sub><br/><br/><code>Video coming after review</code></td>
  </tr>
  <tr>
    <td align="center"><strong>Distracted State Detection</strong><br/><sub>Live distracted-state response</sub><br/><br/><code>Video coming after review</code></td>
    <td align="center"><strong>Live Bluetooth Dashboard</strong><br/><sub>Device-to-browser monitoring interface</sub><br/><br/><code>Video coming after review</code></td>
  </tr>
  <tr>
    <td colspan="2" align="center"><strong>Sensor and Hardware Setup</strong><br/><sub>Arduino, pulse sensor, and test arrangement</sub><br/><br/><code>Video coming after review</code></td>
  </tr>
</table>

No links are attached until real demonstration files or URLs are supplied. Naming guidance is available in [`videos/README.md`](videos/README.md).

## Technologies used

<p align="center">
  <img src="https://img.shields.io/badge/Arduino-00979D?style=flat-square&logo=arduino&logoColor=white" alt="Arduino" />
  <img src="https://img.shields.io/badge/C%2B%2B-00599C?style=flat-square&logo=cplusplus&logoColor=white" alt="C++" />
  <img src="https://img.shields.io/badge/JavaScript-F7DF1E?style=flat-square&logo=javascript&logoColor=111827" alt="JavaScript" />
  <img src="https://img.shields.io/badge/HTML-E34F26?style=flat-square&logo=html5&logoColor=white" alt="HTML" />
  <img src="https://img.shields.io/badge/Edge%20Impulse-6C5CE7?style=flat-square" alt="Edge Impulse" />
  <img src="https://img.shields.io/badge/TinyML-4F46E5?style=flat-square" alt="TinyML" />
  <img src="https://img.shields.io/badge/Embedded%20AI-071426?style=flat-square" alt="Embedded AI" />
  <img src="https://img.shields.io/badge/Bluetooth-0082FC?style=flat-square&logo=bluetooth&logoColor=white" alt="Bluetooth" />
  <img src="https://img.shields.io/badge/Web%20Bluetooth-22D3EE?style=flat-square&labelColor=0B2942" alt="Web Bluetooth" />
  <img src="https://img.shields.io/badge/IMU-Sensors-A78BFA?style=flat-square" alt="IMU sensors" />
  <img src="https://img.shields.io/badge/Pulse-Sensor-EC4899?style=flat-square" alt="Pulse sensors" />
  <img src="https://img.shields.io/badge/Nano%2033%20BLE%20Sense-Rev2-00979D?style=flat-square" alt="Arduino Nano 33 BLE Sense Rev2" />
</p>

## Source code structure

The repository now includes the supplied Arduino sketches and project source notes:

```text
src/
|-- FocusMonitor_Final.ino
|-- IMU_Test.ino
|-- PulseSensor_Basic_Test.ino
|-- PulseSensor_Test.ino
|-- SOURCE_NOTES.md
`-- README.md
```

The uploaded filenames do not always match the behavior in their contents, so [`src/README.md`](src/README.md) documents each file from direct inspection. The uploaded `dashboard.html` contained Markdown notes rather than HTML and is therefore preserved as `SOURCE_NOTES.md`; a runnable dashboard source file is not currently included.

## Challenges and engineering lessons

The project brings several engineering concerns together: coordinating physiological and motion streams, organizing recent data into consistent feature windows, distinguishing meaningful activity from contact or movement changes, deploying a trained model to constrained hardware, and presenting embedded results clearly in a browser interface.

It also reinforces an important interpretation lesson: a classifier can recognize patterns in the signals on which it was trained, but its output must stay framed within the limits of those signals, the evaluated sessions, and the educational prototype context.

## Limitations and ethical notice

> [!IMPORTANT]
> **This project is an educational engineering prototype.**
>
> It is not a medical device and must not be used to diagnose attention disorders, mental health conditions, cognitive ability, or medical conditions.
>
> Focus and distraction are inferred from limited physiological and motion-based signals and may not represent a person’s actual cognitive state in every situation.

## Future work

- Improved classification accuracy
- Expanded sensor fusion
- Mobile dashboard integration
- Long-term activity analysis
- Additional behavioural classes
- Improved sensor contact detection
- More extensive real-world evaluation

## Final technical report

The supplied tutorial report is available here:

### [Open the Embedded AI Project Tutorial Report](<docs/Embedded AI Project Tutorial Report.pdf>)

The report accompanies the repository’s documentation of the project workflow. See [`docs/README.md`](docs/README.md) for file details and naming guidance.

## Authors

<table>
  <tr>
    <td align="center"><strong>Hasan Al Hussein</strong></td>
    <td align="center"><strong>Omar Yousef</strong></td>
    <td align="center"><strong>Ahmad Alhawamdeh</strong></td>
  </tr>
  <tr>
    <td colspan="3" align="center">Khalifa University</td>
  </tr>
</table>

## Repository contents

```text
embedded-ai-focus-monitor/
|-- README.md                    # Main project showcase
|-- assets/
|   |-- dashboard/               # Focused and distracted dashboard captures
|   |-- diagrams/                # System architecture
|   |-- edge-impulse/            # Feature and model-training captures
|   |-- hardware/                # Hardware schematic
|   `-- results/                 # Sensor output and confusion matrix
|-- docs/                        # Tutorial report and documentation guide
|-- src/                         # Supplied Arduino source and source guide
`-- videos/                      # Future demonstration guidance
```

## Repository notice

This repository is a technical project showcase containing documentation, selected source files, visuals, and demonstrations as they become available and are reviewed. It does not represent a commercial or clinically validated product.

<div align="center">

![Footer](https://capsule-render.vercel.app/api?type=waving&height=140&section=footer&color=0:22D3EE,45:4F46E5,100:071426&animation=fadeIn)

</div>
