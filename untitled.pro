#-------------------------------------------------
#
# Project created by QtCreator 2018-09-14T04:51:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = untitled
TEMPLATE = app

INCLUDEPATH += /usr/local/include
LIBS += -L/usr/local/lib \
-lopencv_calib3d \
-lopencv_core \
-lopencv_dnn \
-lopencv_features2d \
-lopencv_flann \
-lopencv_highgui \
-lopencv_imgcodecs \
-lopencv_imgproc \
-lopencv_ml \
-lopencv_objdetect \
-lopencv_photo \
-lopencv_shape \
-lopencv_stitching \
-lopencv_superres \
-lopencv_video \
-lopencv_videoio \
-lopencv_videostab

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui
#debug: {
#LIBS += -L/usr/local/lib \
#-lopencv_calib3d341d \
#-lopencv_core341d \
#-lopencv_dnn341d \
#-lopencv_features2d341d \
#-lopencv_flann341d \
#-lopencv_highgui341d \
#-lopencv_imgcodecs341d \
#-lopencv_imgproc341d \
#-lopencv_ml341d \
#-lopencv_objdetect341d \
#-lopencv_photo341d \
#-lopencv_shape341d \
#-lopencv_stitching341d \
#-lopencv_superres341d \
#-lopencv_video341d \
#-lopencv_videoio341d \
#-lopencv_videostab341d
#}



