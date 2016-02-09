HEADERS       = mainwindow.h \
    PaintTunnel/tunnel.h \
    PaintTunnel/tunnelWidget.h \
    UIClasses/configuration.h \
    UIClasses/personnelMG.h \
    UIClasses/anchorMG.h \
    UIClasses/netconfigMG.h \
    CentralWidget/window.h \
    DataBase/singleton.h \
    Controller/NetWork/receiver.h \
    Controller/Base/baseType.h \
    Controller/Algorithmic/rssi2postionXY.h \
    Controller/controller.h \
    UIClasses/dutyMG.h \
    UIClasses/titleMG.h

SOURCES       = main.cpp \
                mainwindow.cpp \
    PaintTunnel/tunnel.cpp \
    PaintTunnel/tunnelWidget.cpp \
    UIClasses/configuration.cpp \
    UIClasses/personnelMG.cpp \
    UIClasses/anchorMG.cpp \
    UIClasses/netconfigMG.cpp \
    CentralWidget/window.cpp \
    DataBase/singleton.cpp \
    Controller/NetWork/receiver.cpp \
    Controller/Algorithmic/rssi2postionXY.cpp \
    Controller/controller.cpp \
    UIClasses/dutyMG.cpp \
    UIClasses/titleMG.cpp

QT           += core widgets opengl network sql

# install
target.path = $$[QT_INSTALL_EXAMPLES]/opengl/hellogl2
INSTALLS += target

FORMS += \
    UIClasses/configuration.ui \
    UIClasses/personnelMG.ui \
    UIClasses/anchorMG.ui \
    UIClasses/netconfigMG.ui \
    UIClasses/dutyMG.ui \
    UIClasses/titleMG.ui
