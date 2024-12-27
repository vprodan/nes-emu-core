#pragma once
#include "OpcodeHandler.hpp"

class NoopOpcodeHandler : public OpcodeHandler
{
public:
    using OpcodeHandler::OpcodeHandler;

protected:
    int handle(CPU &cpu) const override
    {
        return cycles;
    }
};
