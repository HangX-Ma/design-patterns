#include <iostream>
#include <memory>

class Device
{
 public:
    virtual void powerOff() { power_state = false; }
    virtual ~Device() = default;

 protected:
    bool power_state{true};
};

class DeskLamp : public Device
{
 public:
    void powerOff() override
    {
        Device::powerOff();
        std::cout << "Desk Lamp is turned off." << '\n';
    }
};

class AirConditioner : public Device
{
 public:
    void powerOff() override
    {
        Device::powerOff();
        std::cout << "Air Conditioner is turned off." << '\n';
    }
};

class Television : public Device
{
 public:
    void powerOff() override
    {
        Device::powerOff();
        std::cout << "Television is turned off." << '\n';
    }
};

class MasterSwitch
{
 public:
    MasterSwitch()
    {
        ac = std::make_unique<AirConditioner>();
        dl = std::make_unique<DeskLamp>();
        tv = std::make_unique<Television>();
    }

    void operation(int i)
    {
        switch (i) {
        case 1:
            ac->powerOff();
            break;
        case 2:
            dl->powerOff();
            break;
        case 3:
            tv->powerOff();
            break;
        case 4:
            std::cout << "All devices are off." << '\n';
            break;
        default:
            std::cout << "Invalid device code." << '\n';
        }
    }

 protected:
    std::unique_ptr<AirConditioner> ac;
    std::unique_ptr<DeskLamp> dl;
    std::unique_ptr<Television> tv;
};

int main()
{
    MasterSwitch ms;
    int n;
    std::cin >> n;

    int devno;
    for (int i = 0; i < n; ++i) {
        std::cin >> devno;
        ms.operation(devno);
    }
}
