#pragma once
#include <map>
#include <memory>
#include "cpu/opcode/addressing/AddressingMode.hpp"
#include "cpu/opcode/addressing/AbsoluteAddressingMode.cpp"
#include "cpu/opcode/addressing/ImmediateAddressingMode.cpp"
#include "cpu/opcode/addressing/IndirectAddressingMode.cpp"
#include "cpu/opcode/addressing/RelativeAddressingMode.cpp"
#include "cpu/opcode/addressing/ZeroPageAddressingMode.cpp"
using namespace std;

class AddressingModeRepository
{
public:
    static AddressingModeRepository &getInstance()
    {
        static AddressingModeRepository instance;

        return instance;
    }

    AddressingMode *get(AddressingModeType type)
    {
        return repo[type].get();
    }

private:
    AddressingModeRepository()
    {
        repo[Absolute] = make_unique<AbsoluteAddressingMode>();
        repo[AbsoluteX] = make_unique<AbsoluteAddressingMode>(&CPU::X);
        repo[AbsoluteY] = make_unique<AbsoluteAddressingMode>(&CPU::Y);

        repo[Immediate] = make_unique<ImmediateAddressingMode>();

        repo[Indirect] = make_unique<IndirectAddressingMode>();
        repo[IndirectX] = make_unique<IndirectAddressingMode>(&CPU::X);
        repo[IndirectY] = make_unique<IndirectAddressingMode>(&CPU::Y);

        repo[Relative] = make_unique<RelativeAddressingMode>();

        repo[ZeroPage] = make_unique<ZeroPageAddressingMode>();
        repo[ZeroPageX] = make_unique<ZeroPageAddressingMode>(&CPU::X);
        repo[ZeroPageY] = make_unique<ZeroPageAddressingMode>(&CPU::Y);
    }

    map<AddressingModeType, unique_ptr<AddressingMode>> repo;

    AddressingModeRepository(const AddressingModeRepository &) = delete;
    AddressingModeRepository &operator=(const AddressingModeRepository &) = delete;
};