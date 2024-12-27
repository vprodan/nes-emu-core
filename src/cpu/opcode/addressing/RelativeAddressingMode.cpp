#pragma once
#include <memory>
#include "cpu/opcode/addressing/AddressingMode.hpp"
#include "Utils.cpp"
using namespace std;

class RelativeAddressingMode : public AddressingMode
{
public:
    unique_ptr<ResolvedAddress> resolve(CPU &cpu) const override
    {
        auto crossedBoundary = false;
        auto offset = cpu.bus.read(cpu.PC.read());     // Fetch the signed offset
        auto signedOffset = Utils::signOffset(offset); // Convert the offset to a signed 8-bit value

        cpu.PC.increment();

        auto address = cpu.PC.read();
        auto oldAddress = address;

        address += signedOffset;

        if (Utils::checkPageBoundaryCross(oldAddress, address))
        {
            crossedBoundary = true;
        }

        return make_unique<ResolvedAddress>(address, crossedBoundary);
    }
};