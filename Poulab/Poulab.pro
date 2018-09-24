#-------------------------------------------------
#
# Project created by QtCreator 2018-06-06T13:05:09
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Poulab
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    mainmenuwidget.cpp \
    dbmanager.cpp \
    SqlDatum/sqldatum.cpp \
    TableModel/museumtablemodel.cpp \
    SqlTable/abstractsqltable.cpp \
    SqlTable/museumsqltable.cpp \
    AddItemWidget/addmuseumwidget.cpp \
    AddItemWidget/abstractadditemwidget.cpp \
    SqlDatum/sqlfield.cpp \
    AddItemWidget/addindividualwidget.cpp \
    SqlTable/individualsqltable.cpp \
    TableModel/individualtablemodel.cpp \
    SqlTable/speciessqltable.cpp \
    TableModel/speciestablemodel.cpp \
    AddItemWidget/addspecieswidget.cpp \
    ListModel/museumlistmodel.cpp \
    ListModel/specieslistmodel.cpp \
    SqlTable/materialtypesqltable.cpp \
    SqlTable/measurementtypesqltable.cpp \
    SqlTable/materialsqltable.cpp \
    SqlTable/measurementsqltable.cpp \
    TableModel/abstractsqltablemodel.cpp \
    TableModel/materialtablemodel.cpp \
    TableModel/materialtypetablemodel.cpp \
    TableModel/measurementtablemodel.cpp \
    TableModel/measurementtypetablemodel.cpp \
    ListModel/abstractsqllistmodel.cpp \
    ListModel/individuallistmodel.cpp \
    ListModel/materiallistmodel.cpp \
    ListModel/materialtypelistmodel.cpp \
    ListModel/measurementlistmodel.cpp \
    ListModel/measurementtypelistmodel.cpp \
    AddItemWidget/addmaterialtypewidget.cpp \
    TreeModel/materialtypetreemodel.cpp \
    TreeModel/abstractsqltreemodel.cpp \
    AddItemWidget/addmeasurementtypewidget.cpp \
    statisticswidget.cpp \
    AddItemWidget/addmaterialwidget.cpp \
    AddItemWidget/addmeasurementwidget.cpp \
    AddItemWidget/addallmeasurementswidget.cpp \
    ShowListWidget/showlistwidget.cpp \
    ShowListWidget/showmeasurementwidget.cpp \
    ShowListWidget/showmaterialtypetreewidget.cpp \
    ShowListWidget/showmeasurementtypewidget.cpp \
    ShowListWidget/copymeasurementtypedialog.cpp \
    CustomWidgets/mytableview.cpp \
    CustomWidgets/treebox.cpp \
    CustomWidgets/partiallyeditabletextbox.cpp \
    SqlDatum/quicksqlquery.cpp \
    SearchWidget/searchwidget.cpp \
    SearchWidget/joinform.cpp \
    SearchWidget/filterform.cpp \
    CustomWidgets/lineeditdialog.cpp

HEADERS += \
        mainwindow.h \
    mainmenuwidget.h \
    dbmanager.h \
    SqlDatum/sqldatum.h \
    TableModel/museumtablemodel.h \
    SqlTable/abstractsqltable.h \
    SqlTable/museumsqltable.h \
    AddItemWidget/addmuseumwidget.h \
    AddItemWidget/abstractadditemwidget.h \
    SqlDatum/sqlfield.h \
    AddItemWidget/addindividualwidget.h \
    SqlTable/individualsqltable.h \
    TableModel/individualtablemodel.h \
    SqlTable/speciessqltable.h \
    TableModel/speciestablemodel.h \
    AddItemWidget/addspecieswidget.h \
    ListModel/museumlistmodel.h \
    ListModel/specieslistmodel.h \
    SqlTable/materialtypesqltable.h \
    SqlTable/measurementtypesqltable.h \
    SqlTable/materialsqltable.h \
    SqlTable/measurementsqltable.h \
    TableModel/abstractsqltablemodel.h \
    TableModel/materialtablemodel.h \
    TableModel/materialtypetablemodel.h \
    TableModel/measurementtablemodel.h \
    TableModel/measurementtypetablemodel.h \
    ListModel/abstractsqllistmodel.h \
    ListModel/individuallistmodel.h \
    ListModel/materiallistmodel.h \
    ListModel/materialtypelistmodel.h \
    ListModel/measurementlistmodel.h \
    ListModel/measurementtypelistmodel.h \
    AddItemWidget/addmaterialtypewidget.h \
    TreeModel/materialtypetreemodel.h \
    TreeModel/abstractsqltreemodel.h \
    AddItemWidget/addmeasurementtypewidget.h \
    statisticswidget.h \
    AddItemWidget/addmaterialwidget.h \
    AddItemWidget/addmeasurementwidget.h \
    AddItemWidget/addallmeasurementswidget.h \
    ShowListWidget/showlistwidget.h \
    ShowListWidget/showmeasurementwidget.h \
    ShowListWidget/showmaterialtypetreewidget.h \
    ShowListWidget/showmeasurementtypewidget.h \
    ShowListWidget/copymeasurementtypedialog.h \
    CustomWidgets/mytableview.h \
    CustomWidgets/treebox.h \
    CustomWidgets/partiallyeditabletextbox.h \
    SqlDatum/quicksqlquery.h \
    SearchWidget/searchwidget.h \
    SearchWidget/joinform.h \
    SearchWidget/filterform.h \
    CustomWidgets/lineeditdialog.h

FORMS += \
        mainwindow.ui \
    mainmenuwidget.ui \
    AddItemWidget/addmuseumwidget.ui \
    AddItemWidget/additemwidget.ui \
    AddItemWidget/addindividualwidget.ui \
    AddItemWidget/addspecieswidget.ui \
    AddItemWidget/addmaterialtypewidget.ui \
    AddItemWidget/addmeasurementtypewidget.ui \
    statisticswidget.ui \
    AddItemWidget/addmaterialwidget.ui \
    AddItemWidget/addmeasurementwidget.ui \
    AddItemWidget/addallmeasurementswidget.ui \
    ShowListWidget/showlistwidget.ui \
    ShowListWidget/showmaterialtypetreewidget.ui \
    SearchWidget/searchwidget.ui

DISTFILES +=
