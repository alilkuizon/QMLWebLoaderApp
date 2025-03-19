QT += quick
TARGET = QMLWebLoader  # Sets the executable name
DESTDIR = $$PWD/build
QMAKE_CXXFLAGS += -Wunused-parameter -Werror

HEADERS += \
    mainviewmodel.h \
    webserver.h

SOURCES += \
        main.cpp \
    mainviewmodel.cpp \
    webserver.cpp

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


