#include <iostream>
#include <memory>

struct Bike
{
    std::string property;
    void show() { std::cout << property << '\n'; }
};

class AccessoryBuilder
{
 public:
    virtual ~AccessoryBuilder() = default;

    virtual void reset() { bike = std::make_shared<Bike>(); }
    virtual void setFrame() { bike->property.append("Frame"); }
    virtual void setTires() { bike->property.append("Tires"); }
    virtual void setLubricator() { bike->property.append(" "); }

    virtual std::shared_ptr<Bike> getProduct()
    {
        auto product = bike;
        reset();
        return product;
    }

 protected:
    std::shared_ptr<Bike> bike;
};

class MBBuilder : public AccessoryBuilder
{
 public:
    void setFrame() override
    {
        bike->property.append("Aluminum");
        bike->property.append(" ");
        AccessoryBuilder::setFrame();
    }

    void setTires() override
    {
        bike->property.append("Knobby");
        bike->property.append(" ");
        AccessoryBuilder::setTires();
    }
};

class RBBuilder : public AccessoryBuilder
{
 public:
    void setFrame() override
    {
        bike->property.append("Carbon");
        bike->property.append(" ");
        AccessoryBuilder::setFrame();
    }

    void setTires() override
    {
        bike->property.append("Slim");
        bike->property.append(" ");
        AccessoryBuilder::setTires();
    }
};

class Director
{
 public:
    void createBike(std::shared_ptr<AccessoryBuilder> builder)
    {
        builder->reset();
        builder->setFrame();
        builder->setLubricator();
        builder->setTires();
    }
};

int main()
{
    auto mbike_builder = std::make_shared<MBBuilder>();
    auto rbike_builder = std::make_shared<RBBuilder>();

    int n;
    std::cin >> n;
    std::string type;
    Director director;
    for (int i = 0; i < n; ++i) {
        std::cin >> type;
        if (type == "mountain") {
            director.createBike(std::dynamic_pointer_cast<AccessoryBuilder>(mbike_builder));
            auto mb = mbike_builder->getProduct();
            mb->show();
        } else if (type == "road") {
            director.createBike(std::dynamic_pointer_cast<AccessoryBuilder>(rbike_builder));
            auto rb = rbike_builder->getProduct();
            rb->show();
        }
    }
    return 0;
}
