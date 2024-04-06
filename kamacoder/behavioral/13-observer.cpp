#include <iostream>
#include <memory>
#include <set>

class EventListener
{
 public:
    virtual ~EventListener() = default;
    virtual void update(int time) = 0;
};

class Student : public EventListener
{
 public:
    explicit Student(std::string name) : name_(std::move(name)) {}
    void update(int time) override { std::cout << name_ << " " << time << '\n'; }

 private:
    std::string name_;
};

class Clock
{
 public:
    void subscribe(const std::shared_ptr<Student> &st) { client.emplace(st); }
    void unsubscribe(const std::shared_ptr<Student> &st) { client.erase(st); }

    void notify()
    {
        time++;
        for (auto &st : client) {
            st->update(time);
        }
    }

 protected:
    std::set<std::shared_ptr<Student>> client;
    int time{0};
};

int main()
{
    int n;
    std::cin >> n;
    Clock clock_system;
    std::string name;
    for (int i = 0; i < n; ++i) {
        std::cin >> name;
        auto st = std::make_shared<Student>(name);
        clock_system.subscribe(st);
    }
    // update time
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        clock_system.notify();
    }
}
