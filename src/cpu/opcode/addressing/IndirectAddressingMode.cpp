#pragma once
#include <cstdint>
#include <memory>
#include "cpu/opcode/addressing/AddressingMode.hpp"
#include "cpu/opcode/WithOperationalRegister.cpp"
#include "Utils.cpp"
using namespace std;

class IndirectAddressingMode : public AddressingMode, public WithOperationalRegister
{
public:
    explicit IndirectAddressingMode(Register<uint8_t> CPU::*operationalRegister = nullptr) : WithOperationalRegister(operationalRegister) {}

    unique_ptr<ResolvedAddress> resolve(CPU &cpu) const override
    {
        uint16_t address;
        auto crossedBoundary = false;

        auto reg = getOperationalRegister(cpu);
        if (reg == nullptr)
        {
            // JMP (Indirect) requires reading a 16-bit pointer directly from the instruction.
            auto lo = cpu.bus.read(cpu.PC.read());
            auto hi = cpu.bus.read(cpu.PC.read() + 1);

            auto pointer = (hi << 8) | lo;

            // Emulate the 6502 page boundary bug:
            lo = cpu.bus.read(pointer);
            hi = cpu.bus.read((pointer & 0xff00) | ((pointer + 1) & 0x00ff));

            cpu.PC.increment(2);

            address = (hi << 8) | lo;
        }
        else
        {
            auto pointer = cpu.bus.read(cpu.PC.read());
            cpu.PC.increment();

            // (zp, X)
            if (reg == &cpu.X)
            {
                pointer += cpu.X.read();
            }

            auto lo = cpu.bus.read(pointer);
            auto hi = cpu.bus.read(pointer + 1);
            address = (hi << 8) | lo;

            // (zp), Y
            if (reg == &cpu.Y)
            {
                auto oldAddress = address;
                address += reg->read();

                if (Utils::checkPageBoundaryCross(oldAddress, address))
                {
                    crossedBoundary = true;
                }
            }
        }

        return make_unique<ResolvedAddress>(address, crossedBoundary);
    }
};