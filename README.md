# Automatic-Water-Tank-Filler
This code is designed to fill the base water tank and roof tank. Mainly tested with base tank (as given in code). Code is written for Arduino Mega 2560 so you ll have to take care of the pin numbers.

Arduino Mega board uses 5v relay board to actuate bigger main 220v relays.

Code heavily relies on milis() function to execute multi-tasking.

You can set various times for which a particular action takes place like how long to wait before turning on the motor if base tank full signal is activated? How long to wait if motor is running but there is no water supply? How long to wait before rechecking if there is water supply back in the line?  etc

Hardware components include: A 5v relay board, a water sensor to sense if the tank is full and a water flow sensor based on hall effect sensor.
