#pragma once
#include <cstdint>
#include "cpu/register/Register.cpp"
#include "cpu/CPUBus.cpp"
using namespace std;

class StackRegister : public Register<uint8_t>
{
private:
    CPUBus &bus;
    uint8_t value;

public:
    StackRegister(CPUBus &bus) : Register<uint8_t>(0xfd), bus(bus) {}

    void push(uint8_t value)
    {
        uint16_t address = 0x0100 + this->value;
        bus.write(address, value);
        this->value = this->value - 1;
    }

    uint8_t pop()
    {
        this->value = this->value + 1;
        uint16_t address = 0x0100 + this->value;

        return bus.read(address);
    }
};