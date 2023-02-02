QT += quick qml

SOURCES += \
        View/FirstWindow/firstwindow.cpp \
        View/SecondWindow/secondwindow.cpp \
        main.cpp

resources.files = main.qml 
resources.prefix = /$${TARGET}
RESOURCES += resources \
    Source.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    View/FirstWindow/firstwindow.h \
    View/SecondWindow/secondwindow.h

DISTFILES += \
    View/FirstWindow/FirstWindow.qml \
    View/SecondWindow/SecondWindow.qml
