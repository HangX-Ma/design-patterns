#include <iostream>
#include <memory>
#include <stdexcept>

class TypeC
{
 public:
    virtual ~TypeC() = default;
    virtual void charge() const { std::cout << "TypeC" << '\n'; }
};

class USB
{
 public:
    void charge() const { std::cout << "USB Adapter" << '\n'; }
};

class Dock : public TypeC
{
 public:
    explicit Dock(std::unique_ptr<USB> usb) : usb_port(std::move(usb)) {}

    void charge() const override { usb_port->charge(); }

 protected:
    std::unique_ptr<USB> usb_port;
};

class ExDock : public TypeC, public USB
{
 public:
    explicit ExDock(int type) : type(type) {}
    void charge() const override {
        switch (type) {
        case 1:
            TypeC::charge();
            break;
        case 2:
            USB::charge();
            break;
        default:
            throw std::invalid_argument("Invalid charger port");
        }
    }

 protected:
    int type{1};
};

void client(const std::shared_ptr<TypeC> &charger) { charger->charge(); }

int main()
{
    int n;
    std::cin >> n;

    int type;
    auto typec = std::make_shared<TypeC>();
    auto dock = std::make_shared<Dock>(std::make_unique<USB>());
#if 0
    for (int i = 0; i < n; ++i) {
        std::cin >> type;
        switch (type) {
        case 1:
            client(typec);
            break;
        case 2:
            client(std::dynamic_pointer_cast<TypeC>(dock));
            break;
        default:
            throw std::invalid_argument("Invalid charger port");
        }
    }
#endif

    for (int i = 0; i < n; ++i) {
        std::cin >> type;
        ExDock exdock(type);
        exdock.charge();
    }

    return 0;
}
