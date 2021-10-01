# GC_to_C64
Connect a GC controller into a Commodore 64/128


---DISCLAIMER---

I TAKE NO RESPONSIBILITY  AND/OR LIABILITY IF DAMAGES/LOSSES OR INJURY IS CAUSED USING THIS INFORMATION.
YOU USE THIS INFORMATION AT YOUR OWN RISK.

The original MIT liscence and disclaimer is included in main.c as a precaution.

---DISCLAIMER---

PARTS LIST

1x Raspberry Pi Pico
1x TXS0108E
5x 1N4148 Switching Diodes
1x DB9 Female connector
1x plug for GC controller. Good luck with that one.

A wire with 8 conducting lines, such as a ethernet cable should work. Soldering experience is an asset. Heatshrink is nice but not required.


A few notes about this design.

This is designed to work with a Raspberry Pi Pico. It does not use PIO instead relying on NOPS for cycle specific timing.

Open collector I/O holds a data line high for logical 0 and pulls to ground for a logical 1. This is very important to note for this design and the code that goes with it. You should never put voltage on open collector I/O as a precaution.

As far as I understand, the GC controller uses an open collector I/O and is suppose to use 3.43 volts, however it has been my experience it is perfectly happy with 3.3V. The timing has been tested against an oscilloscope and it shouldn't be able to drive the data line to 3.3V when the GC controller is driving the line low to ground. Putting a voltage onto an open collector I/O is bad and can damage parts. As a precaution, I've set the drive current to 2 millamps and then have the code immediately after set a pull up resistor. The data sheet does not specify if this turns off the drive current on the GPIO. The pull up resistor is something around 60K ohm and should only allow approximately 55 microamps when holding the line at high, 3.3V. When the GC controller is idle, both it and the Raspberry Pi Pico will hold the line at 3.3V and no current should be able to flow along the dataline. I've been using it this way without any issue for awhile now.

the Commodore 64/128 uses open collector I/O. The level converters in this design do not play nice with this and can damage your equipment. I had used 5x 1N4148 switching diodes to compensate for this. They only allow current to flow in one direction, out of the Commodore, protecting the (extremely) difficult to replace hardware contained within. The level converter is in place to ensure the the GPIO on the Raspberry Pi only ever sees 3.3V at max, protecting its pins as well.

The joystick port of the Commodore is documented to only allowed up to 100mA to be drawn from the joysick port. I have looked at the circuit schematics and on the board itself and have verified it ties directly into the 5V rail of the version I own. This might be different on different machines. I have also placed a multimeter in the circuit and verified it only draws 25mA average on load.

This circuit has also been tested and works with an original Atari 2600. It does not work with an Atari Flashback 8.

Please also do not plug in the Raspberry Pi Pico into a usb port to program it while this circuit is also plugged into a Commodore. It will try to power the 5V rail of the Commodore causing a power surge on the USB port. This was learned by accident. (whoopsie)

Although I've taken many precautions to ensure the safety of equipment and have even tested this circuit extensively, I am only human, I might has missed something or coded something incorrectly. It is your responsbility to ensure the accuracy and safety of the information provided.

---DISCLAIMER---

I TAKE NO RESPONSIBILITY  AND/OR LIABILITY IF DAMAGES/LOSSES OR INJURY IS CAUSED USING THIS INFORMATION.
YOU USE THIS INFORMATION AT YOUR OWN RISK.

The original MIT liscence and disclaimer is included in main.c as a precaution.

---DISCLAIMER---

With that said, please be diligent, look over the code, check the circuit, and ensure you are being safe.
