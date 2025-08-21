# GloveKeyboard
Repository for software/instructions, of said Glove Keyboard

This project's story:
- Tried bluetooth HID communication to PC (failed due to bluetooth module not compatible with HID data)
- Tried Raspberry Pi with rest the same (failed due to PC not detecting input data properly, despite the connection being present)
- Modified RPi device, to use WiFi communication, with custom software on PC running simultaneously (working, tensometers are not good for being under changing force of fingers, connections easily break)