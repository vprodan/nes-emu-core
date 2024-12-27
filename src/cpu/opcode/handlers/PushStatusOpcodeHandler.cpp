#pragma once
#include "OpcodeHandler.hpp"
#include "cpu/CPU.cpp"
#include "cpu/register/StatusRegister.cpp"

class PushStatusOpcodeHandler : public OpcodeHandler
{
public:
    using OpcodeHandler::OpcodeHandler;

protected:
    int handle(CPU &cpu) const override
    {
        cpu.S.push(cpu.P.read() | Status::Break | Status::Unused);
        
        return cycles;
    }
};
