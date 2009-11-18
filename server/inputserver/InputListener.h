/*

  Copyright (c) 2009 Multimedia Systems - Cloud Gaming Project http://github.com/tv/C-WG3-1

  All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions
  are met:

  1. Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
  2. Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in the
     documentation and/or other materials provided with the distribution.
  3. Neither the name of authors nor the names of its contributors
     may be used to endorse or promote products derived from this software
     without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS IS'' AND
  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE
  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
  OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
  HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
  OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
  SUCH DAMAGE.
*/

#ifndef INPUTLISTENER_H
#define INPUTLISTENER_H

#include <QtGui>
#include <QtNetwork>
#include <QObject>
#include <QUdpSocket>
#include <QKeyEvent>
#include <QEvent>
#include <QHostAddress>
#include <QByteArray>
#include <X11/Xlib.h>
#include <X11/extensions/XTest.h>
#include <QX11Info>
#include <iostream>

class InputListener: public QObject
{
    Q_OBJECT
    
    static const char KEYPRESS =       0x00;
    static const char KEYRELEASE =     0x01;
    static const char MOUSEX =         0x02;
    static const char MOUSEY =         0x03;
    static const char MOUSE1PRESS =    0x04;
    static const char MOUSE1RELEASE =  0x05;
    static const char MOUSE2PRESS =    0x06;
    static const char MOUSE2RELEASE =  0x07;
    public:
        InputListener(QObject * parent = 0);
        ~InputListener();
        
    private slots:
        
        void processPendingDatagrams();
        
    private:
        quint32 parseKeycode(QByteArray string);
		uint InputListener::handle_qkey(QKeyEvent *event);
        QUdpSocket *udpSocket;
		QProcess *game;
        
};

#endif // INPUTLISTENER_H
