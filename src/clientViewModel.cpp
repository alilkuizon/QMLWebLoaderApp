#include "clientViewModel.h"
#include <QDebug>

ClientViewModel::ClientViewModel(QQuickView *mView, QObject *) : view(mView)
{
    timerCount = 0;
    connect(&timer, &QTimer::timeout, this, &ClientViewModel::onTimeOut);
    timer.setInterval(1000);
}

void ClientViewModel::renderView()
{
    view->setTitle("QML Web Loader App");
    view->setWidth(800);
    view->setHeight(480);
    view->setResizeMode(QQuickView::SizeRootObjectToView);
    view->rootContext()->setContextProperty("viewModel", this);
    view->show();
}

void ClientViewModel::connecttoWebServer(WebServer *newserver)
{
    server = newserver;
    server->findServerPort();
}

QString ClientViewModel::elapsedTime() const
{
    return QString::number(timerCount);
}

void ClientViewModel::toggleTimer()
{
    qDebug() << "Timer toggled";
    if (timer.isActive())
    {
        timerCount = 0;
        timer.stop();
        emit elapsedTimeChanged();
    }
    else
    {
        timer.start();
    }
    emit timerStatusChanged();
}

void ClientViewModel::fetchUSBDeviceList()
{
    m_devices.clear();
    m_devices = getUsbDevicesList();
    emit devicesChanged();
}

void ClientViewModel::exit()
{
    server->exit();
}

void ClientViewModel::cleanup()
{
    server->cleanup();
}

bool ClientViewModel::isTimerActive() const
{
    return timer.isActive();
}

QStringList ClientViewModel::devices() const
{
    return m_devices;
}

QStringList ClientViewModel::getUsbDevicesList()
{
    QStringList deviceList;

#ifdef Q_OS_LINUX
    struct udev *udev = udev_new();
    if (!udev)
    {
        return deviceList;
    }

    struct udev_enumerate *enumerate = udev_enumerate_new(udev);
    udev_enumerate_add_match_subsystem(enumerate, "usb");

    udev_enumerate_add_match_property(enumerate, "DEVTYPE", "usb_device");
    udev_enumerate_scan_devices(enumerate);

    struct udev_list_entry *devices = udev_enumerate_get_list_entry(enumerate);
    struct udev_list_entry *entry;

    udev_list_entry_foreach(entry, devices)
    {
        const char *path = udev_list_entry_get_name(entry);
        struct udev_device *dev = udev_device_new_from_syspath(udev, path);

        if (dev)
        {
            const char *vendor = udev_device_get_sysattr_value(dev, "idVendor");   // Vendor ID
            const char *product = udev_device_get_sysattr_value(dev, "idProduct"); // Product ID
            const char *manufacturer =
                udev_device_get_sysattr_value(dev, "manufacturer"); // Human-readable Vendor
            const char *product_name =
                udev_device_get_sysattr_value(dev, "product");  // Human-readable Product
            const char *devpath = udev_device_get_devpath(dev); // Get device location

            // Fallback to vendor/product ID if manufacturer/product_name is missing
            QString usbModel =
                product_name ? QString(product_name)
                             : (product ? QString("Product ID: %1").arg(product) : "Unknown Model");
            QString usbVendor =
                manufacturer ? QString(manufacturer)
                             : (vendor ? QString("Vendor ID: %1").arg(vendor) : "Unknown Vendor");
            QString usbLocation = devpath ? QString(devpath) : "Unknown Location";

            QString deviceInfo = QString("Model: %1, Vendor: %2, Location: %3")
                                     .arg(usbModel, usbVendor, usbLocation);

            deviceList.append(deviceInfo);
            udev_device_unref(dev);
        }
    }

    udev_enumerate_unref(enumerate);
    udev_unref(udev);

#elif defined(Q_OS_MACOS)
    CFMutableDictionaryRef matchingDict = IOServiceMatching(kIOUSBDeviceClassName);
    if (matchingDict)
    {
        io_iterator_t iter = 0;
        if (IOServiceGetMatchingServices(kIOMasterPortDefault, matchingDict, &iter) == KERN_SUCCESS)
        {
            io_service_t device;
            while ((device = IOIteratorNext(iter)))
            {
                CFStringRef productName = (CFStringRef)IORegistryEntryCreateCFProperty(
                    device, CFSTR(kUSBProductString), kCFAllocatorDefault, 0);
                CFStringRef manufacturerName = (CFStringRef)IORegistryEntryCreateCFProperty(
                    device, CFSTR(kUSBVendorString), kCFAllocatorDefault, 0);

                QString deviceInfo;
                if (productName && manufacturerName)
                {
                    deviceInfo = QString("%1 %2")
                                     .arg(QString::fromCFString(manufacturerName))
                                     .arg(QString::fromCFString(productName));
                }
                else if (productName)
                {
                    deviceInfo = QString::fromCFString(productName);
                }
                else
                {
                    deviceInfo = "Unknown USB device";
                }

                deviceList.append(deviceInfo);

                if (productName)
                    CFRelease(productName);
                if (manufacturerName)
                    CFRelease(manufacturerName);
                IOObjectRelease(device);
            }
            IOObjectRelease(iter);
        }
    }
#else
    // Fallback for unsupported platforms
    deviceList.append("USB device detection not supported on this platform");
#endif

    return deviceList;
}

void ClientViewModel::onTimeOut()
{
    timerCount += 1;
    emit elapsedTimeChanged();
}
