# DBS_DevBoardSampler
Sample and save analog and digital pins from your dev board (currently only Teensy4.0)

## Limitations
- Limited to 10 bytes of data on Teensy 4.0
- Therefore limited to max. 5 adcs at 16 bit or 10 adcs at 8 bit
- Currently adc results can only start at bit 0 of a byte, so 12 bit for example wont allow more readings
- All adcs are configured to the same bit depth

## Reference
### Teensy 4.0 Pinout
Upside:

![Teensy 4.0 Pinout upper side](https://forum.pjrc.com/teensy40_pinout1.png)

Downside:

![Teensy 4.0 Pinout down side](https://forum.pjrc.com/teensy40_pinout2.png)