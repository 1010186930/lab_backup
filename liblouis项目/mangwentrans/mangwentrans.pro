QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        lib_depend/unistr/u16-mbtoucr.c \
        lib_depend/unistr/u16-to-u8.c \
        lib_depend/unistr/u32-to-u8.c \
        lib_depend/unistr/u8-uctomb-aux.c \
        lib_depend/unistr/u8-uctomb.c \
        main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


#arm:
#unix:!macx: LIBS += -L$$PWD/liblious_arm_lib/ -lliblious_linux_pc

#INCLUDEPATH += $$PWD/liblious_arm_lib
#DEPENDPATH += $$PWD/liblious_arm_lib

unix:!macx: LIBS += -L$$PWD/./ -lliblious_linux_pc

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.
