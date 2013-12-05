#ifndef BINARYMANIPULATOR_H
#define BINARYMANIPULATOR_H

#include <string>
#include <vector>

namespace BinaryManipulator
{
    std::string HexToBinaryString(int hex);
    std::vector<bool> HexToBitVector(int hex);
    std::vector<bool> HexDigitToBitVector(int hexDigit);
    int BinaryStringToHex(const std::string &binary);
    int BitVectorToHex(std::vector<bool> bits, int start, int end);
    int BitVectorToHex(std::vector<bool> bits);
    std::string BitVectorToString(std::vector<bool> &bits);
    void WriteHexDigitToBitVector(std::vector<bool> &bits, unsigned int start, int hexDigit);
    void WriteHexDigitToBitVector(std::vector<bool> &bits, unsigned int start, int hexDigit, unsigned int hexStart, unsigned int hexEnd);
    void WriteByteToBitVector(std::vector<bool> &bits, unsigned int start, int hex);
}

#endif // BINARYMANIPULATOR_H
