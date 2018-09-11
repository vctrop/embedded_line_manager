# embedded_queue_manager
A queue manager embedded in an Atmel SAM R21 microontroller.

The manager deals with three types of priority in its queue. It can be used to manage various types of real life queues, such as those found on supermarkets, banks, hospitals and others.

This project was implemented in Atmel Studio 7.0, and is dependent uppon the following Atmel ASF Wizard extension modules:
- Generic board support (driver)
- GFX Monochrome - Monochrome  Graphic Library (service)
- GFX Monochrome - System Font (service)
- PORT - GPIO Pin Control (driver)
- SERCOM USART Serial Communications(driver)
- SYSTEM - Core System Driver (driver)
- TC - Time Counter (Driver)
- Standard serial I/O (stdio)(driver)
- FreeRTOS mini Real-Time Kernel (service)

The GUI used to communicate from the PC to the microcontroller was implemented in Java.
