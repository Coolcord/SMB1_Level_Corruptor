#include "binarymanipulator.h"
#include <iterator>
#include <string>
#include <stdexcept>
#include <vector>

BinaryManipulator::BinaryManipulator()
{

}

std::string BinaryManipulator::HexToBinaryString(int hex)
{
    //Make sure the byte passed in is valid
    if (hex > 0xFF)
        throw "Value cannot be greater than 0xFF!";
    else if (hex < 0x00)
        throw "Value cannot be less than 0x00!";

    std::string binary = "";
    for (int i = 128; i >= 1; i /= 2)
    {
        hex -= i;
        if (hex >= 0)
        {
            binary += "1";
        }
        else
        {
            hex += i;
            binary += "0";
        }
    }
    return binary;
}

std::vector<bool> BinaryManipulator::HexToBitVector(int hex)
{
    std::vector<bool> bits;
    for (int i = 0; i < 8; i++)
    {
        bits.push_back(false);
    }
    //Make sure the byte passed in is valid
    if (hex < 0x0 || hex > 0xFF)
    {
        throw "A value between 0x0 and 0xF is expected";
    }

    for (int i = 128, j = 0; i >= 1; i /= 2, ++j)
    {
        hex -= i;
        if (hex >= 0)
        {
            bits.at(j) = true;
        }
        else
        {
            hex += i;
            bits.at(j) = false;
        }
    }
    return bits;
}

std::vector<bool> BinaryManipulator::HexDigitToBitVector(int hexDigit)
{
    std::vector<bool> bits;
    for (int i = 0; i < 4; i++)
    {
        bits.push_back(false);
    }
    //Make sure the byte passed in is valid
    if (hexDigit < 0x0 || hexDigit > 0xF)
    {
        throw "A value between 0x0 and 0xF is expected";
    }

    for (int i = 8, j = 0; i >= 1; i /= 2, ++j)
    {
        hexDigit -= i;
        if (hexDigit >= 0)
        {
            bits.at(j) = true;
        }
        else
        {
            hexDigit += i;
            bits.at(j) = false;
        }
    }
    return bits;
}

int BinaryManipulator::BinaryStringToHex(const std::string &binary)
{
    int value = 0;
    int j = 1;
    for (int i = binary.length() - 1; i >= 0; i--)
    {
        if (binary[i] == '1')
            value += j;
        j *= 2;
    }
    return value;
}

int BinaryManipulator::BitVectorToHex(std::vector<bool> &bits, int start, int end)
{
    if (bits.size() >= end)
        throw "End cannot be greater than the bit vector size!";
    else if (start < 0)
        throw "Start must be greater than 0!";
    int value = 0;
    int j = 1;
    for (int i = end; i >= start; --i)
    {
        if (bits.at(i) == true)
            value += j;
        j *= 2;
    }
    return value;
}

int BinaryManipulator::BitVectorToHex(std::vector<bool> &bits)
{
    return BitVectorToHex(bits, 0, (bits.size() - 1));
}

std::string BinaryManipulator::BitVectorToString(std::vector<bool> &bits)
{
    std::string binary = "";
    for (std::vector<bool>::iterator itor = bits.begin(); itor != bits.end(); ++itor)
    {
        if (*itor)
            binary += "1";
        else
            binary += "0";
    }
    return binary;
}

void BinaryManipulator::WriteHexDigitToBitVector(std::vector<bool> &bits, unsigned int start, int hexDigit)
{
    WriteHexDigitToBitVector(bits, start, hexDigit, 0, 3);
}

void BinaryManipulator::WriteHexDigitToBitVector(std::vector<bool> &bits, unsigned int start, int hexDigit, unsigned int hexStart, unsigned int hexEnd)
{
    if (start > bits.size())
        throw "Start must be a proper index";
    else if (hexDigit < 0x0 || hexDigit > 0xF)
        throw "A hex digit is expected";
    else if (hexStart > 3 || hexEnd > 3)
        throw "Start and end must be between 0 and 3";
    std::vector<bool> hexDigitBits = HexDigitToBitVector(hexDigit);
    if (start + hexDigitBits.size() > bits.size())
        throw "Cannot write outside of the bit array";
    for (unsigned int i = start, j = hexStart; j <= hexEnd; i++, j++)
    {
        bits.at(i) = hexDigitBits.at(j);
    }
}

void BinaryManipulator::WriteByteToBitVector(std::vector<bool> &bits, unsigned int start, int hex)
{
    if (start > bits.size())
        throw "Start must be a proper index";
    else if (hex < 0x00 || hex > 0xFF)
        throw "A hex digit is expected";
    std::vector<bool> hexBits = HexToBitVector(hex);
    if (start + hexBits.size() > bits.size())
        throw "Cannot write outside of the bit array";
    for (unsigned int i = start, j = 0; i < start + bits.size(); ++i, ++j)
    {
        bits.at(i) = hexBits.at(j);
    }
}
