#pragma once
#include <cstdint>
#include "cpu/register/Register.cpp"
#include "cpu/register/ProgramCounterRegister.cpp"
#include "cpu/register/StackRegister.cpp"
#include "cpu/register/StatusRegister.cpp"
using namespace std;

class CPU
{
public:
    Register<uint8_t> A;
    Register<uint8_t> X;
    Register<uint8_t> Y;
    ProgramCounterRegister PC;
    StackRegister S;
    StatusRegister P;
    IODevice &bus;

    CPU(CPUBus &bus) : bus(bus), A(0), X(0), Y(0), PC(), S(bus), P() {}

    void reset()
    {
        A.reset();
        X.reset();
        Y.reset();
        resetPC();
        S.reset();
        P.reset();
    }

    void step()
    {
        uint8_t opcode = fetch();
        // auto handler = OpcodeHandlerRepository::get(opcode);
        // handler->invoke(*this);
    }

private:
    uint8_t fetch()
    {
        uint8_t opcode = bus.read(PC.read());
        PC.increment();

        return opcode;
    }

    void resetPC()
    {
        PC.write((bus.read(0xfffd) << 8) | bus.read(0xfffc));
    }
};