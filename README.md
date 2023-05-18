![image](https://github.com/mishael254/fluidvolumentricsystem/assets/64144118/311ddb84-5d4e-4b9f-8d91-6e7147b4dab5)
![image](https://github.com/mishael254/fluidvolumentricsystem/assets/64144118/16a4e882-3a8d-4921-baf6-65fe3a92ec50)

OBJECTIVES
general objectives
to develop a model that can determine the position of the level relative to the top or bottom of the process fluid storage vessel,[3] measuring the actual volume of the fluid contained, and then displaying the data to a user-friendly interface in real time.

specific objectives

To gather and analyze existing level and volume measurement systems.
To design the proposed level and volume measurement system
To implement the developed automated fluid volume measurement system
To test and validate the newly developed fluid volume verification system

significance of study
The proposed system aims to help companies that deal with fluid resources like raw milk or petroleum to identify and monitor their resources and products accurately and in real time saving on cost and expenses and also eliminating fraud and exploitation cases as a result of wrong inaccurate measurements.
scope of the study
the project aims at providing an efficient, easy to use fluid measurement system to cooperative creameries and large-scale petroleum companies for managing and accounting for their fluid resources like milk and petroleum in large scale in a more easy, efficient and time saving way. the system works by fully utilizing storage capacities by determining the fluid actual volume and computing the volume remaining accurately and in real time reducing fluid loads [3] 
the proposed system uses reference model of real time architecture to coordinate its components to synchronize for maximum performance and response eliminating time delays using low level C and C++ language 
![image](https://github.com/mishael254/fluidvolumentricsystem/assets/64144118/cfc8ac88-51ee-46fa-9e12-322ae7415bbb)

limitations
there are various environmental factors this system relies on that go in to assumption as being constant and yet they are not, some constants like air pressure density,[4] or gravity may affect this system when they change leading to wrong output,
and since this are environmental and natural factors, they may change over time and the system may not be able to predict these changes let alone adjusting to these changes this overall would affect the behavior of the system.

 




: system architecture
An architecture description is a formal representation of a system, organized in a way that supports reasoning about the structures and the behaviours of the system[24]
![image](https://github.com/mishael254/fluidvolumentricsystem/assets/64144118/2e522760-b649-4e54-8a8b-2e8743885562)


In this sub topic I am going to describe the method which will be used to implement this project. This project is divided into two main parts which are hardware design and software design.





 

: Hardware design
 For the hardware design, the main focus is on the main controller hardware; The Arduino Uno. And what is an Arduino uno? This is an open-source microcontroller board based on the Microchip ATmega328P microcontroller and developed by Arduino.cc and initially released in 2010.[24][25] The board is equipped with sets of digital and analog input/output (I/O) pins that may be interfaced to various expansion boards (shields) and other circuits.[1] The board has 14 digital I/O pins (six capable of PWM output), 6 analog I/O pins, and is programmable with the Arduino IDE (Integrated Development Environment), via a type B USB cable.
The other focus on the hardware of this project are the sensors. Sensors are devices that detect physical parameter of interest eg sound or heat and then converts this physical forces into electrical signals which are processed in analog mode and then can be used or even measured by an electrical or an electronic system.
 The ATmega328P microcontroller chip, is mounted on a board that has the input and  output pins and through this pins,  I have connected two of the sensors that will be used to gather and detect a physical parameter called pressure and ultrasonic waves.

·	Pressure transducer transmitter sensor – To measure the pressure exerted
![image](https://github.com/mishael254/fluidvolumentricsystem/assets/64144118/656554f5-feaa-42c7-828f-84a4d883ca5d)

This sensor consists of three wires black, yellow and red wire. Where the red wire is connected with voltage source the black wire is connected with the ground the yellow wire is connected to the analogue pin A0 which will be used for the measurement. 
·	Ultrasonic Distance Sensor - HC-SR04 to act as a calibration tool and measure the volume before a liquid is displaced.
This economical sensor provides 2cm to 400cm of non-contact measurement functionality with a ranging accuracy that can reach up to 3mm. The HC-SR04 module includes an ultrasonic transmitter, a receiver and a control circuit.

There are only four pins that you need to worry about on the HC-SR04: VCC (Power), Trig (Trigger), Echo (Receive), and GND (Ground). You will find this sensor very easy to set up and use 
![image](https://github.com/mishael254/fluidvolumentricsystem/assets/64144118/2bbbee5a-a706-4bed-9d54-ada55462f96d)

Features
·	Operating Voltage: 5V DC
·	Operating Current: 15mA
·	Measure Angle: 15°
·	Ranging Distance: 2cm - 4m


This sensor has additional control circuitry that can prevent inconsistent "bouncy" data depending on the application.
 

4.2.3.2: Software design
Meanwhile, for the software design,I implemented and used various software design tools.  I used the Arduino software which can be downloaded directly   through   the   internet   from   the   Arduino   main   page. The  Arduino  Software (IDE) compiler is used to edit, test, simulate and dump the code into the microprocessor. This software really came in handy especially when communicating with the ATmega328P microcontroller.
I also used Microsoft visual studio 2022 IDE, to come up with the logic behind all the computations required for the project to get a stabilized constant data flow between the hardware and the software.
I also used various APIs so as to establish a serial port connection like the win 32 API which is basically an API that is provided by the Microsoft cooperation to windows operating systems that ensures that a programmer can have hardware access to serial ports in windows.
And as for the framework , I used QT framework, this is a c++ support framework that allows easy and free use of design tools to create and come up with a design user interface of your choice. Qt is full of tools to simplify developers' lives and help with not just coding but also tasks like building, compiling, localization, and more.
As for compilation I used the AVR-GCC toolkit The AVR GCC Toolchain is a collection of tools and libraries used to compile your code for the AVR microcontrollers. This collection includes a compiler, assembler, linker, and some libraries.
Most of the tools are based on efforts from the GNU community (GCC stands for GNU Compiler Collection), and some others are developed by Microchip.
