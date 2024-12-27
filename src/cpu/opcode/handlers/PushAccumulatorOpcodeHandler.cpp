#pragma once
#include "OpcodeHandler.hpp"
#include "cpu/CPU.cpp"

class PushAccumulatorOpcodeHandler : public OpcodeHandler
{
public:
    using OpcodeHandler::OpcodeHandler;

protected:
    int handle(CPU &cpu) const override
    {
        cpu.S.push(cpu.A.read());
        
        return cycles;
    }
};
