greaterThan(QT_MAJOR_VERSION, 4){
    cache()
}

include(quick-x-src.pri)

TEMPLATE = lib
LIBS += $${COCOS2DX_SYSTEM_LIBS}
DESTDIR = $${LIB_OUTPUT_DIR}
TARGET = $${QUICK_LIB}

CONFIG += static
