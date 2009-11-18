#include "VLCWidget.h"

/* libVLC and Qt sample code
 * Copyright © 2009 Alexander Maringer <maringer@maringer-it.de>
 */

#include <QVBoxLayout>
#include <QPushButton>
#include <QSlider>
#include <QTimer>
#include <QFrame>

VLCWidget::VLCWidget(QString file, QStatusBar *statusBar, QWidget *parent)
: QWidget(parent)
{
    //preparation of the vlc command
    const char * const vlc_args[] = {
              "-I", "dummy", /* Don't use any interface */
              "--ignore-config", /* Don't use VLC's config */
              "--extraintf=logger", //log anything
              "--verbose=2", //be much more verbose then normal for debugging purpose
              "--plugin-path=\\plugins\\" };

    _isPlaying=false;

    //Initialize an instance of vlc
    //a structure for the exception is neede for this initalization
    libvlc_exception_init(&_vlcexcep);

    //create a new libvlc instance
    _vlcinstance=libvlc_new(sizeof(vlc_args) / sizeof(vlc_args[0]), vlc_args,&_vlcexcep);  //tricky calculation of the char space used
    raise (&_vlcexcep);

    //media
    _m = libvlc_media_new (_vlcinstance, file.toAscii(), &_vlcexcep);
    raise(&_vlcexcep);

    //media player
    _mp = libvlc_media_player_new_from_media(_m, &_vlcexcep);
    raise(&_vlcexcep);

    #if defined(Q_OS_WIN)
        //libvlc_media_player_set_drawable(_mp, reinterpret_cast<unsigned int>(_videoWidget->winId()), &_vlcexcep );
        //libvlc_media_player_set_hwnd(_mp, _videoWidget->winId(), &_vlcexcep ); // for vlc 1.0
        libvlc_media_player_set_hwnd(_mp, this->winId(), &_vlcexcep ); // for vlc 1.0

    #elif defined(Q_OS_MAC)
        //libvlc_media_player_set_drawable(_mp, _videoWidget->winId(), &_vlcexcep );
        //libvlc_media_player_set_agl (_mp, _videoWidget->winId(), &_vlcexcep); // for vlc 1.0
        libvlc_media_player_set_agl (_mp, this->winId(), &_vlcexcep); // for vlc 1.0
    #else //Linux
        //libvlc_media_player_set_drawable(_mp, _videoWidget->winId(), &_vlcexcep );
        //libvlc_media_player_set_xwindow(_mp, _videoWidget->winId(), &_vlcexcep ); // for vlc 1.0
        libvlc_media_player_set_xwindow(_mp, this->winId(), &_vlcexcep ); // for vlc 1.0
    #endif
    raise(&_vlcexcep);

    /* Play */
    libvlc_media_player_play (_mp, &_vlcexcep );
    raise(&_vlcexcep);

    _isPlaying=true;

    // Create a media player playing environement
    //_mp = libvlc_media_player_new (_vlcinstance, &_vlcexcep);
    //raise (&_vlcexcep);

    this->resize(800,600);
    this->show();
}

//desctructor
VLCWidget::~VLCWidget()
{
    /* Stop playing */
    libvlc_media_player_stop (_mp, &_vlcexcep);

    /* Free the media_player */
    libvlc_media_player_release (_mp);

    libvlc_release (_vlcinstance);
    raise (&_vlcexcep);
}

/*
void VLCWidget::playFile(QString file)
{
    //the file has to be in one of the following formats /perhaps a little bit outdated)

    [file://]filename              Plain media file
    http://ip:port/file            HTTP URL
    ftp://ip:port/file             FTP URL
    mms://ip:port/file             MMS URL
    screen://                      Screen capture
    [dvd://][device][@raw_device]  DVD device
    [vcd://][device]               VCD device
    [cdda://][device]              Audio CD device
    udp:[[<source address>]@[<bind address>][:<bind port>]]


    // Create a new LibVLC media descriptor
    _m = libvlc_media_new (_vlcinstance, file.toAscii(), &_vlcexcep);
    raise(&_vlcexcep);

    libvlc_media_player_set_media (_mp, _m, &_vlcexcep);
    raise(&_vlcexcep);

    // /!\ Please note /!\
    //
    // passing the widget to the lib shows vlc at which position it should show up
    // vlc automatically resizes the video to the ´given size of the widget
    // and it even resizes it, if the size changes at the playing

    //Get our media instance to use our window
    #if defined(Q_OS_WIN)
        //libvlc_media_player_set_drawable(_mp, reinterpret_cast<unsigned int>(_videoWidget->winId()), &_vlcexcep );
        //libvlc_media_player_set_hwnd(_mp, _videoWidget->winId(), &_vlcexcep ); // for vlc 1.0
        libvlc_media_player_set_hwnd(_mp, this->winId(), &_vlcexcep ); // for vlc 1.0

    #elif defined(Q_OS_MAC)
        //libvlc_media_player_set_drawable(_mp, _videoWidget->winId(), &_vlcexcep );
        //libvlc_media_player_set_agl (_mp, _videoWidget->winId(), &_vlcexcep); // for vlc 1.0
        libvlc_media_player_set_agl (_mp, this->winId(), &_vlcexcep); // for vlc 1.0
    #else //Linux
        //libvlc_media_player_set_drawable(_mp, _videoWidget->winId(), &_vlcexcep );
        //libvlc_media_player_set_xwindow(_mp, _videoWidget->winId(), &_vlcexcep ); // for vlc 1.0
        libvlc_media_player_set_xwindow(_mp, this->winId(), &_vlcexcep ); // for vlc 1.0
    #endif
    raise(&_vlcexcep);

    // Play
    libvlc_media_player_play (_mp, &_vlcexcep );
    raise(&_vlcexcep);

    _isPlaying=true;

    //libvlc_video_set_mouse_input(_mp, 0);
    //raise(&_vlcexcep);


    this->resize(800,600);
    //libvlc_video_set_scale(_mp, 1.0, &_vlcexcep );
    //raise(&_vlcexcep);
    //int h = libvlc_video_get_height (_mp, &_vlcexcep );
    //int w = libvlc_video_get_width (_mp, &_vlcexcep );
    //_videoWidget->resize(100,h);

}*/

/*
void VLCWidget::updateInterface()
{
    if(!_isPlaying)
        return;

    // It's possible that the vlc doesn't play anything
    // so check before
    libvlc_media_t *curMedia = libvlc_media_player_get_media (_mp, &_vlcexcep);
    libvlc_exception_clear(&_vlcexcep);
    if (curMedia == NULL)
        return;
}*/
void VLCWidget::raise(libvlc_exception_t * ex)
{
    if (libvlc_exception_raised (ex))
    {
         fprintf (stderr, "error: %s\n", libvlc_exception_get_message(ex));
         exit (-1);
    }
}
