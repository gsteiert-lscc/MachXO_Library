# Lattice MachXO Arduino Library #

This is an Arduino driver library for accessing the configuration port of the Lattice [MachXO2](http://www.latticesemi.com/en/Products/FPGAandCPLD/MachXO2)/[MachXO3](http://www.latticesemi.com/en/Products/FPGAandCPLD/MachXO3) through I2C or SPI.
This implements the procedures outlined in the Programming and Configuration Usage Guides:
[MachXO2 Programming and Configuration Usage Guide](http://www.latticesemi.com/view_document?document_id=39085)
[MachXO3 Programming and Configuration Usage Guide](http://www.latticesemi.com/view_document?document_id=50123)

## About this Driver ##

To access the Lattice MachXO device, you only need the standard Wire(I2C) or SPI libraries.  However, the size of the images for the MachXO devices are larger than the integrated storage of some microcontrollers so the load function reads the data from a file using the SdFat library.  

To use this library, copy this directory and all the contents into the "libraries" directory where Arduino keeps all your installed libraries (typically ~/Documents/Aduino/libraries).

## MachXO2/3 Hex Files ##

To manage file size and for ease of parsing, the load function uses the hex file format.  The .jed Jedec files can be translated into .hex format using the Lattice Diamond Deployment Tool.

## Examples ##

Examples are provided that demonstrate how to load a hex file into the MachXO device.  These examples get the file from an external flash device as is available on the Adafruit "Express" boards like the [Feather M4 Express](https://www.adafruit.com/product/3857) or [Feather nRF52840 Express](https://www.adafruit.com/product/4062).  This configuration is becoming very popular since the extra storage makes it easier to implement CircuitPython.  For boards without SPI flash, an SD card can be used to store the files.  The TinyUSB libray is used so that files can be copied to the board just like a USB thumb drive.  

### Example Hex Files ###

Some example hex files are provided for demonstration purposes.

* tiny256.hex is an example for the [TinyFPGA AX1](https://store.tinyfpga.com/products/tinyfpga-a1) that blinks the LED
* xo3starter.hex is an example for the [MachXO3LF Starter Kit](http://www.latticesemi.com/en/Products/DevelopmentBoardsAndKits/MachXO3LFStarterKit) that applies a counter to the LEDs controlled by the switches.

## SPI Support ##

It is intended to add SPI support to this library in future revisions.  Until that is fully implemented, an example sketch is provided that implements the functions locally.  
