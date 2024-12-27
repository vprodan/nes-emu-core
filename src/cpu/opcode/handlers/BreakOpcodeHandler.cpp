#pragma once
#include <memory>
#include "OpcodeHandler.hpp"
#include "cpu/CPU.cpp"
#include "cpu/register/StatusRegister.cpp"
using namespace std;

class BreakOpcodeHandler : public OpcodeHandler
{
public:
    using OpcodeHandler::OpcodeHandler;

protected:
    int handle(CPU &cpu) const override
    {
        cpu.PC.increment(); // Increment PC before pushing to stack
        
        cpu.S.push(cpu.PC.read() >> 8); // Push PC high byte
        cpu.S.push(cpu.PC.read()); // Push PC low byte

        cpu.S.push(cpu.P.read() | Break); // Push status register to stack

        cpu.P.set(InterruptDisable); // Set interrupt disable flag

        cpu.PC.write(cpu.bus.read(0xFFFE) | (cpu.bus.read(0xFFFF) << 8)); // Set PC to interrupt vector

        return cycles;
    }
};
