JuJe_Arduino_repo
=================

This is an Arduino project who permits to develop our communication between to card.

Initial Specification:

Communication with 3 pins : CS, CLK and DATA
Communication process : 
CS = 0, DATA is sent when the CLK is equal to '1'.

We can send this frame to an other Arduino board in order to activate led or bip for example.

For the moment, the frame contains 3 bits : 2 bits for the hardware and 1 bit for the command.
