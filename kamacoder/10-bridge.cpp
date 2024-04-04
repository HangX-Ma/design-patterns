#include <iostream>
#include <memory>
#include <utility>

class Device
{
 public:
    explicit Device(std::string brand) : brand(std::move(brand)) {}
    virtual ~Device() = default;

    virtual void switchChannel()
    {
        std::cout << "Switching " << getBrand() << " TV channel" << '\n';
    }

    virtual void powerOn()
    {
        std::cout << getBrand() << " TV is ON" << '\n';
        power_state = true;
    }

    virtual void powerOff()
    {
        std::cout << getBrand() << " TV is OFF" << '\n';
        power_state = false;
    }

    virtual const std::string &getBrand() const { return brand; };

 protected:
    bool power_state{false};
    std::string brand;
};

class TCL : public Device
{
 public:
    TCL() : Device("TCL") {}
};

class Sony : public Device
{
 public:
    Sony() : Device("Sony") {}
};

class Remote
{
 public:
    void operation(int brand, int op)
    {
        if (brand == 0) {
            dev = std::make_unique<Sony>();
        }
        else if (brand == 1) {
            dev = std::make_unique<TCL>();
        }

        switch (op) {
        case 2:
            dev->powerOn();
            break;
        case 3:
            dev->powerOff();
            break;
        case 4:
            dev->switchChannel();
            break;
        default:
            break;
        }
    }

 protected:
    std::unique_ptr<Device> dev;
};

int main()
{
    int n;
    std::cin >> n;

    Remote remote;
    for (int i = 0; i < n; ++i) {
        int brand;
        int op;
        std::cin >> brand >> op;
        remote.operation(brand, op);
    }
    return 0;
}
