# About Design Patterns Problems - C++

<!--toc:start-->

- [About Design Patterns Problems - C++](#about-design-patterns-problems-c)
  - [1. Cart](#1-cart)
  - [2. Build block factory](#2-build-block-factory)
  - [3. Furniture factory](#3-furniture-factory)
  - [4. Bicycle processing](#4-bicycle-processing)
  - [5. Rectangle prototype](#5-rectangle-prototype)
  - [6. Dock](#6-dock)
  - [7. Buy a house](#7-buy-a-house)
  - [8. Coffee with sugar](#8-coffee-with-sugar)
  - [9. Power switch](#9-power-switch)
  - [10. Universal remote control](#10-universal-remote-control)
  - [11. Company's organization structure](#11-companys-organization-structure)
    - [11.1 About `std::shared_from_this`](#111-about-stdsharedfromthis)
    - [11.2 About `std::string_view`](#112-about-stdstringview)
  - [12. Graphics editor](#12-graphics-editor)
  <!--toc:end-->

## 1. Cart

I know how to use smart pointer to design singleton. You can take a glance of the following reference urls.

- Use `std::mutex` and `std::unique_lock` to make thread safe.
- Use double `nullptr` checks to avoid redundant lock.
- Use `std::weak_ptr` to ensure the singleton resources will be automatically released after last user leaves.

I was awkward to see the my knowledge punctured about `static` when in an interview. At this time, I know why the `static` variable in a class needs to be initialized out of class and why the `static` variables can initialize in class functions or normal functions.

> [c++static用法详解与为什么非const静态变量要在类外定义的原因分析-CSDN](https://blog.csdn.net/TwoTon/article/details/124525595)\[**Important!**\]\
> [为什么static成员变量一定要在类外初始化?-博客园](https://www.cnblogs.com/lixuejian/p/13215271.html)\
> [设计模式——C++11实现单例模式(饿汉模式、懒汉模式)，与单例的进程-CSDN](https://blog.csdn.net/qq_51963665/article/details/132667572)\
> [3. 创建型模式--SINGLETON(单件)-CSDN](https://blog.csdn.net/sky8336/article/details/107729014)

## 2. Build block factory

The **Factory** design pattern inherit from its parent class with common interfaces. If we have 3 products, we need to create 3 factories to produce them.

## 3. Furniture factory

The **Abstract Factory** seems to be similar with **Factory**. It actually the same if we reduce each factory's products to one. **Abstract Factory** creates combinations of some products and manage their production in one class. That means we can produce more than one products using one factory. What's more, we can produce different style products by inherit parent class and realize polymorphism.

## 4. Bicycle processing

We need to abstract the processing procedure in **Abstract Builder** and realize them in **Concrete Builder**. We can ask **Director** to help us produce certain products. It isn't necessary in some scenarios because the client can do it by own.

- `reset` first before production.
- In `getProduct` we need to reset the inner prototype empty and return previous assembled product.

## 5. Rectangle prototype

Nothing innovative but make full use of `this` pointer and inheritance.

## 6. Dock

Use **multiple inheritance** or **combination** can both easily convert items from weird interface to target interface.

## 7. Buy a house

Initially I think **Facade** has no difference with **Proxy**. But **Proxy** design pattern makes all proxies or real objects share the same interface, which differs from **Facade** design pattern.

## 8. Coffee with sugar

What is **Decorator**? Understanding this concept seems to be more important. This design pattern acts like a stack that adds the needed **Concrete Decorators** on original one.

In this scenarios, we want to brew a cup of coffee with some supplements. We are asked only one small packet _sugar_ or a cup of _milk_. Actually we can add more _sugar_ and _milk_.

```cpp
// Get a cup of black coffee with milk and sugar
std::shared_ptr<Coffee> coffee;
std::shared_ptr<Coffee> mixer1;
std::shared_ptr<Coffee> mixer2;
coffee = std::make_shared<BlackCoffe>();
mixer1 = std::make_shared<MilkMixer>(coffee);
mixer2 = std::make_shared<SugarMixer>(mixer1);
```

## 9. Power switch

Just like `switch` and `if-else`.

## 10. Universal remote control

**Abstraction** and **Implementation**.

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

> [shared_from_this bad_weak_ptr的原因-CSDN](https://blog.csdn.net/G1036583997/article/details/65626749)\
> [shared_from_this使用中运行错误bad_weak_ptr原因分析-CSDN](https://blog.csdn.net/xhtchina/article/details/126296962)

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

## 12. Graphics editor

How to identify the reusable the shared resources is the core. In this problem, the shared resources are **Shape Type**. The unique resources are **Position** at where to draw shapes.

I also met a problem about **local static variable**. I want to use a `static string` variable in a function. However, it seems only acquire the first definition value, which not updated since ever.

```cpp
static std::string outstr = first_drawn_ ? " drawn at " : " shared at ";
```

I find an explanation: _Static variables are initialized only once, and then uninitialized._ The expression above not an assignment but a definition. So the value stored in `outstr` only acquired during initialization. So what we need to do is just make the expression a pure definition and then change its value.

> [关于静态变量“赋值无效问题”的探讨结果](https://blog.csdn.net/cinmyheart/article/details/9737533)
