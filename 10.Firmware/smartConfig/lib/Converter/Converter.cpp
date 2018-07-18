/*
    Copyright (c) Dung Nguyen - All Rights Reserved
 */

#include "Converter.h"

Converter::Converter() {

}

int Converter::parseDateString(String inputString) {
    if (inputString.length() != 6) {
        return -1;
    }
    int year = inputString.substring(0,2).toInt();
    if (year < 0 || year > 99) {
        return -1;
    }
    int month = inputString.substring(2,4).toInt();
    if (month > 12 || month < 1) {
        return -1;
    }
    int day = inputString.substring(4,6).toInt();
    if (day > 31 || day < 1) {
        return -1;
    }
    return year + month + day;
}

bool Converter::isHexString(String inputString, int length) {
    bool result = inputString.length() == length;
    if (result) {
        char c;
        for (int i = 0; i < length; i++) {
            c = inputString[i];
            if (isHexadecimalDigit(c) == false) {
                result = false;
                break;
            }
        }
    }
    return result;
}

bool Converter::isNumberString(String inputString, int length) {
    bool result = inputString.length() == length;
    if (result) {
        char c;
        char zero = '0';
        char nine = '9';
        for (int i = 0; i < length; i++) {
            c = inputString[i];
            if (c < zero || c > nine) {
                result = false;
                break;
            }
        }
    }
    return result;
}

bool Converter::isAcceptedCharacter(char c) {
    return c >= 32 && c <= 126;
}

int Converter::parseAcceptedCharacterString(String inputString) {
    char c;
    int result = 0;
    int length = inputString.length();
    for (int i = 0; i < length; i++) {
        c = inputString[i];
        if (isAcceptedCharacter(c)) {
            result += c;
        } else {
            result = -1;
            break;
        }
    }
    return result;
}

String Converter::byteToString (byte value, int length) {
    String result = "";
    if (length > 0) {
        String tmpStr = "";
        tmpStr += value;
        int tmpLength = tmpStr.length();
        if (tmpLength <= length) {
            for (int i = tmpLength; i < length; i++) {
                result += "0";
            }
            result += value;
        } else {
            result = tmpStr.substring(tmpLength - length, tmpLength);
        }
    } else {
        result = "";
    }
    return result;
}

String Converter::intToString (unsigned int value, int length) {
    String result = "";
    if (length > 0) {
        String tmpStr = "";
        tmpStr += value;
        int tmpLength = tmpStr.length();
        if (tmpLength <= length) {
            for (int i = tmpLength; i < length; i++) {
                result += "0";
            }
            result += value;
        } else {
            result = tmpStr.substring(tmpLength - length, tmpLength);
        }
    } else {
        result = "";
    }
    return result;
}

String Converter::byteToHexString (byte value) {
    int length = 2;
    String result = "";
    String tmp = String (value, HEX);
    int strLength = tmp.length();
    int i = 0;
    for (i = 0; i < length - strLength; i++) {
        result += '0';
    }
    for (i = 0; i < strLength; i++) {
        char tmpChar = tmp[i];
        if (tmpChar < '0' || tmpChar > '9') {
            tmpChar += 'A' - 'a';
        }
        result += tmpChar;
    }
    return result;
}

byte Converter::hexStringToByte (String value) {
    byte result = 0;
    int tmpLength = value.length();
    if (tmpLength == 2) {
        int tmpByte;
        char tmpC;
        for (int i = 0; i < tmpLength; i++) {
            tmpC = value[i];
            if (tmpC >= '0' && tmpC <= '9') {
                tmpByte = tmpC - '0';
            } else if (tmpC >= 'a' && tmpC <= 'f') {
                tmpByte = tmpC - 'a' + 10;
            } else if (tmpC >= 'A' && tmpC <= 'F') {
                tmpByte = tmpC - 'A' + 10;
            } else {
                return 0;
            }
            result = 16 * result + tmpByte;
        }
    }
    return result;
}

String Converter::longToHexString (unsigned long value) {
    String result = "";
    String tmp = String (value, HEX);
    int length = tmp.length();
    for (int i = 0; i < length; i++) {
        char tmpChar = tmp[i];
        if (tmpChar < '0' || tmpChar > '9') {
            tmpChar += 'A' - 'a';
        }
        result += tmpChar;
    }
    return result;
}

unsigned long Converter::hexStringToLong (String value) {
    unsigned long result = 0;
    int tmpLength = value.length();
    if (tmpLength <= 8) {
        int tmpByte;
        char tmpC;
        for (int i = 0; i < tmpLength; i++) {
            tmpC = value[i];
            if (tmpC >= '0' && tmpC <= '9') {
                tmpByte = tmpC - '0';
            } else if (tmpC >= 'a' && tmpC <= 'f') {
                tmpByte = tmpC - 'a' + 10;
            } else if (tmpC >= 'A' && tmpC <= 'F') {
                tmpByte = tmpC - 'A' + 10;
            } else {
                return 0;
            }
            result = 16 * result + tmpByte;
        }
    }
    return result;
}

unsigned long Converter::decimalStringToLong (String value) {
    unsigned long result = 0;
    int tmpLength = value.length();
    int tmpByte;
    char tmpC;
    for (int i = 0; i < tmpLength; i++) {
        tmpC = value[i];
        if (tmpC >= '0' && tmpC <= '9') {
            tmpByte = tmpC - '0';
        } else {
            return 0;
        }
        result = 10 * result + tmpByte;
    }
    return result;
}
