#pragma once
#include "OpcodeHandler.hpp"
#include "cpu/CPU.cpp"
#include "cpu/register/StatusRegister.cpp"

class PullStatusOpcodeHandler : public OpcodeHandler
{
public:
    using OpcodeHandler::OpcodeHandler;

protected:
    int handle(CPU &cpu) const override
    {
        cpu.P.write(cpu.S.pop());
        cpu.P.clear(Status::Break);
        
        return cycles;
    }
};
