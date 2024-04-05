#include <iostream>
#include <memory>
#include <mutex>
#include <unordered_map>

class Cart
{
 public:
    Cart(const Cart &) = delete;
    Cart &operator=(const Cart &) = delete;

    void add(const std::string &good, int number)
    {
        if (buyerlist_.count(good) > 0) {
            buyerlist_[good] += number;
        } else {
            buyerlist_.emplace(good, number);
        }
    }

    void showCart()
    {
        if (!buyerlist_.empty()) {
            for (const auto &[name, num] : buyerlist_) {
                std::cout << name << " " << num << '\n';
            }
        }
    }

    static std::shared_ptr<Cart> getInstance()
    {
        auto cart = cart_.lock();
        if (cart == nullptr) {
            std::unique_lock<std::mutex> lock(mt_);
            if (cart == nullptr) {
                cart.reset(new Cart());
                cart_ = cart;
            }
        }
        return cart;
    }

 private:
    Cart() = default;

 private:
    static std::weak_ptr<Cart> cart_;
    static std::mutex mt_;
    std::unordered_map<std::string, int> buyerlist_;
};

std::weak_ptr<Cart> Cart::cart_;
std::mutex Cart::mt_;

int main()
{
    std::string good;
    int num;
    auto cart = Cart::getInstance();
    while (std::cin >> good >> num) {
        if (good == "NONE") {
            break;
        }
        cart->add(good, num);
    }
    cart->showCart();
    return 0;
}
