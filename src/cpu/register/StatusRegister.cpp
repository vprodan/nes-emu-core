#pragma once
#include <cstdint>
#include <map>
#include "cpu/register/Register.cpp"
using namespace std;

enum Status
{
    Carry = 0b00000001,
    Zero = 0b00000010,
    InterruptDisable = 0b00000100,
    Decimal = 0b00001000,
    Break = 0b00010000,
    Unused = 0b00100000,
    Overflow = 0b01000000,
    Negative = 0b10000000,
};

class StatusRegister : public Register<uint8_t>
{
public:
    StatusRegister() : Register<uint8_t>(Status::Unused) {}

    void set(Status status)
    {
        value |= status;
    }

    void clear(Status status)
    {
        value &= ~status;
    }

    bool isSet(Status status) const
    {
        return (value & status) != 0;
    }

    void setAll(const map<Status, bool> &statuses)
    {
        for (const auto &[status, enabled] : statuses)
        {
            if (enabled)
            {
                set(status);
            }
            else
            {
                clear(status);
            }
        }
    }
};