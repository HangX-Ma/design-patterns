#include <iostream>
#include <memory>

class House
{
 public:
    virtual ~House() = default;
    virtual void request() const = 0;
};

class HouseMarket : public House
{
 public:
    void request() const override
    {
        // House market just provide house resource service.
        // So it always return true if we ask it provide us a house.
        std::cout << "YES" << '\n';
    }
};

class Proxy : public House
{
 public:
    explicit Proxy(int size) : house_size(size), house_market(nullptr) {}

    Proxy(int size, std::unique_ptr<HouseMarket> hm) : house_size(size), house_market(std::move(hm))
    {
    }

    bool checkHouse() const
    {
        if (house_size > 100) {
            return true;
        }
        std::cout << "NO" << '\n';
        return false;
    }

    void request() const override
    {
        // lazy allocation
        if (house_market == nullptr) {
            house_market = std::make_unique<HouseMarket>();
        }
        if (checkHouse()) {
            house_market->request();
        }
    }

 protected:
    int house_size;
    mutable std::unique_ptr<HouseMarket> house_market{nullptr};
};

// proxy design pattern makes all proxies or real objects share
// the same interface, which differs from facade design pattern.
void client(const std::unique_ptr<House> &house) { house->request(); }

int main()
{
    int n;
    std::cin >> n;

    int size;
    std::unique_ptr<Proxy> proxy;
    for (int i = 0; i < n; ++i) {
        std::cin >> size;
        auto market = std::make_unique<HouseMarket>();
        proxy = std::make_unique<Proxy>(size, std::move(market));
        proxy->request();
        client(std::move(proxy));
    }
    return 0;
}
