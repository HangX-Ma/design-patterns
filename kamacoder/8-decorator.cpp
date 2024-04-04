#include <exception>
#include <iostream>
#include <memory>

class Coffee
{
 public:
    virtual ~Coffee() = default;
    virtual void brew() const = 0;
};

class BlackCoffe : public Coffee
{
 public:
    void brew() const override { std::cout << "Brewing Black Coffee" << '\n'; };
};

class Latte : public Coffee
{
 public:
    void brew() const override { std::cout << "Brewing Latte" << '\n'; };
};

class Mixer : public Coffee
{
 public:
    explicit Mixer(std::shared_ptr<Coffee> &coffee) : coffee_(coffee) {}
    void brew() const override { coffee_->brew(); }

 private:
    std::shared_ptr<Coffee> coffee_;
};

class MilkMixer : public Mixer
{
 public:
    explicit MilkMixer(std::shared_ptr<Coffee> &coffee) : Mixer(coffee) {}
    void brew() const override
    {
        Mixer::brew();
        std::cout << "Adding Milk" << '\n';
    }
};

class SugarMixer : public Mixer
{
 public:
    explicit SugarMixer(std::shared_ptr<Coffee> &coffee) : Mixer(coffee) {}
    void brew() const override
    {
        Mixer::brew();
        std::cout << "Adding Sugar" << '\n';
    }
};

class CoffeeMaker
{
 public:
    void brewCoffer(int type, int supplment)
    {
        std::shared_ptr<Coffee> coffee;
        std::shared_ptr<Coffee> mixer;
        switch (type) {
        case 1:
            coffee = std::make_shared<BlackCoffe>();
            break;
        case 2:
            coffee = std::make_shared<Latte>();
            break;
        default:
            throw std::exception();
        }

        switch (supplment) {
        case 1:
            mixer = std::make_shared<MilkMixer>(coffee);
            break;
        case 2:
            mixer = std::make_shared<SugarMixer>(coffee);
            break;
        default:
            throw std::exception();
        }
        mixer->brew();
    }
};

int main()
{
    int coffee_type;
    int supplement_type;
    CoffeeMaker cm;
    while (std::cin >> coffee_type >> supplement_type) {
        cm.brewCoffer(coffee_type, supplement_type);
    }
    return 0;
}
