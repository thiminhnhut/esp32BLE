/*
    Copyright (c) Dung Nguyen - All Rights Reserved
 */

#ifndef EEPROMESP32_h
#define EEPROMESP32_h

#include <EEPROM.h>
#include "Converter.h"

class EEPROMESP32 {
  private:
    int _size;
    Converter _converter;
  public:

    EEPROMESP32();

    void begin(int size);
    void end();
    bool commit();

    // value -> address
    void write(int address, byte value);
    byte read(int address);

    void putInt(int address, int value);
    int getInt(int address);

    void putShortInt(int address, unsigned short int value);
    unsigned short int getShortInt(int address);

    void putLong(int address, long value);
    long getLong(int address);

    // write hex string to ROM
    // return true if hex string length is even
    bool writeHexString (int address, String value);
    // read hex string in ROM from address to address + length
    String readHexString(int address, int numByte, char seperateChar);
    String readHexString(int address, int numByte);

    // use 2 byte
    void writeInt(int address, unsigned int value);
    unsigned int readInt(int address);

    // use 4 byte
    void writeLong(int address, unsigned long value);
    unsigned long readLong(int address);

    // use length byte
    int writeString(int address, String value);
    String readString(int address);

    // reset rom from address (from) to address (to)
    void reset(int from, int to);

    void reset(int from);
};

#endif
