win32 {
    INCLUDEPATH += $$PWD/win
    LIBS += -L$$PWD/win -lTrackerbird
}

mac {
    LIBS += \
    -framework Cocoa \
    -framework Foundation \
    -framework CoreFoundation \
    -framework AppKit \
    -framework Security \
    -framework SystemConfiguration \
    -framework WebKit \
    -framework IOKit
    LIBS += -lz
    LIBS += -L$$PWD/3rd/TrackerbirdSDK/mac -lTrackerbirdSDK-MacOS-CPP
}
