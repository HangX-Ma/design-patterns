#include <iostream>
#include <memory>
#include <utility>
#include <vector>

class Command
{
 public:
    virtual ~Command() = default;
    virtual void execute() const = 0;
};

class OrderCommand : public Command
{
 public:
    explicit OrderCommand(std::string drink_name) : drink_name_(std::move(drink_name)) {}

    void execute() const override { std::cout << drink_name_ << " is ready!" << '\n'; }

 private:
    std::string drink_name_;
};

class DrinkMachine
{
 public:
    void makeDrink(std::shared_ptr<Command> &command) { command->execute(); }
};

class OrderSystem
{
 public:
    void takeOrder(std::shared_ptr<Command> command) { commands.push_back(std::move(command)); }

    void submitOrder(const std::shared_ptr<DrinkMachine> &drink_machine)
    {
        if (!commands.empty()) {
            for (auto &cmd : commands) {
                drink_machine->makeDrink(cmd);
            }
        }
        commands.clear();
    }

 protected:
    std::vector<std::shared_ptr<Command>> commands;
};

int main() {
    int n;
    std::cin >> n;

    std::string drink_name;
    auto drink_machine = std::make_shared<DrinkMachine>();
    auto ordersys = std::make_unique<OrderSystem>();
    for (int i = 0; i < n; ++i) {
        std::cin >> drink_name;
        auto cmd = std::make_shared<OrderCommand>(drink_name);
        ordersys->takeOrder(cmd);
    }
    ordersys->submitOrder(drink_machine);
    return 0;
}
