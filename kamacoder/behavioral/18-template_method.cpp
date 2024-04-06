#include <iostream>
#include <memory>

class CoffeeMaker
{
 public:
    virtual ~CoffeeMaker() = default;

    virtual void grind() const { std::cout << "Grinding coffee beans" << '\n'; }
    virtual void brew() const { std::cout << "Brewing coffee" << '\n'; }
    virtual void addCondiments() const { std::cout << "Adding condiments" << '\n'; }
};

class AmericanCoffee : public CoffeeMaker
{
 public:
    AmericanCoffee() { std::cout << "Making American Coffee:" << '\n'; }
};

class Latte : public CoffeeMaker
{
 public:
    Latte() { std::cout << "Making Latte:" << '\n'; }
    void addCondiments() const override
    {
        std::cout << "Adding milk" << '\n';
        CoffeeMaker::addCondiments();
    }
};

class Maker
{
 public:
    void select(int type)
    {
        switch (type) {
        case 1:
            coffee_maker = std::make_shared<AmericanCoffee>();
            break;
        case 2:
            coffee_maker = std::make_shared<Latte>();
            break;
        default:
            throw std::invalid_argument("Invalid coffee type");
        }
        makeCoffee();
    }

 private:
    void makeCoffee() const
    {
        if (coffee_maker == nullptr) {
            return;
        }
        coffee_maker->grind();
        coffee_maker->brew();
        coffee_maker->addCondiments();
    }

 protected:
    std::shared_ptr<CoffeeMaker> coffee_maker{nullptr};
};

int main()
{
    Maker maker;
    int type;
    while (std::cin >> type) {
        maker.select(type);
        std::cout << '\n';
    }
}
