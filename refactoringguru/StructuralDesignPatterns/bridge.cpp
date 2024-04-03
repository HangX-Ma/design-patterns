#include <iostream>
#include <memory>

class Device
{
 public:
    Device() { std::cout << "Device Constructor" << '\n'; }
    virtual ~Device() { std::cout << "Device Destructor" << '\n'; }

    virtual bool isEnabled() { return power_on_; };
    virtual void enable() { power_on_ = true; }
    virtual void disable() { power_on_ = false; }
    virtual void setChannel(uint8_t channel) { channel_ = channel; }
    virtual uint8_t getChannel() { return channel_; }
    virtual void setVolume(uint8_t volume)
    {
        volume_ = std::min(volume, static_cast<uint8_t>(100));
    }
    virtual uint8_t getVolume() { return volume_; }

    virtual void info() {}

 private:
    bool power_on_{false};
    uint8_t channel_{0};
    uint8_t volume_{20};
};

class Remote
{
 public:
    explicit Remote(std::unique_ptr<Device> device) : device(std::move(device)) {}

    void togglePower()
    {
        if (device->isEnabled()) {
            device->disable();
        }
        else {
            device->enable();
        }
    }
    void volumeDown() { device->setVolume(device->getVolume() - 10); }
    void volumeUp() { device->setVolume(device->getVolume() + 10); }
    void channelDown() { device->setChannel(device->getChannel() - 1); }
    void channelUp() { device->setChannel(device->getChannel() + 1); }
    void getInfo() { device->info(); }

 protected:
    std::unique_ptr<Device> device;
};

class AdvancedRemote : public Remote
{
 public:
    explicit AdvancedRemote(std::unique_ptr<Device> device) : Remote(std::move(device)) {}

    void mute() { device->setVolume(0); }
};

class TV : public Device
{
 public:
    TV() { std::cout << "TV Constructor" << '\n'; }
    ~TV() override { std::cout << "TV Destructor" << '\n'; }
    void info() override { std::cout << "Device Type: TV" << '\n'; };
};

class Radio : public Device
{
 public:
    Radio() { std::cout << "Radio Constructor" << '\n'; }
    ~Radio() override { std::cout << "Radio Destructor" << '\n'; }
    void info() override { std::cout << "Device Type: Radio" << '\n'; };
};

int main()
{
    std::unique_ptr<Device> tv = std::make_unique<TV>();
    std::unique_ptr<Device> raido = std::make_unique<Radio>();

    auto tv_remote = std::make_unique<Remote>(std::move(tv));
    auto radio_remote = std::make_unique<Remote>(std::move(raido));

    tv_remote->getInfo();
    radio_remote->getInfo();

    return 0;
}
