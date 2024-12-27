#pragma once
#include <cstdint>
#include "cpu/register/Register.cpp"
using namespace std;

class ProgramCounterRegister : public Register<uint16_t>
{
public:
    ProgramCounterRegister() : Register<uint16_t>(0x8000) {}

    void increment(uint16_t value = 1)
    {
        this->value += value;
    }
};