# ENGG1100 Arduino IDE Examples

This repository contains various Arduino IDE code examples to assist engineering students in their first year team project course.

If you attended a presentation session, you can view the associated slides [here](https://github.com/aburo8/engg1100-demo/tree/master/presentations).

## Getting Started

These examples are designed for you to be able to easily follow along! To get started you will need to have the Arduino IDE installed and the access to the associated hardware.

### Arduino IDE Installation

The easiest way to write code for a micro-controller is using the Arduino IDE. An IDE is an Integrated Development Environment, this is basically a code editor which contains some extra neat features like a debugger. Download the latest version of the Arduino IDE for your platform of choice [here](https://www.arduino.cc/en/software)!

### Running Examples

To run an example follow these steps:

1. Download (or clone) this codebase from GitHub to your local computer. You can do this by pressing the **green button** in the top right corner which says `<>Code`.
2. Open the Arduino IDE. Select `File -> Open` then navigate to the example you wish to run.
3. Configure your board type by selecting `Tools -> Board -> Arduino AVR Boards -> Arduino Uno`. *Note: if you are using a different board, make sure you select the appropriate option*.
4. Connect your board to the computer using the USB cable.
5. Configure your Connection Port by selecting `Tools -> Port -> COMX (Arduino Uno)`. *Note: if you are on Windows, your ports will be in the COMX format, don't worry about the number just select the port which has your board name e.g. Arduino Uno. If you are on a Unix based system (like MaxOS), your ports will look something like /dev/ttyUSB0. Again, just select the port which says board name*.
6. Assemble the hardware for the example you are trying to run. Do this by following the hardware instructions below for the specified example.
7. Press the `->` icon in the top left of the IDE to upload the example code to the Arduino board.
8. BAM! You are now running the code example!
9. [BONUS STEP] Try making some changes to the code example! Get creative and have some fun! Maybe try and combine different examples to build something super cool!

Examples List -

Not all of our demo code will work *out of the box* with any micro-controller. We have split out examples up into Arduino (ATmega boards) and ESP32 boards.

Arduino (ATmega) Boards -
- [IR Motor Remote Control](#ir-motor-control-motor_control_demo)
- [IR Winch Remote Control](#ir-winch-control-winch_control_demo)
- [IR Remote Controller Mapping](#ir-remote-mapping-ir_receiver_test)

ESP32 Boards -
- [ESP32 Sensing](#ir-motor-control-motor_control_demo)
- [ESP32 Remote Controlled Servo Control](#ir-motor-control-motor_control_demo)
- [ESP32 Simple Web Server](#ir-motor-control-motor_control_demo)
- [ESP32 ESP Home Workshop - NO CODE NEEDED!](#ir-motor-control-motor_control_demo)

After an example which isn't in this repository?!?!?! Luckily there are plenty of resources out there! Give the following a try -

- [Arduino Official Built-In Examples](https://docs.arduino.cc/built-in-examples/) - These are fantastic way to get started! You can access these examples directly from within the Arduino IDE by selecting `File -> Examples`!
- Google (or Generative AI), there are a plethora of Arduino code samples scattered across the internet you just need to search for them. Generative AI tools like ChatGPT can also be a great way to generate an obscure or niche code example. Proceed with *CAUTION* though, not all examples are 100% accurate (or working).

## Notes & Acknowledgments

- To develop the Circuit Diagrams, a free open source tool called **Fritzing** was used. Check it out [here](https://fritzing.org/)!
- Make sure you reference any code samples that you modify or copy! This is really important so you don't get in trouble for breaching University Academic Integrity policies!!!
