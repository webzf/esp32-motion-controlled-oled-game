# 🎮 ESP32 Motion-Controlled OLED Game

<p align="center">
  <img src="YOUR_GIF_LINK" width="320" alt="ESP32 Motion Game Demo"/>
</p>

<p align="center">
  <b>Control a game with motion using ESP32 + OLED + MPU6050</b><br>
  No buttons. Just tilt and play.
</p>

<p align="center">
  <a href="https://www.youtube.com/shorts/8D0C3xrz-D4">
    <img src="https://img.shields.io/badge/Watch-YouTube%20Short-red?style=for-the-badge&logo=youtube"/>
  </a>
  <a href="https://github.com/YOUR_USERNAME/esp32-motion-game">
    <img src="https://img.shields.io/github/stars/YOUR_USERNAME/esp32-motion-game?style=for-the-badge"/>
  </a>
  <a href="https://beacons.ai/ztronics/">
    <img src="https://img.shields.io/badge/Get-Components-blue?style=for-the-badge"/>
  </a>
</p>

---

## 🚀 Watch It in Action

🎬 **YouTube Short**  
👉 https://www.youtube.com/shorts/8D0C3xrz-D4

---

## 💻 Get the Code

    git clone https://github.com/YOUR_USERNAME/esp32-motion-game.git
    cd esp32-motion-game

---

## 🧰 Components (Tested Setup)

| Component | Buy Link |
|----------|----------|
| ESP32 | 👉 https://beacons.ai/ztronics/ |
| OLED SSD1306 | 👉 https://beacons.ai/ztronics/ |
| MPU6050 Gyroscope | 👉 https://beacons.ai/ztronics/ |

💡 Using the same components ensures compatibility and saves time.

---

## ⚙️ Features

- 🎮 Motion-controlled gameplay (no buttons)
- ⚡ Smooth real-time animation
- 🧠 Gyroscope-based movement (MPU6050)
- 🪶 Lightweight & optimized code
- 🧩 Beginner-friendly project

---

## 🔌 Wiring (I2C)

| OLED / MPU6050 | ESP32 |
|---------------|------|
| VCC | 3.3V |
| GND | GND |
| SDA | GPIO 21 |
| SCL | GPIO 22 |

---

## 📦 Required Libraries

- Adafruit SSD1306  
- Adafruit GFX  
- Wire  
- MPU6050  

---

## ▶️ How It Works

- ESP32 reads tilt data from MPU6050  
- Converts motion into movement  
- Renders game in real-time on OLED  
- You control everything by tilting 😄  

---

## 🧪 Troubleshooting

**OLED not working?**
- Check I2C address (0x3C or 0x3D)
- Verify wiring

**MPU6050 not detected?**
- Confirm SDA/SCL connections  
- Try another MPU6050 library  

**Low FPS / lag?**
- Reduce display refresh rate  

---

## ❤️ Support the Project

- ⭐ Star the repo  
- 🔁 Share with friends  
- 💬 Leave feedback  

---

## 🔗 More Projects + Components

👉 https://beacons.ai/ztronics/

---

## 🔍 SEO Keywords

esp32 oled tutorial  
esp32 game project  
mpu6050 esp32 example  
arduino oled game  
diy esp32 projects  
esp32 motion control game  
oled display esp32 project  

---

## 📄 License

This project is open-source — feel free to use and modify.
