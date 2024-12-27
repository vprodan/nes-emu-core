#pragma once
#include <memory>
#include "OpcodeHandler.hpp"
#include "cpu/CPU.cpp"
#include "Utils.cpp"
using namespace std;

class BranchStatusOpcodeHandler : public OpcodeHandler
{
public:
    BranchStatusOpcodeHandler(int cycles, AddressingMode *addressingMode, Status status, bool isSet)
        : OpcodeHandler(cycles, addressingMode), status(status), isSet(isSet) {}

protected:
    Status status;
    bool isSet;

    int handle(CPU &cpu, unique_ptr<ResolvedAddress> &resolvedAddress) const override
    {
        auto isSet = cpu.P.isSet(status);

        if (this->isSet == isSet)
        {
            auto signedOffset = Utils::signOffset(resolvedAddress->address);

            cpu.PC.write(cpu.PC.read() + signedOffset);

            return cycles + 1 + (resolvedAddress->crossedBoundary ? 1 : 0);
        }

        return cycles;
    }
};
