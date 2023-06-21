QT       += core gui multimedia sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    base.cpp \
    bullet.cpp \
    effect.cpp \
    gameElement.cpp \
    gameLevel.cpp \
    gameOverForm.cpp \
    gamingForm.cpp \
    main.cpp \
    gameform.cpp \
    mapBlock.cpp \
    menuForm.cpp \
    modeChooseForm.cpp \
    recordForm.cpp \
    tank.cpp

HEADERS += \
    base.h \
    bullet.h \
    effect.h \
    gameElement.h \
    gameLevel.h \
    gameOverForm.h \
    gameform.h \
    gamingForm.h \
    mapBlock.h \
    menuForm.h \
    modeChooseForm.h \
    recordForm.h \
    tank.h

FORMS += \
    gameOverForm.ui \
    gameform.ui \
    gamingForm.ui \
    menuForm.ui \
    modeChooseForm.ui \
    recordForm.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    font.qrc \
    images.qrc \
    sound.qrc

RC_ICONS = tank.ico
