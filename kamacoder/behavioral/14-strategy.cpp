#include <iostream>
#include <memory>

class Strategy
{
 public:
    virtual int getDiscount(int total_price) const = 0;
};

class PlanA : public Strategy
{
 public:
    int getDiscount(int total_price) const override
    {
        return static_cast<double>(total_price) * 0.9;
    }
};

class PlanB : public Strategy
{
 public:
    int getDiscount(int total_price) const override
    {
        if (total_price < 100) {
            return total_price;
        }
        if (total_price < 150) {
            return total_price - 5;
        }
        if (total_price < 200) {
            return total_price - 15;
        }
        if (total_price < 300) {
            return total_price - 25;
        }
        return total_price - 40;
    }
};

class DecisionSystem
{
 public:
    void execute(int total_price, int type)
    {
        switch (type) {
        case 1:
            strategy = std::make_unique<PlanA>();
            break;
        case 2:
            strategy = std::make_unique<PlanB>();
            break;
        default:
            throw std::invalid_argument("Invalid strategy");
        }
        std::cout << strategy->getDiscount(total_price) << '\n';
    }

 protected:
    std::unique_ptr<Strategy> strategy{nullptr};
};

int main()
{
    auto decision_system = std::make_unique<DecisionSystem>();
    int n;
    std::cin >> n;
    int type;
    int total_price;
    for (int i = 0; i < n; ++i) {
        std::cin >> total_price >> type;
        decision_system->execute(total_price, type);
    }
    return 0;
}
