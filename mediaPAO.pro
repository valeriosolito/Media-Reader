QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    src/AbsItem.cpp \
    src/Album.cpp \
    src/Film.cpp \
    src/Fumetto.cpp \
    src/ItemRepo.cpp \
    JSon/ItemReader.cpp \
    JSon/Json.cpp \
    JSon/JsonFile.cpp \
    visitors/JsonVisitor.cpp \
    widgets/classPanel.cpp \
    widgets/itemCard.cpp \
    widgets/itemDetail.cpp \
    widgets/itemGrid.cpp

HEADERS += \
    JSon/ItemReader.h \
    JSon/Json.h \
    JSon/JsonFile.h \
    header/AbsItem.h \
    header/Album.h \
    header/Film.h \
    header/Fumetto.h \
    header/ItemRepo.h \
    mainwindow.h \
    visitors/visitor.h \
    visitors/JsonVisitor.h \
    widgets/addItem.h \
    widgets/classPanel.h \
    widgets/itemCard.h \
    widgets/itemDetail.h \
    widgets/itemGrid.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    items.json

RESOURCES += \
    resources.qrc
