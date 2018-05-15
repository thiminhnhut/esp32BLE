/*
    Copyright (c) Dung Nguyen - All Rights Reserved
 */

#include "EEPROMESP32.h"

EEPROMESP32::EEPROMESP32()
{

}

void EEPROMESP32::begin(int size)
{
    _size = size;
    EEPROM.begin(_size);
}

void EEPROMESP32::end()
{
    EEPROM.end();
}

// write value to address
bool EEPROMESP32::commit()
{
    return EEPROM.commit();
}

// write value to address
void EEPROMESP32::write(int address, byte value)
{
    EEPROM.write(address, value);
}

// read value from address
byte EEPROMESP32::read(int address)
{
    return EEPROM.read(address);
}

void EEPROMESP32::putInt(int address, int value) {
    EEPROM.put(address, value);
}

int EEPROMESP32::getInt(int address) {
    int value;
    EEPROM.get(address, value);
    return value;
}

void EEPROMESP32::putShortInt(int address, unsigned short int value) {
    EEPROM.put(address, value);
}

unsigned short int EEPROMESP32::getShortInt(int address) {
    unsigned short int value;
    EEPROM.get(address, value);
    return value;
}

void EEPROMESP32::putLong(int address, long value) {
    EEPROM.put(address, value);
}

long EEPROMESP32::getLong(int address) {
    long value;
    EEPROM.get(address, value);
    return value;
}

// write hex string to ROM
// return true if value is hex string and length is even
bool EEPROMESP32::writeHexString (int address, String value) {
    int length = value.length();
    boolean success = length % 2 == 0;
    if (success) {
        char c;
        for (int i = 0; i < length; i++) {
            c = value[i];
            if (isHexadecimalDigit(c) == false) {
                return false;
            }
        }
        byte tmp = 0;
        byte highByte = 0;
        byte lowByte = 0;
        int offset = 0;
        for (int i = 0; i < length; i++) {
            c = value[i];
            if (c >= '0' && c <= '9') {
                tmp = c - '0';
            } else if (c >= 'a' && c <= 'f') {
                tmp = c - 'a' + 10;
            } else {
                tmp = c - 'A' + 10;
            }
            if (i % 2 == 0) {
                highByte = tmp;
            } else {
                offset = i / 2;
                lowByte = tmp;
                tmp = 16 * highByte + lowByte;
                write(address + offset, tmp);
            }
        }
    }
    return success;
}

// read hex string in ROM from address to address + length
String EEPROMESP32::readHexString(int address, int numByte) {
    String result = "";
    byte tmp = 0;
    for (int i = 0; i < numByte; i++) {
        tmp = read (address + i);
        result += _converter.byteToHexString(tmp);
    }
    return result;
}

// read hex string in ROM from address to address + length
String EEPROMESP32::readHexString(int address, int numByte, char seperateChar) {
    String result = "";
    byte tmp = 0;
    for (int i = 0; i < numByte; i++) {
        tmp = read (address + i);
        if (i > 0) {
            result += seperateChar;
        }
        result += _converter.byteToHexString(tmp);
    }
    return result;
}

// use 2 bytes
void EEPROMESP32::writeInt(int address, unsigned int value) {
    byte highByte = value / 256;
    byte lowByte = value % 256;
    write (address, highByte);
    write (address + 1, lowByte);
}

// use 2 bytes
unsigned int EEPROMESP32::readInt(int address) {
    unsigned int result = 0;
    byte tmp = 0;
    for (int i = 0; i < 2; i++) {
        tmp = read(address + i);
        result = result * 256 + tmp;
    }
    return result;
}

// use 2 bytes
void EEPROMESP32::writeLong(int address, unsigned long value) {
    byte number = 0;
    unsigned long remain = value;
    for (byte i = 0; i < 4; i++) {
        number = remain % 256;
        write(address + 3 - i , number);
        remain /= 256;
    }
}

// use 4 bytes
unsigned long EEPROMESP32::readLong(int address) {
    unsigned long result = 0;
    byte tmp = 0;
    for (int i = 0; i < 4; i++) {
        tmp = read (address + i);
        result = result * 256 + tmp;
    }
    return result;
}

// use length byte
int EEPROMESP32::writeString(int address, String value) {
    if (_converter.parseAcceptedCharacterString(value) >= 0) {
        int length = value.length();
        if (length < 255) {
            byte tmp;
            for (int i = 0; i< length; i++) {
                tmp = value[i];
                write(address + i, tmp);
            }
            write(address + length, 0);
            return length + 1;
        }
    }
    return -1;
}

String EEPROMESP32::readString(int address) {
    String result = "";
    byte value;
    char c ;
    int next = address;
    while (next < _size) {
        value = read(next++);
        c = char(value);
        if (c == 0) {
            break;
        } else {
            if (_converter.isAcceptedCharacter(c)) {
                result += c;
            } else {
                result = "";
                break;
            }
        }
    }
    return result;
}

// reset Rom from - to address
void EEPROMESP32::reset(int from, int to) {
    for (int i = from; i < to; i++) {
        write (i, 255);
    }
}

void EEPROMESP32::reset(int from) {
    for (int i = from; i < _size; i++) {
        write (i, 255);
    }
}
