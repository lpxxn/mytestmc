#-------------------------------------------------
#
# Project created by QtCreator 2019-10-17T11:53:21
#
#-------------------------------------------------

QT       += core gui network


message('------------')
PROJECT_SOURCE_TREE = $$PWD
sub_dir = $$_PRO_FILE_PWD_
sub_dir ~= s,^$$re_escape($$PWD),,

PROJECT_BUILD_TREE = $$clean_path($$OUT_PWD)

PROJECT_BUILD_TREE ~= s,$$re_escape($$sub_dir)$,,
message($$PROJECT_BUILD_TREE)
message($$QMAKE_HOST.arch)

message($$QMAKESPEC)

macx {
 CURRENTHOST = MAC
}
linux {
 CURRENTHOST = LINUX
}
win32 {
 CURRENTHOST = WIN
}
unix: !macx {
 CURRENTHOST = UNIX
}
isEmpty(CURRENTHOST) {
 CURRENTHOST = HOST
}

message($$CURRENTHOST)
CONFIG(debug, debug|release) {
    DEBUG_RELEASE = DEBUG
} else {
    DEBUG_RELEASE = RELEASE
}

PROJECT_COMP_TYPE = $${CURRENTHOST}_$${QMAKE_HOST.arch}_$$DEBUG_RELEASE
PROJECT_APP_PATH = $$PROJECT_SOURCE_TREE/bin/$$PROJECT_COMP_TYPE

message($$PROJECT_APP_PATH)
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

DESTDIR = $$PROJECT_APP_PATH

TARGET = cafeteria
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
    common/configdata.cpp \
    common/loginconfigdata.cpp \
    common/mrequestcuser.cpp \
    common/settingconfig.cpp \
    common/util.cpp \
        main.cpp \
        mainwidget.cpp \
    mcsetting.cpp \
    supplierform.cpp

HEADERS += \
    common/configdata.h \
    common/constants.h \
    common/loginconfigdata.h \
    common/mrequestcuser.h \
    common/settingconfig.h \
    common/util.h \
        mainwidget.h \
    mcsetting.h \
    supplierform.h

FORMS += \
        mainwidget.ui \
        mcsetting.ui \
        supplierform.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
