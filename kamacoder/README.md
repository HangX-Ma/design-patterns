# About Design Patterns Problems - C++

## 11. Company's organization structure

We are asked to use **Composite** design pattern to solve the problem.

- **Input**

  ```bash
  MyCompany
  8
  D HR
  E HRManager
  D Finance
  E AccountantA
  E AccountantB
  D IT
  E DeveloperA
  E DeveloperB
  ```

- **Output**

  ```bash
  Company Structure:
  MyCompany
  HR
    HRManager
  Finance
    AccountantA
    AccountantB
  IT
    DeveloperA
    DeveloperB
  ```

### 11.1 About `std::shared_from_this`

I try to use `void setParent(std::shared_ptr<Property> property)` function to store the parent smart pointer in class `Company` and class `Employee`. I found C++ provide `std::enable_shared_from_this<T>` template to help us wrapper `this` pointer, with which asks us use `public` inheritance.

I use `std::shared_from_this()` function to return the wrapper pointer but it leads to the following error.

```bash
terminate called after throwing an instance of 'std::bad_weak_ptr'
  what():  bad_weak_ptr
Aborted
```

Look at what `std::shared_from_this` does:

```bash
shared_ptr<_Tp>
shared_from_this()
{
    return shared_ptr<_Tp>(this->_M_weak_this);
}
```

It actually returns a **shared_ptr** from **weak_ptr**, which means we need to wrapper the class that use `std::shared_from_this` with `shared_ptr`. Otherwise, the **weak_ptr** will be empty and `std::shared_from_this` will return `nullptr`.

> [shared_from_this bad_weak_ptr的原因](https://blog.csdn.net/G1036583997/article/details/65626749)\
> [shared_from_this使用中运行错误bad_weak_ptr原因分析](https://blog.csdn.net/xhtchina/article/details/126296962)

### 11.2 About `std::string_view`

`std::string_view` only provides a window that allows us look through the string quickly. If you use it store necessary string data, you will be upset on account of the string life cycle. One feasible method is that we can use `std::string_view` as function parameter type and store it in `std::string` to solidifying its life cycle. If we do like this, the data in `std::string_view` will be copied into `std::string`, which has the same life cycle as the instantiated class.

```cpp
class Property {
 public:
    virtual void setName(std::string_view name) { this->name = std::string{name}; }
    ...
 protected:
    std::string name;
}
```
