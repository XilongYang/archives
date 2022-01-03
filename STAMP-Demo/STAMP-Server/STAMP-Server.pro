QT -= gui
QT += network

CONFIG += c++11 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    config.h \
    stamp.h

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build/Library/release/ -lSTAMP-Protocol
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build/Library/debug/ -lSTAMP-Protocol
else:unix: LIBS += -L$$PWD/../build/Library/ -lSTAMP-Protocol

INCLUDEPATH += $$PWD/../build/Library
DEPENDPATH += $$PWD/../build/Library

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../build/Library/release/libSTAMP-Protocol.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../build/Library/debug/libSTAMP-Protocol.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../build/Library/release/STAMP-Protocol.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../build/Library/debug/STAMP-Protocol.lib
else:unix: PRE_TARGETDEPS += $$PWD/../build/Library/libSTAMP-Protocol.a
