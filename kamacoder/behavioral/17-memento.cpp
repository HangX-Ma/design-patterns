#include <iostream>
#include <memory>
#include <vector>

class Memento
{
 public:
    virtual ~Memento() = default;
    virtual int getCounter() const = 0;
};

class ConcreteMemento : public Memento
{
 public:
    explicit ConcreteMemento(int count_value) : count_value(count_value) {}

    int getCounter() const override { return count_value; }

 protected:
    int count_value;
};

class Counter
{
 public:
    std::unique_ptr<Memento> save() { return std::make_unique<ConcreteMemento>(this->count_value); }
    void restore(std::unique_ptr<Memento> mem) {
        count_value = mem->getCounter();
        std::cout << count_value << '\n';
    }

    void increment()
    {
        count_value++;
        std::cout << count_value << '\n';
    }

    void decrement()
    {
        count_value--;
        std::cout << count_value << '\n';
    }

    void updateValue(int val) { count_value = val; }

 protected:
    int count_value{0};
};

class Caretaker
{
 public:
    Caretaker() : counter(std::make_unique<Counter>()) {}

    void backup(std::vector<std::unique_ptr<Memento>> &memoto_list)
    {
        memoto_list.push_back(counter->save());
    }

    void undo()
    {
        if (undo_list_.empty()) {
            return;
        }
        // save previous state in redo_list_
        backup(redo_list_);
        // restore from undo_list_
        auto memonto = std::move(undo_list_.back());
        undo_list_.pop_back();
        counter->restore(std::move(memonto));
    }

    void redo()
    {
        if (redo_list_.empty()) {
            return;
        }
        // save previous state in undo_list_
        backup(undo_list_);
        // restore from redo_list_
        auto memonto = std::move(redo_list_.back());
        redo_list_.pop_back();
        counter->restore(std::move(memonto));
    }

    void increment()
    {
        redo_list_.clear();
        backup(undo_list_);
        counter->increment();
    }

    void decrement()
    {
        redo_list_.clear();
        backup(undo_list_);
        counter->decrement();
    }

 protected:
    std::unique_ptr<Counter> counter;

 private:
    std::vector<std::unique_ptr<Memento>> undo_list_;
    std::vector<std::unique_ptr<Memento>> redo_list_;
};

int main()
{
    std::string cmd;
    auto caretaker = std::make_unique<Caretaker>();
    while (std::cin >> cmd) {
        if (cmd == "Increment") {
            caretaker->increment();
        } else if (cmd == "Decrement") {
            caretaker->decrement();
        } else if (cmd == "Undo") {
            caretaker->undo();
        } else if (cmd == "Redo") {
            caretaker->redo();
        }
    }
    return 0;
}
