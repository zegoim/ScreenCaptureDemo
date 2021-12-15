include(ScreenCaptureDemo(Express SDK).pri)

DISTFILES += \
    ScreenCaptureDemo(Express SDK).pri \
    root_cert

RESOURCES += \
    ScreenCaptureDemo.qrc

FORMS += \
    ZegoCaptureView.ui \
    ZegoScreenCaptureDemo.ui \
    ZegoThumbnailView.ui

HEADERS += \
    CustomVideoCapture.h \
    ZegoCaptureView.h \
    ZegoCustomVideoSourceContext.h \
    ZegoScreenCaptureController.h \
    ZegoScreenCaptureDemo.h \
    ZegoScreenCaptureSettings.h \
    ZegoScreenCaptureSettings_p.h \
    ZegoThumbnailView.h

SOURCES += \
    CustomVideoCapture.cpp \
    ZegoCaptureView.cpp \
    ZegoScreenCaptureController.cpp \
    ZegoScreenCaptureDemo.cpp \
    ZegoScreenCaptureSettings.cpp \
    ZegoThumbnailView.cpp \
    main.cpp

win32:CONFIG(release, debug|release) {
    contains(DEFINES, WIN64) {
        LIBS += -L$$PWD/../ZegoExpress/lib/x64/ -lZegoExpressEngine
        LIBS += -L$$PWD/../ZegoScreenCapture/libs/x64/ -lZegoScreenCapture
        DEPENDPATH += $$PWD/../ZegoExpress/lib/x64
        DEPENDPATH += $$PWD/../ZegoScreenCapture/libs/x64

    } else {
        LIBS += -L$$PWD/../ZegoExpress/lib/x86/ -lZegoExpressEngine
        LIBS += -L$$PWD/../ZegoScreenCapture/libs/x86/ -lZegoScreenCapture
        DEPENDPATH += $$PWD/../ZegoExpress/lib/x86
        DEPENDPATH += $$PWD/../ZegoScreenCapture/libs/x86
    }
} else {
    contains(DEFINES, WIN64) {
        LIBS += -L$$PWD/../ZegoExpress/lib/x64/ -lZegoExpressEngine
        LIBS += -L$$PWD/../ZegoScreenCapture/libs/x64/ -lZegoScreenCapture
        DEPENDPATH += $$PWD/../ZegoExpress/lib/x64
        DEPENDPATH += $$PWD/../ZegoScreenCapture/libs/x64

    } else {
        LIBS += -L$$PWD/../ZegoExpress/lib/x86/ -lZegoExpressEngine
        LIBS += -L$$PWD/../ZegoScreenCapture/libs/x86/ -lZegoScreenCapture
        DEPENDPATH += $$PWD/../ZegoExpress/lib/x86
        DEPENDPATH += $$PWD/../ZegoScreenCapture/libs/x86
    }
}

INCLUDEPATH += $$PWD/../ZegoExpress/include
INCLUDEPATH += $$PWD/../ZegoExpress/include/internal
INCLUDEPATH += $$PWD/../ZegoScreenCapture/include


QT += widgets
