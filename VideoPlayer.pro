QT += core gui widgets multimedia multimediawidgets

CONFIG += c++11


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        src/a_video.cpp \
        src/the_appbar.cpp \
        src/the_buttons.cpp \
        src/the_controls.cpp \
        src/the_help.cpp \
        src/the_player.cpp \
        src/the_recents.cpp \
        src/the_settings.cpp \
        src/the_store.cpp \
        src/the_tutorial.cpp \
        src/the_utils.cpp \
        src/the_video.cpp \
        src/the_window.cpp \
        src/main.cpp

HEADERS += \
    src/a_video.h \
    src/the_appbar.h \
    src/the_buttons.h \
    src/the_controls.h \
    src/the_help.h \
    src/the_player.h \
    src/the_recents.h \
    src/the_settings.h \
    src/the_store.h \
    src/the_tutorial.h \
    src/the_utils.h \
    src/the_video.h \
    src/the_window.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    src/icons.qrc \
    src/styles.qrc

# Application icons
RC_ICONS += src/icons/htvp-icon.ico # Win32
ICON = src/icons/htvp-icon.icns # MacOS

TARGET = HTVP