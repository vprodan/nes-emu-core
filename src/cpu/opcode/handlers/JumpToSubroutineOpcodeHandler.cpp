#pragma once
#include <memory>
#include "OpcodeHandler.hpp"
#include "cpu/CPU.cpp"
#include "Utils.cpp"
using namespace std;

class JumpToSubroutineOpcodeHandler : public OpcodeHandler
{
public:
    using OpcodeHandler::OpcodeHandler;

protected:
    int handle(CPU &cpu, unique_ptr<ResolvedAddress> &resolvedAddress) const override
    {
        auto returnAddress = cpu.PC.read() - 1;
        uint8_t hi = returnAddress >> 8;
        uint8_t lo = returnAddress;

        cpu.S.push(hi);
        cpu.S.push(lo);

        cpu.PC.write(resolvedAddress->address);

        return cycles;
    }
};
