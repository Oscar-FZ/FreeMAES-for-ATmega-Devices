# FreeMAES for ATmega Devices 🚀  
*Adaptation of the FreeMAES library for embedded MAS development on ATmega microcontrollers.*

---

##  Overview

This project provides an **adaptation of the [FreeMAES](https://github.com/DRoMarin/FreeMAES.git)** multi-agent framework to **Microchip ATmega-based devices**, enabling distributed agent-based applications on low-resource embedded platforms.

Additionally, it includes a complete **Multi-Agent System (MAS)** implementation developed for the **SunFounder Galaxy RVR** rover.

---

# 🧩 Requirements

FreeMAES works in conjunction with the real-time operating system **FreeRTOS**, so it is required to install FreeRTOS before using this library.

You can install it through the **Arduino IDE Library Manager**:

1. Open **Arduino IDE** → go to **Sketch → Include Library → Manage Libraries…**
2. Search for **“FreeRTOS”** by *Richard Barry*
3. Install **version 11** (Note: newer versions *may* work, but are not guaranteed)

> ⚠️ **Important:**
> This repository includes a custom `FreeRTOSConfig.h` file.
> Make sure to use this version instead of the original one provided by the FreeRTOS library.

---

# ⚙️ How to Install the Library

It is recommended that you use **Arduino IDE** for implementing this library.

### Installation Steps

1. Add both **Supporting_Functions** and **maes-rtos** folders to your Arduino IDE `libraries` directory.
2. Open Arduino IDE → **Sketch → Include Library** → under *Contributed Libraries*, add:
   - `Supporting_Functions`
   - `maes-rtos`
3. Restart Arduino IDE.
4. Include both libraries at the start of your project:

```cpp
#include <supporting_functions.h>
#include <maes-rtos.h>
```

---

# 🤖 GalaxyRVR MAS Project

This repository also includes a **Multi-Agent System (MAS)** implementation for the **SunFounder Galaxy RVR** rover.
It was deployed on the Galaxy RVR using an **Arduino Mega 2560**, replacing the original **Arduino Uno R3** (for reasons explained in the *Recommendations* section).

The MAS consists of **nine agents**, each responsible for a specific subsystem:

| Agent Function | Source Files |
|----------------|---------------|
| Wheel Motor Control Agent | `car_control_agent.cpp / .h` |
| RGB Lights Control Agent | `rgb_agent.cpp / .h` |
| Servo Control Agent | `soft_servo_agent.cpp / .h` |
| Infrared Sensor Agent | `infrared_agent.cpp / .h` |
| Ultrasonic Sensor Agent | `ultrasonic_agent.cpp / .h` |
| Object Following Mode Agent | `following_mode_agent.cpp / .h` |
| Obstacle Avoidance Mode Agent | `avoidance_mode_agent.cpp / .h` |
| Mode Handler Agent | `mode_handler_agent.cpp / .h` |
| WiFi Communications Agent | `wifi_agent.cpp / .h` |

Each agent is implemented as a **FreeMAES agent task** running on **FreeRTOS**.

---

# 💡 Recommendations

It is **highly recommended** to use FreeMAES on devices with **higher SRAM capacity**.

Initially, the GalaxyRVR MAS was implemented on an **Arduino Uno R3 (2 kB SRAM)** — it worked, but the limited memory only allowed the use of two simple agents.

If you plan to implement a more complex MAS, consider using devices with larger SRAM:

| Device | Microcontroller | Flash | SRAM | EEPROM | Recommendation |
|---------|----------------|------|------|------|------|
| Arduino UNO Mini | ATmega328P | 32kB | 2kB | 1kB | - |
| Arduino UNO Rev3 | ATmega328P | 32kB | 2kB | 1kB | - |
| Arduino UNO WiFi Rev2 | ATmega4809 | 48kB | 6kB | 256B | ✅ |
| Arduino Leonardo | ATmega32u4 | 32kB | 2.5kB	 | 1kB | - |
| Arduino Mega 2560 Rev3 | ATmega2560 | 256kB | 8kB | 4kB | ✅ |
| Arduino Micro | ATmega32u4 | 32kB | 2.5kB | 1kB | - |

---

# 🧑‍💻 Author

**Óscar Fernández Zúñiga**
Instituto Tecnológico de Costa Rica (TEC)
School of Electronics Engineering
**SETEC Lab – Space Systems Laboratory**
