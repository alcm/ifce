#include <iostream>
#include <memory>
#include <vector>

class UsbDevice {
   public:
    virtual void AttachToUsbPort() const
    {
        std::cout << "Usb device attach logic." << std::endl;
    }
};

class SerialDevice {
   public:
    void AttachToSerialPort() const
    {
        std::cout << "Serial device attach logic." << std::endl;
    }
};

class UsbAdapter : public UsbDevice {
   public:
    UsbAdapter(const SerialDevice &device)
        : device_(device)
    {
    }

    void AttachToUsbPort() const override
    {
        std::cout << "Attaching serial port using adapter class." << std::endl;
        device_.AttachToSerialPort();
    }

   private:
    SerialDevice device_;
};

int main()
{
    SerialDevice serial_dev;
    std::vector<std::shared_ptr<UsbDevice>> devices{std::make_shared<UsbDevice>(),
                                                    std::make_shared<UsbAdapter>(serial_dev)};

    for (auto &dev : devices)
        dev->AttachToUsbPort();
}
