#include <iostream>
#include <memory>
#include <unordered_map>
#include <vector>

class Mediator;
class UserBase
{
 public:
    explicit UserBase(std::unique_ptr<Mediator> mediator = nullptr) : mediator(std::move(mediator))
    {
    }

    virtual ~UserBase() = default;

    void setMediator(std::unique_ptr<Mediator> new_mediator)
    {
        this->mediator = std::move(new_mediator);
    }

    virtual void sendMessage(const std::string &message) = 0;

    virtual void receiveMessage(const std::shared_ptr<UserBase> &sender, const std::string &message)
        = 0;

 protected:
    std::unique_ptr<Mediator> mediator;
};

class Mediator
{
 public:
    virtual ~Mediator() = default;
    virtual void notify(std::shared_ptr<UserBase> sender, const std::string &message) = 0;
};

class ChatRoomMediator : public Mediator
{
 public:
    void addUser(std::shared_ptr<UserBase> new_user) { user_list_.push_back(std::move(new_user)); }

    void notify(std::shared_ptr<UserBase> sender, const std::string &message) override
    {
        for (const auto &receiver : user_list_) {
            if (receiver != sender) {
                receiver->receiveMessage(sender, message);
            }
        }
    }

 private:
    std::vector<std::shared_ptr<UserBase>> user_list_;
};

class User : public UserBase, public std::enable_shared_from_this<UserBase>
{
 public:
    explicit User(std::string name) : name_(std::move(name)) {}

    void sendMessage(const std::string &message) override
    {
        mediator->notify(shared_from_this(), message);
    }

    void receiveMessage([[maybe_unused]] const std::shared_ptr<UserBase> &sender,
                        const std::string &message) override
    {
        std::string messages = name_ + " received: " + message;
        std::cout << messages << '\n';
    }

 private:
    std::string name_;
};

int main()
{
    int n;
    std::cin >> n;
    std::string user_name;
    auto mediator = std::make_unique<ChatRoomMediator>();
    std::unordered_map<std::string, std::shared_ptr<User>> users;
    for (int i = 0; i < n; ++i) {
        std::cin >> user_name;
        auto new_user = std::make_shared<User>(user_name);
        users.emplace(user_name, new_user);
        mediator->addUser(new_user);
    }

    std::string message;
    while (std::cin >> user_name >> message) {
        mediator->notify(users[user_name], message);
    }

    return 0;
}
