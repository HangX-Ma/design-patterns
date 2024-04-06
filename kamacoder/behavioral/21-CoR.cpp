#include <iostream>
#include <memory>

class Handler
{
 public:
    virtual ~Handler() = default;

    virtual std::shared_ptr<Handler> setNext(std::shared_ptr<Handler> handler) = 0;
    virtual void handle(const std::string &name, int day) = 0;
};

class AbstractHandler : public Handler
{
 public:
    std::shared_ptr<Handler> setNext(std::shared_ptr<Handler> handler) override
    {
        this->next_handler = handler;
        return handler;
    }

    void handle(const std::string &name, int day) override
    {
        if (next_handler != nullptr) {
            next_handler->handle(name, day);
        }
    }

 protected:
    std::shared_ptr<Handler> next_handler;
};

class Supervisor : public AbstractHandler
{
 public:
    void handle(const std::string &name, int day) override
    {
        if (day <= 3) {
            std::cout << name << " Approved by " << processer_name << "." << '\n';
        } else {
            next_handler->handle(name, day);
        }
    }

 protected:
    std::string processer_name{"Supervisor"};
};

class Manager : public AbstractHandler
{
 public:
    void handle(const std::string &name, int day) override
    {
        if (day <= 7) {
            std::cout << name << " Approved by " << processer_name << "." << '\n';
        } else {
            next_handler->handle(name, day);
        }
    }

 protected:
    std::string processer_name{"Manager"};
};

class Director : public AbstractHandler
{
 public:
    void handle(const std::string &name, int day) override
    {
        if (day <= 10) {
            std::cout << name << " Approved by " << processer_name << "." << '\n';
        } else {
            std::cout << name << " Denied by " << processer_name << "." << '\n';
        }
    }

 protected:
    std::string processer_name{"Director"};
};

int main()
{
    auto supervisor = std::make_shared<Supervisor>();
    auto manager = std::make_shared<Manager>();
    auto director = std::make_shared<Director>();
    supervisor->setNext(manager)->setNext(director);

    int n;
    std::cin >> n;

    std::string name;
    int day;
    for (int i = 0; i < n; ++i) {
        std::cin >> name >> day;
        supervisor->handle(name, day);
    }
    return 0;
}
