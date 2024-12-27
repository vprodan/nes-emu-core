#pragma once
#include <cstdint>
#include <memory>
#include "OpcodeHandler.hpp"
#include "cpu/CPU.cpp"
#include "cpu/opcode/WithOperationalRegister.cpp"
#include "Utils.cpp"
#include "cpu/register/Register.cpp"
using namespace std;

class TransferRegisterOpcodeHandler : public OpcodeHandler, public WithOperationalRegister
{
private:
    Register<uint8_t> CPU::*destinationRegister;

public:
    TransferRegisterOpcodeHandler(int cycles, Register<uint8_t> CPU::*sourceRegister, Register<uint8_t> CPU::*destinationRegister)
        : OpcodeHandler(cycles), WithOperationalRegister(sourceRegister), destinationRegister(destinationRegister) {}

protected:
    int handle(CPU &cpu) const override
    {
        auto sourceReg = *getOperationalRegister(cpu);
        auto destReg = cpu.*destinationRegister;

        auto value = sourceReg.read();

        destReg.write(value);

        if (destinationRegister != reinterpret_cast<Register<uint8_t> CPU::*>(&CPU::S))
        {
            cpu.P.setAll({
                {Status::Zero, Utils::isZero(value)},
                {Status::Negative, Utils::isNegative(value)},
            });
        }

        return cycles;
    }
};
