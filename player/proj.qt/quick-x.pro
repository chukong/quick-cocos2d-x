TEMPLATE = subdirs
CONFIG += ordered
win32
{
    SUBDIRS = ../../lib/proj.qt/libchipmunk.pro
}

SUBDIRS += \
    ../../lib/proj.qt/libquickqt.pro \
    ./quick-x-player.pro

