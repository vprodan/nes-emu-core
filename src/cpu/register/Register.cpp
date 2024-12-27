#pragma once
#include <cstdint>
using namespace std;

template <typename T>
class Register
{
protected:
    T value;
    const T defaultValue;

public:
    Register(T defaultValue = 0) : defaultValue(defaultValue)
    {
        reset();
    }

    T read() const
    {
        return value;
    }

    void write(T value)
    {
        this->value = value;
    }

    void reset()
    {
        write(defaultValue);
    }
};