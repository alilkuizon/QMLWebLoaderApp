QT += quick
TARGET = QMLWebLoaderApp  # Sets the executable name
DESTDIR = $$PWD/../binaries
QMAKE_CXXFLAGS += -Wunused-parameter -Werror

HEADERS += \
    clientViewModel.h \
    webserver.h

SOURCES += \
    clientViewModel.cpp \
        main.cpp \
    webserver.cpp

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

unix {
    LIBS += -ludev
    INCLUDEPATH += /usr/include/libudev

    QMAKE_POST_LINK += chmod 755 $$DESTDIR/$$TARGET

    QMAKE_LFLAGS += -Wl,-rpath,\'\$$ORIGIN/gcc_64/lib\'
    QMAKE_LFLAGS += -Wl,--disable-new-dtags
}

