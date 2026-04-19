# ESP32 Workshop (ESPHome)

An interactive, hands-on workshop that walks students through progressively complex ESP32 demos using [ESPHome](https://esphome.io/). Instead of writing C/Arduino code, device behaviour is defined in YAML configuration files and flashed to the ESP32 via the ESPHome CLI — all from within a Jupyter notebook.

The ESP32 runs in **Wi-Fi Access Point mode** and hosts a web server at `http://192.168.4.1`, so students can interact with their hardware from any phone or laptop browser — no router, app, or Home Assistant required.

## Prerequisites

- Python 3
- ESP32 dev board (ESP-WROOM-32)
- USB cable for flashing
- Hardware components (see individual demos below)

## Getting Started

1. **Open the workshop notebook** — [`Workshop.ipynb`](Workshop.ipynb) guides you through every step.

2. **Create a Python virtual environment** and install ESPHome:

   ```powershell
   python -m venv .venv
   .\.venv\Scripts\python.exe -m pip install --upgrade pip
   .\.venv\Scripts\python.exe -m pip install esphome
   ```

3. **Configure secrets** — copy [`configs/secrets.yaml.example`](configs/secrets.yaml.example) to `configs/secrets.yaml` and set your Wi-Fi password:

   ```yaml
   wifi_password: "your_password_here"
   ```

4. **Connect your ESP32** via USB and follow the notebook cells in order.

## Network Configuration

All demo configs run the ESP32 in **Wi-Fi Access Point (AP) mode**:
- The ESP32 creates its own network: `MY_ESP32` (password in `secrets.yaml`)
- No internet connection or router needed — it acts as its own gateway
- Access the web dashboard at **`http://192.168.4.1`** from any connected device

Each config includes `web_server: local: true`, which embeds the web UI directly on the ESP32. This ensures the interface works without external CDN dependencies, making it ideal for offline/isolated environments where the device is the only network gateway.

## Workshop Demos

Each demo builds on the previous one. Flash a config with:

```powershell
.\.venv\Scripts\python.exe -m esphome run configs/<config_file>.yaml
```

### Demo 0 — LED + Button (Basic I/O)

**Config:** [`0.init.yaml`](configs/0.init.yaml) · **Wiring:** [LED+Button](images/LED+Button_bb.png)

| Component | GPIO |
|-----------|------|
| LED | GPIO5 |
| Button (INPUT_PULLUP) | GPIO23 |

Toggle the LED and read button state from the web dashboard. Introduces GPIO and the ESPHome web server.

### Demo 1 — LED + Button + Automation

**Config:** [`1.automation.yaml`](configs/1.automation.yaml) · **Wiring:** same as Demo 0

Same circuit — now pressing the physical button automatically toggles the LED via `on_press`/`on_release` automations. Introduces event-driven logic in YAML.

### Demo 2 — Servo Control

**Config:** [`2.servo.yaml`](configs/2.servo.yaml) · **Wiring:** [Servo](images/Servo_bb.png)

| Component | GPIO |
|-----------|------|
| Continuous Servo (PWM) | GPIO26 |

A slider on the web page controls servo speed and direction (−100 % to +100 %). Introduces the ESP32 LEDC PWM peripheral and the servo component.

### Demo 3 — MPU6050 Accelerometer / Gyroscope

**Config:** [`3.accelerometer.yaml`](configs/3.accelerometer.yaml) · **Wiring:** [MPU6050](images/MPU6050_bb.png)

| Component | GPIO |
|-----------|------|
| MPU6050 SDA | GPIO21 |
| MPU6050 SCL | GPIO22 |

Streams acceleration (X/Y/Z), gyroscope (X/Y/Z), and temperature readings to the web dashboard every second. Introduces I2C communication and sensor integration.

### Demo 4 — Tilt-Controlled Servo (Capstone)

**Config:** [`4.control.yaml`](configs/4.control.yaml) · **Wiring:** MPU6050 + Servo (Demos 2 & 3 combined)

Tilting the MPU6050 along the X-axis directly controls the servo speed and direction in real time (100 ms update interval). Uses a C++ lambda to clamp and map the accelerometer reading. This is the capstone demo showing closed-loop sensor-to-actuator control.

## Folder Structure

```
esp32/
├── Workshop.ipynb          # Main workshop notebook
├── configs/
│   ├── 0.init.yaml         # LED + Button
│   ├── 1.automation.yaml   # LED + Button + Automation
│   ├── 2.servo.yaml        # Servo control
│   ├── 3.accelerometer.yaml# MPU6050 sensor
│   ├── 4.control.yaml      # Tilt → Servo (capstone)
│   ├── secrets.yaml.example# Template for Wi-Fi credentials
│   └── secrets.yaml        # Your credentials (git-ignored)
├── fritzing/               # Editable Fritzing wiring diagrams
│   ├── LED+Button.fzz
│   ├── MPU6050.fzz
│   └── Servo.fzz
└── images/                 # Wiring diagrams, pinouts, reference images
```

## Reference

- [ESPHome Documentation](https://esphome.io/)
- [ESP32 Pinout](images/pinout.png)
