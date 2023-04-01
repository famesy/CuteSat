# CubeSat PCB Design for Reliable Space Missions

CubeSat is an affordable and popular educational platform for deploying payloads into orbit. However, many university-level missions fail at a rate of around 50%. The primary reason for this is the difficulty of adapting an existing design, which results in poorly designed hardware for the harsh environment of space and a lack of failure handling software.

To address this problem, we have developed an expandable, low-cost printed circuit board (PCB) that can be stacked and includes the following components:

- Power supply unit
- Microcontroller
- Several sensors
- Watchdog
- Communication bus isolation
- External memory

We have used a component selection methodology that is based on existing research and adapted it to our design. We have also implemented a software Hamming error-correction code to protect the data.

Since our PCBs are modular, readers can design their own system using our design as a starting point. We offer failure handler software and hardware that can be easily integrated into their design. Our ultimate goal is to make space studies more accessible to everyone, increase the success rate, and allow people to focus on their missions rather than the hectic development.

Lastly, we intend to make our project open source so that it can continue to grow and improve over time. We hope that this project will develop into a community where people can discuss their designs and share their changes and knowledge for various missions.

Thank you for considering our CubeSat PCB design for your space mission needs.

## Project Components
This project includes two distinct folders: hardware and software.

### Hardware
The hardware folder contains four PCB designs that were used in our mission:

#### MCU (base PCB)

![Base PCB](/images/Base_PCB.png)

#### Motor driver (payload PCB)

![Driver PCB](/images/Driver_PCB.png)

#### Encoder (payload PCB)

![Encoder PCB](/images/Encoder_PCB.png)

#### ST-Link adapter

### Software
The software folder contains STM32 projects that include libraries for interfacing with the sensors and implementing error detection and correction algorithms.

### How its look when assemble

![SUM PCB](/images/Sum_PCB.png)

####Thank you for your interest in our project!