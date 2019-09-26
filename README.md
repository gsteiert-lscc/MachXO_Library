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

## Notes on sharing I2C pins ##

To make best use of the pins, it is convenient to use the I2C pins for both configuration and user interface.  This can be done, but it requires access to the PROGRAMN pin, because loading an image that uses the I2C configuration pins will disable I2C configuration.  To upate an image that uses the I2C configuration pins, simply hold PROGRAMN low to clear the image and activate I2C configuration.

The simplest way to achieve this is to connect a GPIO to PROGRAMN so that you can select configuration or user mode by setting the pin low or high, respectively.

If you cannot control PROGRAMN programatically with a GPIO, you should provide a manual method of control such as a button or jumper to select configuration mode.  Please remember that you may need to hold this low for the duration of programming.

Toggling PROGRAMN low will reload the image so this pin also makes a very useful reset for the device.

## Examples ##

Examples are provided that demonstrate how to load a hex file into the MachXO device.  These examples get the file from an external flash device as is available on the Adafruit "Express" boards like the [Feather M4 Express](https://www.adafruit.com/product/3857) or [Feather nRF52840 Express](https://www.adafruit.com/product/4062).  This configuration is becoming very popular since the extra storage makes it easier to implement CircuitPython.  For boards without SPI flash, an SD card can be used to store the files.  The TinyUSB libray is used so that files can be copied to the board just like a USB thumb drive.  

### machXOdemo ###

This demonstration can be used with I2C or SPI.  Select the interface you wish to use by which of lines 69-71 is not commented out.  A simple terminal interface is provided to test the different commands.

### i2c_term ###

This is similar to machXOdemo, except that it includes generic I2C commands in the terminal interface so that it can also be used for interfacing with your own user code running on the FPGA, or with other I2C devices on the same bus.

### Example Hex Files ###

Some example hex files are provided in the examples/hex_files folder for demonstration purposes.

* tiny256.hex is an example for the [TinyFPGA AX1](https://store.tinyfpga.com/products/tinyfpga-a1) that blinks the LED
* xo3starter.hex is an example for the [MachXO3LF Starter Kit](http://www.latticesemi.com/en/Products/DevelopmentBoardsAndKits/MachXO3LFStarterKit) that applies a counter to the LEDs controlled by the switches
