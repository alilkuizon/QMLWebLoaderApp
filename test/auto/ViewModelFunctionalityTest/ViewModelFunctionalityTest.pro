QT += testlib
QT -= gui

include(../../../src/src.pri)
CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_functionaltest.cpp
