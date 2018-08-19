# Overview
This is a ECG/SPO2 Monitor Project. We mainly used TI's (Texas Instrument) ADS1293/AFE4400 analog front-end IC to acquire physiology data form human body, and used TI's MSP430F149 MCU to control these Chips, and send the data to our Android Smartphone App via TI's Bluetooth IC CC2540. In our smartphone App, we can display ECG/PPG wavefore, compute & display SPO2,Heart Rate, and Heart Rate Variability(HRV), and control the hardware to running on different acquision mode (such as 3-Leads or 5-Leads mode).

To do so, we disigned and made custome PCB using Autodesk EAGLE, doing embedded system programing for MSP430 using IAR IDE, and doing some stuff about smartphone APP.

The major advantages of our system, is our outstanding power consumption performance. Our hardware only took about 5mW Power for Li-ion battery. Also, our PCB is super portable, size less than 10-by-10cm.

We Shared the majority of our code and design files. Including MSP430 program, PCB layout, APP code.

We do these stuff is for a [National BME(Biomedical Engineering) Competition for College Students](http://bmedesign.medmeeting.org/cn) in ShenZhen, China.

# Hardware

# Development Team
Jingjie Li (jingjie.li@nyu.edu) - Hardware, PCB Layout, Part of MSP430 Programming
Jinming Li (lijinmingli@foxmail.com) - MSP430 Programming
Haoyi Tao (thyzyfx@qq.com) - Android Programming

We are all class of 2019 BME undergraduate student in Xi'an Jiaotong University
