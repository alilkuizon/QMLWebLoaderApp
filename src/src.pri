INCLUDEPATH += $$PWD

QT+=quick
SOURCES += \
    $$PWD/clientViewModel.cpp

HEADERS += \
    $$PWD/clientViewModel.h

unix {
    LIBS += -ludev
    INCLUDEPATH += /usr/include/libudev
}
