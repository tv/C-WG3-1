#ifndef VLCWIDGET_H
#define VLCWIDGET_H

#include <iostream>
#include <cstdio>
#include "vlc/vlc.h"

#include <QWidget>
#include <QStatusBar>

#include <QVBoxLayout>
#include <QPushButton>
#include <QSlider>
#include <QTimer>
#include <QFrame>

class QVBoxLayout;
class QPushButton;
class QTimer;
class QFrame;
class QSlider;

//#define POSITION_RESOLUTION 10000

class VLCWidget : public QWidget
{
    Q_OBJECT
    bool _isPlaying;
    libvlc_exception_t _vlcexcep;
    libvlc_instance_t *_vlcinstance;
    libvlc_media_player_t *_mp;
    libvlc_media_t *_m;

public:
    VLCWidget(QString str, QStatusBar* statusBar, QWidget* parent = 0);
    ~VLCWidget();
    void raise(libvlc_exception_t * ex);

};

#endif // VLCWIDGET_H
