#pragma once
#include <cstdint>
#include <memory>
#include "cpu/opcode/addressing/AddressingMode.hpp"
#include "cpu/opcode/WithOperationalRegister.cpp"
#include "Utils.cpp"
using namespace std;

class AbsoluteAddressingMode : public AddressingMode, public WithOperationalRegister
{
public:
    explicit AbsoluteAddressingMode(Register<uint8_t> CPU::*operationalRegister = nullptr) : WithOperationalRegister(operationalRegister) {}

    unique_ptr<ResolvedAddress> resolve(CPU &cpu) const override
    {
        auto lo = cpu.bus.read(cpu.PC.read());
        auto hi = cpu.bus.read(cpu.PC.read() + 1);
        auto address = (hi << 8) | lo;
        auto crossedBoundary = false;

        auto reg = getOperationalRegister(cpu);
        if (reg != nullptr)
        {
            auto oldAddress = address;
            address += reg->read();

            if (Utils::checkPageBoundaryCross(oldAddress, address))
            {
                crossedBoundary = true;
            }
        }

        cpu.PC.increment(2);

        return make_unique<ResolvedAddress>(address, crossedBoundary);
    }
};