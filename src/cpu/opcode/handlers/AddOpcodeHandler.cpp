#pragma once
#include <memory>
#include "OpcodeHandler.hpp"
#include "cpu/CPU.cpp"
#include "Utils.cpp"
using namespace std;

class AddOpcodeHandler : public OpcodeHandler
{
public:
    using OpcodeHandler::OpcodeHandler;
protected:
    int handle(CPU &cpu, unique_ptr<ResolvedAddress> &resolvedAddress) const override
    {
        auto c = cpu.P.isSet(Carry) ? 1 : 0;
        auto a = cpu.A.read();
        auto b = cpu.bus.read(resolvedAddress->address);
        auto result = a + b + c;

        cpu.A.write(result);
        cpu.P.setAll({
            {Zero, Utils::isZero(result)},
            {Negative, Utils::isNegative(result)},
            {Carry, Utils::isCarryAdd(result)},
            {Overflow, Utils::isOverflowArith(a, b, result)},
        });

        return cycles + (resolvedAddress->crossedBoundary ? 1 : 0);
    }
};
