#include <iostream>
#include <memory>

using std::unique_ptr;

class Block
{
 public:
    virtual ~Block() = default;
};

class Circle : public Block
{
 public:
    Circle() { std::cout << "Circle Block" << '\n'; }
};

class Square : public Block
{
 public:
    Square() { std::cout << "Square Block" << '\n'; }
};

class Factory
{
 public:
    virtual ~Factory() = default;
    virtual std::shared_ptr<Block> create() const = 0;
};

class CircleFactory : public Factory
{
 public:
    std::shared_ptr<Block> create() const override { return std::make_shared<Circle>(); }
};

class SquareFactory : public Factory
{
 public:
    std::shared_ptr<Block> create() const override { return std::make_shared<Square>(); }
};

int main()
{
    std::string type;
    int num;
    int n;
    std::cin >> n;

    std::shared_ptr<Factory> fc;
    for (int k = 0; k < n; ++k) {
        while (std::cin >> type >> num) {
            if (type == "Circle") {
                fc = std::dynamic_pointer_cast<Factory>(std::make_shared<CircleFactory>());
            } else if (type == "Square") {
                fc = std::dynamic_pointer_cast<Factory>(std::make_shared<SquareFactory>());
            }
            for (int i = 0; i < num; ++i) {
                fc->create();
            }
        }
    }
    return 0;
}
