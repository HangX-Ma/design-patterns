#include <iostream>
#include <memory>
#include <utility>

class Shape
{
 public:
    Shape() = default;
    explicit Shape(const std::shared_ptr<Shape> &other)
    {
        this->x = other->x;
        this->y = other->y;
    }
    virtual ~Shape() = default;
    virtual std::shared_ptr<Shape> clone() = 0;

 public:
    int x;
    int y;
};

class Rectangle : public Shape, public std::enable_shared_from_this<Rectangle>
{
 public:
    Rectangle(std::string color, int width, int height)
        : color(std::move(color)), width(width), height(height)
    {
    }
    explicit Rectangle(const std::shared_ptr<Rectangle> &other) : Shape(other)
    {
        this->color = other->color;
        width = other->width;
        height = other->height;
    }
    std::shared_ptr<Shape> clone() override
    {
        std::cout << "Color: " << color << ", Width: " << width << ", Height: " << height << '\n';
        return std::make_shared<Rectangle>(shared_from_this());
    }

 public:
    std::string color;
    int width;
    int height;
};

int main()
{
    int n;
    std::cin >> n;

    std::string color;
    int width;
    int height;
    for (int i = 0; i < n; ++i) {
        std::cin >> color >> width >> height;
        auto rectangle = std::make_shared<Rectangle>(color, width, height);
        rectangle->clone();
    }
}
