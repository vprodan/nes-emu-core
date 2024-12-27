#pragma once
#include <memory>
#include "OpcodeHandler.hpp"
#include "cpu/CPU.cpp"
#include "cpu/register/StatusRegister.cpp"
using namespace std;

class StatusFlagOpcodeHandler : public OpcodeHandler
{
private:
    Status flag;
    bool setFlag;

public:
    StatusFlagOpcodeHandler(int cycles, Status flag, bool setFlag)
        : OpcodeHandler(cycles), flag(flag), setFlag(setFlag) {}

protected:
    int handle(CPU &cpu) const override
    {
        if (setFlag)
        {
            cpu.P.set(flag);
        }
        else
        {
            cpu.P.clear(flag);
        }

        return cycles;
    }
};
