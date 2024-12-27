#pragma once
#include <memory>
#include <stdexcept>
#include "cpu/CPU.cpp"
#include "cpu/opcode/addressing/AddressingMode.hpp"
using namespace std;

class OpcodeHandler
{
protected:
    int cycles;
    AddressingMode *addressingMode;

public:
    virtual ~OpcodeHandler() = default;

    explicit OpcodeHandler(int cycles, AddressingMode *addressingMode = nullptr)
        : cycles(cycles), addressingMode(addressingMode) {}

    int invoke(CPU &cpu) const {
        auto resolvedAddress = addressingMode ? addressingMode->resolve(cpu) : nullptr;

        return (resolvedAddress != nullptr) ? handle(cpu, resolvedAddress) : handle(cpu);
    }

protected:
    virtual int handle(CPU &cpu, unique_ptr<ResolvedAddress> &resolvedAddress) const
    {
        throw runtime_error("handle(CPU&, unique_ptr<ResolvedAddress>&) not implemented");
    }

    virtual int handle(CPU &cpu) const
    {
        throw runtime_error("handle(CPU&) not implemented");
    }
};