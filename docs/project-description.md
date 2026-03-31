# 📘 Project Description: Smart Room Fan Automation System

## 🔍 Overview
The Smart Room Fan Automation System is an embedded system project designed to optimize energy usage and improve comfort by automatically controlling a fan based on room occupancy and temperature.

This system integrates multiple sensors and control logic to create a responsive and efficient environment without requiring manual intervention.

---

## 🎯 Objectives
- Automate fan operation based on real-time conditions
- Reduce energy wastage when the room is unoccupied
- Dynamically adjust fan speed based on temperature
- Provide real-time feedback using an LCD display

---

## 🧠 System Architecture

The system consists of three main modules:

### 1. Occupancy Detection Module
- Uses two IR sensors placed at entry/exit points
- Detects direction of movement:
  - IR1 → IR2 → Person entering
  - IR2 → IR1 → Person exiting
- Maintains a real-time people counter

### 2. Temperature Monitoring Module
- Uses DHT11 sensor
- Continuously reads ambient temperature
- Provides input for fan speed control logic

### 3. Fan Control Module
- Fan operates only when people are present
- Speed is controlled using PWM signals
- Speed levels are mapped to temperature ranges

---

## ⚙️ Working Principle

1. System initializes and waits for sensor input  
2. IR sensors detect movement and update people count  
3. Temperature is continuously monitored  
4. Fan behavior:
   - OFF → if no people in the room  
   - ON → if people are present  
   - Fan speed increases as temperature rises and decreases as temperature falls.
5. LCD displays:
   - Current temperature  
   - Number of people in the room  

---

## 📊 Fan Speed Logic

| Temperature (°C) | Fan Speed (PWM) |
|-----------------|----------------|
| < 25            | OFF            |
| 25–26           | Low            |
| 26–27           | Medium         |
| 27–28           | High           |
| ≥ 28            | Maximum        |

---

## ⚠️ Limitations
- IR sensors may miscount in crowded conditions
- DHT11 has limited accuracy compared to advanced sensors
- System assumes single entry/exit path

---

## 🧩 Conclusion
This project demonstrates how embedded systems can be used to build intelligent automation solutions that improve efficiency and user comfort. It combines sensor integration, control systems and real-time processing into a practical application.