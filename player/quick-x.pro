TEMPLATE = subdirs
CONFIG += ordered

win32 {
    SUBDIRS = ../lib/proj.qt/libchipmunk.pro
}
SUBDIRS += \
    ../lib/proj.qt/libquickqt.pro \
    ./proj.qt/quick-x-player.pro

win32 {
    ../lib/proj.qt/libquickqt.pro.depends = ../lib/proj.qt/libchipmunk.pro
}
./proj.qt/quick-x-player.pro.depends = ../lib/proj.qt/libquickqt.pro
