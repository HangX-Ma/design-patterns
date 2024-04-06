#include <iostream>
#include <memory>
#include <utility>

class DeskLamp;

class OnState;
class OffState;
class BlinkState;
class State
{
 public:
    explicit State(std::shared_ptr<DeskLamp> dl) : desk_lamp(std::move(dl)) {}

    virtual void on() = 0;
    virtual void off() = 0;
    virtual void blink() = 0;

 protected:
    std::shared_ptr<DeskLamp> desk_lamp;
};

class DeskLamp : std::enable_shared_from_this<DeskLamp>
{
 public:
    void changeState(std::shared_ptr<State> next_state) { state = std::move(next_state); }

    void on()
    {
        std::cout << "Light is ON" << '\n';
        state->on();
    }

    void off()
    {
        std::cout << "Light is OFF" << '\n';
        state->off();
    }

    void blink()
    {
        std::cout << "Light is Blinking" << '\n';
        state->blink();
    }

 protected:
    std::shared_ptr<State> state{nullptr};
};

class OnState : public State
{
 public:
    explicit OnState(std::shared_ptr<DeskLamp> dl) : State(std::move(dl)) {}

    void on() override {}

    void blink() override
    {
        if (desk_lamp != nullptr) {
            desk_lamp->changeState(
                std::dynamic_pointer_cast<State>(std::make_shared<BlinkState>(desk_lamp)));
        }
    }

    void off() override
    {
        if (desk_lamp != nullptr) {
            desk_lamp->changeState(
                std::dynamic_pointer_cast<State>(std::make_shared<OffState>(desk_lamp)));
        }
    }
};

class OffState : public State
{
 public:
    explicit OffState(std::shared_ptr<DeskLamp> dl) : State(std::move(dl)) {}

    void on() override
    {
        if (desk_lamp != nullptr) {
            desk_lamp->changeState(
                std::dynamic_pointer_cast<State>(std::make_shared<OnState>(desk_lamp)));
        }
    }

    void blink() override
    {
        if (desk_lamp != nullptr) {
            desk_lamp->changeState(
                std::dynamic_pointer_cast<State>(std::make_shared<BlinkState>(desk_lamp)));
        }
    }

    void off() override {}
};

class BlinkState : public State
{
 public:
    explicit BlinkState(std::shared_ptr<DeskLamp> dl) : State(std::move(dl)) {}

    void on() override
    {
        if (desk_lamp != nullptr) {
            desk_lamp->changeState(
                std::dynamic_pointer_cast<State>(std::make_shared<OnState>(desk_lamp)));
        }
    }

    void blink() override {}

    void off() override
    {
        if (desk_lamp != nullptr) {
            desk_lamp->changeState(
                std::dynamic_pointer_cast<State>(std::make_shared<OffState>(desk_lamp)));
        }
    }
};

int main()
{
    int n;
    std::cin >> n;
    std::string state;
    auto desk_lamp = std::make_shared<DeskLamp>();
    desk_lamp->changeState(std::make_shared<OffState>(desk_lamp));
    for (int i = 0; i < n; ++i) {
        std::cin >> state;
        if (state == "ON") {
            desk_lamp->on();
        } else if (state == "OFF") {
            desk_lamp->off();
        } else if (state == "BLINK") {
            desk_lamp->blink();
        }
    }
    return 0;
}
