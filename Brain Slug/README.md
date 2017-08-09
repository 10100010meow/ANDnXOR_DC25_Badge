# Brain Slug #

This was a last minute addon we made for our badge this year. It's a basic PCB with ATtiny85 and 5x WS2812B LEDs.

## BOM ##

 * 1x ATtiny85-20SU
 * 5x WS2812B LEDs
 * 1x 220 ohm 0805 Resistor
 * 1x 4.7k ohm 0805 Resistor
 * 1x 10k ohm 0805 Resistor
 * 1x 1uF 0805 Capacitor

## Assembly ##

The PCB was designed to be soldered easily by hand. Only a few surface mount parts. Note the rotation of the WS2812B LEDs changes.

_The footprint used for the ATtiny85 barely fits, care should be taken when soldering to ensure all pins are connected_

## Programming ##

The brain slug contains a 10 pin ISP header. Use a USBASP (few bucks on Ebay) to flash the bootloader and firmware from Arduino. _Arduino 1.6.9 was used to program our brain slugs_. Bootloader should be set to 16Mhz PLL. The brain slug can be powered by the USBASP.

## Dependencies ##

 * ATtiny Arduino Core
 * Adafruit NeoPixel Library

## Todo ##

May never get to this, but if we revisit the project:

 * Fix ATtiny85 footprint
 * Put MCU into deep sleep during delays
 * Dim LEDs slightly
 * Change ISP header to TagConnect 2050 to clean up design
 * Change WS2812B LEDs to have same rotation
