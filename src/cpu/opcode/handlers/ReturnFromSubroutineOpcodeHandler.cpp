#pragma once
#include <memory>
#include "OpcodeHandler.hpp"
#include "cpu/CPU.cpp"
using namespace std;

class ReturnFromSubroutineOpcodeHandler : public OpcodeHandler
{
public:
    using OpcodeHandler::OpcodeHandler;

protected:
    int handle(CPU &cpu) const override
    {
        auto lo = cpu.S.pop(); // Pop low byte of PC
        auto hi = cpu.S.pop(); // Pop high byte of PC

        cpu.PC.write((hi << 8) | lo); // Restore PC

        cpu.PC.increment();

        return cycles;
    }
};
