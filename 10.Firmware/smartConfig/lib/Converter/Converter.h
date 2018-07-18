/*
    Copyright (c) Dung Nguyen - All Rights Reserved
 */

#ifndef Converter_h
#define Converter_h

#include <Arduino.h>

class Converter {
  public:

    Converter();

    int parseDateString(String inputString);

    bool isHexString(String inputString, int length);

    bool isNumberString(String inputString, int length);

    bool isAcceptedCharacter(char c);

    int parseAcceptedCharacterString(String inputString);

    String byteToString (byte value, int length);

    String intToString (unsigned int value, int length);

    String byteToHexString (byte value);

    byte hexStringToByte (String value);

    String longToHexString (unsigned long value);

    unsigned long hexStringToLong (String value);

    unsigned long decimalStringToLong (String value);

};
#endif
