# 🌊 ESP32 Water Quality Monitoring System

## 📝 Description

This project implements a water quality monitoring system using an ESP32 microcontroller. The system measures various water parameters and can transmit data over WiFi.

## 🌟 Features

- 📶 WiFi connectivity for data transmission
- 🔄 WebSocket support for real-time monitoring
- 📡 Serial communication for device configuration
- 🔌 JSON-based data exchange format

## 🛠️ Project Structure

```
src/
├── main.cpp              # Main application entry point
├── SerialComm.*          # Handles serial communication and command parsing
└── Socket.*              # Manages WebSocket connections and data transmission
```

## 🚀 Getting Started

### Prerequisites

- PlatformIO IDE (recommended) or Arduino IDE
- ESP32 board support package
- Required libraries:
  - ArduinoJson
  - WiFi
  - WebSockets (if using WebSocket functionality)

### Hardware Setup

- **ESP32 Board**: Any ESP32 development board
- **Serial Interface**:
  - RX: GPIO16
  - TX: GPIO17

### Installation

1. Clone this repository
2. Open the project in your preferred IDE
3. Configure WiFi credentials and API key through serial commands
4. Upload the firmware to your ESP32
5. Monitor the serial output at 9600 baud

## 🔧 Usage

### Initial Configuration

1. Connect to the ESP32 via serial monitor
2. Configure WiFi credentials:
   ```
   setWifiSsid <your_ssid>
   setWifiPassword <your_password>
   ```
3. Set your API key:
   ```
   setApiKey <your_api_key>
   ```
4. Complete configuration:
   ```
   configureFinished
   ```

## 🤝 Contributing

### 🌿 Branching Strategy

| Branch            | Description                            | Allowed commit types                 |
| ----------------- | -------------------------------------- | ------------------------------------ |
| `main`            | Main stable branch                     | Only `merge` and tags (`vX.X.X`)     |
| `feature/<name>`  | Adds new functionalities               | `feat`, `test`, `docs`, `style`      |
| `hotfix/<name>`   | Urgent fix in production               | `fix`, `style`, `chore`              |
| `bugfix/<name>`   | Non-urgent bug fix                     | `fix`, `test`                        |
| `refactor/<name>` | Code improvements without logic change | `refactor`, `style`, `docs`, `chore` |
| `docs/<name>`     | Documentation updates                  | `docs`                               |

## ✍️ Commit types (Conventional Commits)

We use the [Conventional Commits](https://www.conventionalcommits.org/) format to improve readability of history.

| Type       | Main usage                                            | Example                                                |
| ---------- | ----------------------------------------------------- | ------------------------------------------------------ |
| `feat`     | New functionality or feature                          | `feat: add new sensor for water turbidity measurement` |
| `fix`      | Bug fix                                               | `fix: correct bug in sensor reading calculation`       |
| `refactor` | Internal code improvement (without changing behavior) | `refactor: optimize code for better performance`       |
| `docs`     | Documentation updates                                 | `docs: update README with latest project information`  |
| `test`     | Add or modify tests                                   | `test: add unit tests for sensor reading validation`   |
| `style`    | Code formatting or styling (no logic changes)         | `style: apply consistent coding style`                 |
| `chore`    | Maintenance tasks that do not affect code logic       | `chore: update dependencies to latest version`         |

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 📧 Contact

For support or questions, please open an issue in the repository.

---

<div align="center">
  Made with ❤️ for clean water monitoring
</div>
