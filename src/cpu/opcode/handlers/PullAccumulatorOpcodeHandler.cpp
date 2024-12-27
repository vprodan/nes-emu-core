#pragma once
#include "OpcodeHandler.hpp"
#include "cpu/CPU.cpp"
#include "Utils.cpp"

class PullAccumulatorOpcodeHandler : public OpcodeHandler
{
public:
    using OpcodeHandler::OpcodeHandler;

protected:
    int handle(CPU &cpu) const override
    {
        uint8_t value = cpu.S.pop();
        cpu.A.write(value);

        cpu.P.setAll({
            {Status::Zero, Utils::isZero(value)},
            {Status::Negative, Utils::isNegative(value)},
        });

        return cycles;
    }
};
