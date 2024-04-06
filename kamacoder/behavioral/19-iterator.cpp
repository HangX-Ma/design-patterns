#include <iostream>
#include <memory>
#include <vector>

template <typename T>
class Iterator
{
 public:
    virtual ~Iterator() = default;
    virtual std::shared_ptr<T> next() = 0;
    virtual bool hasNext() = 0;
};

class Student
{
 public:
    Student(std::string name, std::string id) : name(std::move(name)), id(std::move(id)) {}

    const std::string &getName() { return name; }
    const std::string &getSID() { return id; }

 protected:
    std::string name;
    std::string id;
};

class StudentIteratorInner : public Iterator<Student>
{
 public:
    explicit StudentIteratorInner(const std::vector<std::shared_ptr<Student>> &student_vec)
    {
        stvec_ = student_vec;
    }

    bool hasNext() override { return index_ < stvec_.size(); }

    std::shared_ptr<Student> next() override
    {
        if (hasNext()) {
            return stvec_[index_++];
        }
        return nullptr;
    }

 private:
    size_t index_;
    std::vector<std::shared_ptr<Student>> stvec_;
};

class StudentIteratorInterface
{
    virtual std::unique_ptr<Iterator<Student>> iterator() = 0;
};

class StudentIterator : public StudentIteratorInterface
{
 public:
    void add(std::shared_ptr<Student> student) { stvec_.push_back(std::move(student)); }

    std::unique_ptr<Iterator<Student>> iterator() override
    {
        return std::make_unique<StudentIteratorInner>(stvec_);
    }

 private:
    std::vector<std::shared_ptr<Student>> stvec_;
};

int main()
{
    int n;
    std::cin >> n;
    std::shared_ptr<Student> st = nullptr;
    auto st_iterator = std::make_unique<StudentIterator>();
    std::string name;
    std::string id;
    for (int i = 0; i < n; ++i) {
        std::cin >> name >> id;
        st = std::make_shared<Student>(name, id);
        st_iterator->add(st);
    }

    auto iterator = st_iterator->iterator();
    while (iterator->hasNext()) {
        auto next = iterator->next();
        if (next != nullptr) {
            std::cout << next->getName() << " " << next->getSID() << '\n';
        }
    }
    return 0;
}
