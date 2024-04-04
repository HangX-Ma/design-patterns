#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>
#include <string_view>

class Property
{
 public:
    Property() = default;
    Property(std::string_view type, std::string_view name, bool has_children)
        : has_children(has_children), type(std::string{type}), name(std::string{name})
    {
    }
    virtual ~Property() = default;

    virtual std::string_view getName() const { return name; }
    virtual void setName(std::string_view name) { this->name = std::string{name}; }

    virtual std::string_view getType() const { return type; }
    virtual void setType(std::string_view type) { this->type = std::string{type}; }

    virtual void setParent(std::shared_ptr<Property> property) { parent = property; }
    virtual std::shared_ptr<Property> getParent() { return parent; }

    virtual bool isComposite() const { return has_children; }
    virtual void add([[maybe_unused]] std::shared_ptr<Property> property) {}
    virtual void remove([[maybe_unused]] std::shared_ptr<Property> property) {}
    virtual void print() const = 0;

    bool operator==(const Property &rhs) const
    {
        return this->type == rhs.type && this->name == rhs.name;
    }

 protected:
    std::shared_ptr<Property> parent{nullptr};
    bool has_children{false};
    std::string type;
    std::string name;
};

class Department : public Property, public std::enable_shared_from_this<Department>
{
 public:
    Department() = default;
    explicit Department(std::string_view name) : Property("D", name, true) {}

    void add(std::shared_ptr<Property> employee) override
    {
        employees.push_back(employee);
        employee->setParent(shared_from_this());
    }

    void remove(std::shared_ptr<Property> employee) override
    {
        auto it = std::find(employees.begin(), employees.end(), employee);
        if (it != employees.end()) {
            employees.erase(it);
            employee->setParent(nullptr);
        }
    }

    void print() const override
    {
        std::cout << this->name << '\n';
        for (const auto &employee : employees) {
            std::cout << "  ";
            employee->print();
        }
    }

 protected:
    std::vector<std::shared_ptr<Property>> employees;
};

class Employee : public Property
{
 public:
    Employee() = default;
    explicit Employee(std::string_view name) : Property("E", name, false) {}
    void print() const override { std::cout << "  " << this->name << '\n'; }
};

class Company : public Property, public std::enable_shared_from_this<Company>
{
 public:
    explicit Company(std::string_view name) : Property("C", name, true) {}

    void add(std::shared_ptr<Property> department) override
    {
        departments.push_back(department);
        department->setParent(shared_from_this());
    }

    void remove(std::shared_ptr<Property> department) override
    {
        auto it = std::find(departments.begin(), departments.end(), department);
        if (it != departments.end()) {
            departments.erase(it);
            department->setParent(nullptr);
        }
    }

    void print() const override
    {
        std::cout << "Company Structure:" << '\n';
        std::cout << this->name << '\n';
        for (const auto &department : departments) {
            std::cout << "  ";
            department->print();
        }
    }

 protected:
    std::vector<std::shared_ptr<Property>> departments;
};

int main()
{
    std::string company_name;
    std::cin >> company_name;
    auto company = std::make_shared<Company>(company_name);

    int n;
    std::cin >> n;
    std::string itype;
    std::string iname;

    int i = 0;
    std::cin >> itype >> iname;
    while (i < n) {
        auto department = std::make_shared<Department>(iname);
        i++;
        while (i < n) {
            itype.clear();
            iname.clear();
            std::cin >> itype >> iname;
            if (itype == "E") {
                auto employee = std::make_shared<Employee>(iname);
                department->add(employee);
                i++;
                continue;
            }
            break;
        }
        company->add(department);
    }
    company->print();

    return 0;
};
