# 📡 Smart Network Health Monitoring & Channel Recommendation System

## 📌 Overview

This project presents an IoT-based system that intelligently analyzes WiFi network congestion and recommends the optimal channel to improve connectivity.

Unlike basic WiFi scanners, this system performs real-time analysis using channel occupancy and RSSI data, and provides both local and cloud-based monitoring for better decision-making in dense network environments.

---

## 🏆 Achievement

Awarded **First Prize** at the College Mini Project Expo for innovation and practical implementation.

---

## 🎯 Problem Statement

In modern digital environments such as hostels, campuses, and offices, multiple WiFi networks operate on overlapping channels. This leads to interference, reduced speed, and unstable connectivity.

Most users rely on automatic router settings without understanding channel congestion, resulting in suboptimal performance.

---

## 💡 Proposed Solution

The system uses an ESP32 microcontroller to scan nearby WiFi networks and collect parameters such as channel number and signal strength (RSSI). It analyzes congestion and recommends the most optimal channel for improved performance.

Additionally, the system integrates with the ThingSpeak IoT cloud platform for real-time monitoring and visualization.

---

## 🚀 What Makes This Different?

* Performs intelligent channel congestion analysis (not just scanning)
* Automatically recommends the best channel
* Combines embedded systems with IoT cloud analytics
* Provides both local (OLED + LED) and remote (ThingSpeak) monitoring
* Enables real-time and historical data analysis

---

## ⚙️ Key Features

* Real-time WiFi network scanning
* Channel occupancy analysis
* RSSI-based signal strength evaluation
* Optimal channel recommendation algorithm
* OLED display output
* RGB LED status indication
* ThingSpeak cloud integration
* MATLAB-based visualization

---

## 🧠 How It Works

1. ESP32 scans nearby WiFi networks
2. Extracts channel number and RSSI values
3. Calculates channel occupancy and average signal strength
4. Determines network health status
5. Recommends optimal channel with minimal interference
6. Displays output on OLED and RGB LED
7. Uploads data to ThingSpeak cloud

---

## 🧩 Hardware Components

* ESP32 Microcontroller
* OLED Display (I2C - SSD1306)
* RGB LED
* Resistors (220Ω)
* Breadboard & Jumper wires

---

## ☁️ IoT Cloud Integration

The system uses ThingSpeak to upload real-time data such as channel occupancy, RSSI values, and network health status.

The data is visualized using:

* Graphical dashboards
* MATLAB analytics for deeper insights

---

## 📊 Output

* Recommended WiFi channel displayed on OLED
* Network health indication using RGB LED
* Real-time dashboard on ThingSpeak
* Graph-based analysis using MATLAB

---

## 🌍 Applications

* Educational institutions
* Hostels and apartments
* Office environments
* Smart campuses
* Public WiFi networks

---

## 🧪 Hackathon Enhancement

This project is extended for hackathon submission with improved visualization and refined decision logic for better real-time analysis.

---

## 🚀 Future Scope

* Mobile application integration
* Automatic router channel switching
* AI-based congestion prediction
* Support for 5GHz band

---

## 🔗 Project Resources

* ThingSpeak Dashboard: https://thingspeak.mathworks.com/channels/3273014
* Wokwi Simulation: https://wokwi.com/projects/456940084448315393

---

## 💬 Key Insight

**“Best channel does not only mean strongest signal — it also means least interference.”**

---

## 📌 Conclusion

This project provides a practical and scalable solution for improving WiFi performance in congested environments.

By combining embedded systems, real-time data analysis, and IoT cloud integration, it enables intelligent and data-driven network optimization.
