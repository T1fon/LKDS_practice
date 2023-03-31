QT += quick qml sql serialport

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
    Controller/controller_databasemanager.h \
    Controller/controller_keytable.h \
    Controller/SerialManager/ControllerSerialManager.h \
    Model/COMPortModel/COMPortModel.h \
    Model/model_database.h \
    Model/SerialManager/ModelSerialManager.h \
    View/FifthWindow/fifthwindow.h \
    View/FirstWindow/firstwindow.h \
    View/FouthWindow/fouthwindow.h \
    View/SecondWindow/secondwindow.h \
    View/SettingsWindow/SettingsWindow.h \
    View/ThirdWindow/thirdwindow.h
SOURCES += \
    Controller/controller_databasemanager.cpp \
    Controller/controller_keytable.cpp \
    Controller/SerialManager/ControllerSerialManager.cpp \
    Model/COMPortModel/COMPortModel.cpp \
    Model/model_database.cpp \
    Model/SerialManager/ModelSerialManager.cpp \
    View/FifthWindow/fifthwindow.cpp \
    View/FirstWindow/firstwindow.cpp \
    View/FouthWindow/fouthwindow.cpp \
    View/SecondWindow/secondwindow.cpp \
    View/SettingsWindow/SettingsWindow.cpp \
    View/ThirdWindow/thirdwindow.cpp \
    main.cpp

DISTFILES += \
    View/FifthWindow/FifthWindow.qml \
    View/FirstWindow/FirstWindow.qml \
    View/FouthWindow/FouthWindow.qml \
    View/SecondWindow/AddCompany.qml \
    View/SecondWindow/SecondWindow.qml \
    View/SecondWindow/TableModeler.qml \
    View/ThirdWindow/TableModeler_th.qml \
    View/ThirdWindow/ThirdWindow.qml \
    View/SettingsWindow/SettingsWindow.qml
