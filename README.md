# arduino-heater-relay
Arudino connected heater relay for 2-wire heater system
Uses the SEEED relay shield v2.1

A basic example of a relay connected to the Arduino which can receive the following commands over the serial port - 

# = Read sensor setting
@ = Switch relay OFF if ON, and ON if OFF
! = Read temperature from BMP180 sensor

Included files - 

FOR ARDUINO
heater-relay.ino = Arduino script which communicates over the serial TX/RX ports, accepts relay commands, and reads state and temperature
BMP180.zip = BMP180 library for Arduino

FOR DEVICE CONNECTED TO SERIAL TX/RX (Rasp Pi, BBB, etc.)
heater.php = Basic web page to read and write relay status and temperature, uses exec python scripts
read-state.py = Sends serial command to read relay state from Arduino
write-state.py = Switches relay OFF if ON, and ON if OFF.  Call read-state first to determine whether to call write-state
read-temp.py = Reads temperature from BMP180 sensor


Basic Setup
1. Attach SEEED relay shield v2.1
2. Load Arduino Uno with include ino
3. Attach BMP180 sensor to Arduino (3.3V to VCC, GND to GND, SCL to A5, SDA to A4)
4. Connect basic button to GND and D2 and LED to GND and D13
5. Attach 2 heater wires to COM1 and NO1 ports on the relay shield
6. Load python scripts to Raspi Pi home directory (e.g. /home/pi/read-state.py, etc.)
7. Install Apache and PHP5 if needed and copy heater.php to /var/www/html (or web root directory)
8. Disable tty ports on Linux to allow use of AMA0 port (remove ttyAMA0 line in /boot/cmdline.txt)
9. In my case, I had to add www-data to the sudoers file to allow access to the serial ports (sudo visudo, add line below to the end:)
www-data ALL=(ALL) NOPASSWD: ALL
10. Restart Pi and you should have a web enabled heater relay with temperature reading