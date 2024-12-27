#pragma once
#include <cstdint>
#include <vector>
#include <memory>
#include "IODevice.hpp"
using namespace std;

class CPUBus : public IODevice
{
public:
    void addDevice(uint16_t startAddress, uint16_t endAddress, shared_ptr<IODevice> device)
    {
        devices.push_back({startAddress, endAddress, device});
    }

    uint8_t read(uint16_t address)
    {
        IODevice *device = getDevice(address);

        return device->read(address);
    };

    void write(uint16_t address, uint8_t value)
    {
        IODevice *device = getDevice(address);

        return device->write(address, value);
    };

private:
    struct DeviceMapping
    {
        uint16_t startAddress;
        uint16_t endAddress;
        shared_ptr<IODevice> device;
    };

    vector<DeviceMapping> devices;

    IODevice *getDevice(uint16_t address)
    {
        for (const auto &device : devices)
        {
            if (address >= device.startAddress && address <= device.endAddress)
            {
                return device.device.get();
            }
        }

        return nullptr;
    }
};