#pragma once
#include <cstdint>
using namespace std;

namespace Utils
{
    inline bool checkPageBoundaryCross(uint16_t oldAddress, uint16_t newAddress)
    {
        return (oldAddress & 0xff00) != (newAddress & 0xff00);
    }

    inline bool isZero(uint8_t value)
    {
        return value == 0;
    }

    inline bool isNegative(uint8_t value)
    {
        return (value & 0x80) != 0;
    }

    inline bool isCarryAdd(uint16_t value)
    {
        return (value & 0x100) != 0;
    }

    inline bool isOverflowArith(uint8_t a, uint8_t b, uint16_t result)
    {
        return ((a ^ result) & (b ^ result) & 0x80) != 0;
    }

    inline bool isOverflowBit(uint8_t value)
    {
        return (value & 0x40) != 0;
    }

    inline bool isCarrySub(uint16_t value)
    {
        return (value & 0x100) == 0;
    }

    inline bool isCarryCompare(uint16_t value)
    {
        return (value & 0x100) == 0;
    }

    inline bool isCarryRight(uint8_t value)
    {
        return (value & 0x01) != 0;
    }

    inline bool isCarryLeft(uint8_t value)
    {
        return (value & 0x80) != 0;
    }

    inline int signOffset(uint8_t offset)
    {
        return offset > 127 ? offset - 256 : offset;
    }
} // namespace utils