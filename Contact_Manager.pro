QT += core gui widgets sql network
# Mysql server paths:
INCLUDEPATH += "C:\Program Files\MySQL\MySQL Server 8.0\include"
LIBS += -L"C:\Program Files\MySQL\MySQL Server 8.0\lib" -lmysql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17



# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    auth.cpp \
    contactmanager.cpp \
    databasemanager.cpp \
    main.cpp \
    mainwin.cpp \
    mainwindow.cpp

HEADERS += \
    auth.h \
    contactmanager.h \
    databasemanager.h \
    mainwin.h \
    mainwindow.h

FORMS += \
    mainwin.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    img.qrc
