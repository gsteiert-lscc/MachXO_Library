// MIT License
//
// Author(s): Greg Steiert
// Copyright (c) 2019 Lattice Semiconductor Corporation
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

/* This is a library for programming the Lattice MachXO2/3 device 
   through I2C or SPI.

*/

#ifndef __MachXO_H__
#define __MachXO_H__

#include "Arduino.h"
#include "SdFat.h"
#include <Wire.h>
#include <SPI.h>

#define MACHXO_I2C_ADDR       0x40
#define MACHXO_SPI_SPEED      500000

#define DBG_MSG               if (_verbose) Serial

//  Forward declarations of Wire and SPI for board/variant combinations that don't have a default 'Wire' or 'SPI' 
extern TwoWire Wire;  /**< Forward declaration of Wire object */
extern SPIClass SPI;  /**< Forward declaration of SPI object */

// Erase Flag Enumeration
enum {
    MACHXO_ERASE_SRAM = (1 << 16),
    MACHXO_ERASE_FEATURE_ROW = (1 << 17),
    MACHXO_ERASE_CONFIG_FLASH = (1 << 18),
    MACHXO_ERASE_UFM = (1 << 19),
};

// Class Definition for MachXO Programming library
class MachXO {
public:
    MachXO(TwoWire *theWire = &Wire, uint8_t theAddr = MACHXO_I2C_ADDR);
    MachXO(int8_t cspin, SPIClass *theSPI = &SPI);
    MachXO(int8_t cspin, int8_t mosipin, int8_t misopin, int8_t sckpin);
    void begin(uint8_t verbose = 0);
    uint32_t readDeviceID(uint8_t *ibuf);
    uint32_t readUserCode(uint8_t *ibuf);
    uint32_t readStatus(uint8_t *ibuf);
    uint32_t readFeatureBits(uint8_t *ibuf);
    uint32_t readFeatureRow(uint8_t *ibuf);
    uint32_t readOTPFuses(uint8_t *ibuf);
    uint32_t readFlash(uint8_t *ibuf);
    uint32_t readUFM(uint8_t *ibuf);
    uint32_t eraseUFM();
    uint32_t erase(uint32_t flags);
    uint32_t enableConfigTransparent();
    uint32_t enableConfigOffline();
    uint32_t isBusy();
    uint32_t waitBusy();
    uint32_t resetConfigAddress();
    uint32_t resetUFMAddress();
    uint32_t setConfigAddress(uint32_t page);
    uint32_t setUFMAddress(uint32_t page);
    uint32_t programPage(uint8_t *obuf);
    uint32_t programDone();
    uint32_t refresh();
    uint32_t wakeup();
    uint32_t loadHex(FatFile hexFile);
//    uint32_t loadHex(FatFileSystem *fatfs, char *fileName);

private:
    TwoWire *_wire; /**< Wire object */
    SPIClass *_spi; /**< SPI object */
    uint8_t _verbose;
    uint8_t _i2caddr;
    uint8_t spixfer(uint8_t x);
    uint32_t cmdxfer(uint8_t *wbuf, int wcnt, uint8_t *rbuf, int rcnt);
    int8_t _cs, _mosi, _miso, _sck;
};

#endif // __MachXO_H__