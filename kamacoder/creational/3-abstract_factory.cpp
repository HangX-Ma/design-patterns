#include <iostream>
#include <memory>

class Chair
{
 public:
    Chair() { std::cout << "chair" << '\n'; }
};

class Sofa
{
 public:
    Sofa() { std::cout << "sofa" << '\n'; }
};

class FunitureFactory
{
 public:
    virtual ~FunitureFactory() = default;
    virtual std::shared_ptr<Chair> createChair() { return std::make_shared<Chair>(); }
    virtual std::shared_ptr<Sofa> createSofa() { return std::make_shared<Sofa>(); }
};

class ModernFactory : public FunitureFactory
{
 public:
    std::shared_ptr<Chair> createChair() override
    {
        std::cout << "modern ";
        return FunitureFactory::createChair();
    }
    std::shared_ptr<Sofa> createSofa() override
    {
        std::cout << "modern ";
        return FunitureFactory::createSofa();
    }
};

class ClassicFactory : public FunitureFactory
{
 public:
    std::shared_ptr<Chair> createChair() override
    {
        std::cout << "classical ";
        return FunitureFactory::createChair();
    }
    std::shared_ptr<Sofa> createSofa() override
    {
        std::cout << "classical ";
        return FunitureFactory::createSofa();
    }
};

int main()
{
    auto ff = std::make_unique<FunitureFactory>();
    int n;
    std::cin >> n;
    std::string type;
    for (int i = 0; i < n; ++i) {
        std::cin >> type;
        if (type == "modern") {
            ff = std::make_unique<ModernFactory>();
        } else if (type == "classical") {
            ff = std::make_unique<ClassicFactory>();
        }
        ff->createChair();
        ff->createSofa();
    }
}
