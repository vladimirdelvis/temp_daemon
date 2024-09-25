# Temperature Daemon
This project will get the temperature of the CPU and GPU from your operating system and send it to the Arduino board via the serial port.
The I2C LCD connected Arduino board displays these temperatures on connected LCD screen.

This project only works on Linux with an nVidia graphics card. Since the source code of this project may not match your sensor information, there is a possibility that the project may not work. It is recommended to edit the source code.

Required packages/libraries
libserialport
lm_sensors
nvidia-utils
cuda (make)
LiquidCrystal_I2C (for Arduino)
