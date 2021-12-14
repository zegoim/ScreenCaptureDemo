
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../ZegoExpress/lib/x86/ -lZegoExpressEngine
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../ZegoExpress/lib/x86/ -lZegoExpressEngine
else:unix: LIBS += -L$$PWD/../ZegoExpress/lib/x86/ -lZegoExpressEngine

INCLUDEPATH += $$PWD/../ZegoExpress/include
INCLUDEPATH += $$PWD/../ZegoExpress/include/internal
DEPENDPATH += $$PWD/../ZegoExpress/lib/x86

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../ZegoScreenCapture/libs/x86/ -lZegoScreenCapture
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../ZegoScreenCapture/libs/x86/ -lZegoScreenCapture
else:unix: LIBS += -L$$PWD/../ZegoScreenCapture/libs/x86/ -lZegoScreenCapture

INCLUDEPATH += $$PWD/../ZegoScreenCapture/include
DEPENDPATH += $$PWD/../ZegoScreenCapture/libs/x86

QT += widgets

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
