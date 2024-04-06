#include <iostream>
#include <memory>
#include <iomanip>

class Visitor
{
 public:
    int getRectangleSize(int width, int height) { return width * height; }
    double getCircleSize(double radius) { return 3.14 * radius * radius; }
};

class Shape
{
 public:
    virtual ~Shape() = default;
    virtual void accept(const std::shared_ptr<Visitor> &visitor) const = 0;
};

class Rectange : public Shape
{
 public:
    Rectange(int width, int height) : width(width), height(height) {}

    void accept(const std::shared_ptr<Visitor> &visitor) const override
    {
        std::cout << visitor->getRectangleSize(width, height) << '\n';
    }

 protected:
    int width;
    int height;
};

class Circle : public Shape
{
 public:
    explicit Circle(double r) : radius(r) {}

    void accept(const std::shared_ptr<Visitor> &visitor) const override
    {
        std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(2)
                  << visitor->getCircleSize(radius) << '\n';
    }

 protected:
    double radius;
};

int main()
{
    auto visitor = std::make_shared<Visitor>();
    int n;
    std::string type;
    int width;
    int height;
    int radius;

    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        std::cin >> type;
        if (type == "Circle") {
            std::cin >> radius;
            auto circle = std::make_unique<Circle>(radius);
            circle->accept(visitor);
        } else if (type == "Rectangle") {
            std::cin >> width >> height;
            auto rectangle = std::make_unique<Rectange>(width, height);
            rectangle->accept(visitor);
        }
    }
    return 0;
}
