#include <functional>
#include <iostream>
#include <memory>
#include <unordered_map>
#include <utility>
#include <vector>

class Shape
{
 public:
    virtual ~Shape() = default;
    virtual void drawTo(int x, int y) const = 0;
};

class ShapeType : public Shape
{
 public:
    explicit ShapeType(std::string_view type) : type(std::string(type)) {}
    void drawTo(int x, int y) const override
    {
        static std::string_view outstr;
        outstr = first_drawn_ ? " drawn at " : " shared at ";
        first_drawn_ = false;
        std::cout << type << outstr << "(" << x << "," << y << ")" << '\n';
    };

    bool operator==(const ShapeType &rhs) { return this->type == rhs.type; }

 private:
    mutable bool first_drawn_{true};

 protected:
    std::string type;
};

struct SVHash
{
    size_t operator()(std::string_view sv) const { return std::hash<std::string_view>{}(sv); }
};

struct SVComparator
{
    bool operator()(std::string_view sv1, std::string_view sv2) const { return sv1 == sv2; }
};

class ShapeFactory
{
 public:
    std::shared_ptr<ShapeType> getShapeType(std::string_view type)
    {
        auto it = shared_shapes_.find(type);
        if (it != shared_shapes_.end()) {
            return it->second;
        }
        auto new_type = std::make_shared<ShapeType>(type);
        shared_shapes_.emplace(type, new_type);
        return new_type;
    }

 private:
    std::unordered_map<std::string_view, std::shared_ptr<ShapeType>, SVHash, SVComparator>
        shared_shapes_;
};

class ConcreteShape
{
 public:
    ConcreteShape(std::shared_ptr<ShapeType> type, int x, int y)
        : type(std::move(type)), x(x), y(y){};

    void draw() const { type->drawTo(x, y); }

 protected:
    std::shared_ptr<ShapeType> type;
    int x;
    int y;
};

int main()
{
    ShapeFactory sf;

    std::string type;
    int x;
    int y;
    while (std::cin >> type >> x >> y) {
        auto shape_type = sf.getShapeType(type);
        auto cs = ConcreteShape(shape_type, x, y);
        cs.draw();
    }
    return 0;
}
