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

#include "InputListener.h"

using namespace std;

InputListener::InputListener(QObject* parent): QObject(parent)
{
    udpSocket = new QUdpSocket();
    if(udpSocket->bind(45455) == -1)
    {
        cout << "Socketin bindaus epäonnistui" << endl;
        exit(1);
    }

    game = new ThreadHandler(this);
    glcplay = new QProcess(this);
    ffmpeg = new QProcess(this);

    connect(this, SIGNAL(startGameProcess(QString)), game, SLOT(runProcess(QString)));

	
    connect(udpSocket, SIGNAL(readyRead()), this, SLOT(processPendingDatagrams()));
}

InputListener::~InputListener()
{
    udpSocket->close();
    game->exit();
    ffmpeg->close();
    glcplay->close();
}

uint InputListener::handle_qkey(QKeyEvent *event)
{
    int qkey = event->key();

    uint xkeysym;


    switch (qkey) {
        case Qt::Key_Escape: xkeysym = XK_Escape; break;
        case Qt::Key_Tab: xkeysym = XK_Tab; break;
        case Qt::Key_Backspace: xkeysym = XK_BackSpace; break;
        case Qt::Key_Return: xkeysym = XK_Return; break;
        case Qt::Key_Insert: xkeysym = XK_Insert; break;
        case Qt::Key_Delete: xkeysym = XK_Delete; break;
        case Qt::Key_Pause: xkeysym = XK_Pause; break;
        case Qt::Key_Print: xkeysym = XK_Print; break;
        case Qt::Key_SysReq: xkeysym = XK_Sys_Req; break;
        case Qt::Key_Clear: xkeysym = XK_Clear; break;
        case Qt::Key_Home: xkeysym = XK_Home; break;
        case Qt::Key_End: xkeysym = XK_End; break;
        case Qt::Key_Left: xkeysym = XK_Left; break;
        case Qt::Key_Up: xkeysym = XK_Up; break;
        case Qt::Key_Right: xkeysym = XK_Right; break;
        case Qt::Key_Down: xkeysym = XK_Down; break;
        case Qt::Key_Shift: xkeysym = XK_Shift_L; break;
        case Qt::Key_Control: xkeysym = XK_Control_L; break;
        case Qt::Key_Meta: xkeysym = XK_Meta_L; break;
        case Qt::Key_Alt: xkeysym = XK_Alt_L; break;
        case Qt::Key_CapsLock: xkeysym = XK_Caps_Lock; break;
        case Qt::Key_NumLock: xkeysym = XK_Num_Lock; break;
        case Qt::Key_ScrollLock: xkeysym = XK_Scroll_Lock; break;
        case Qt::Key_F1: xkeysym = XK_F1; break;
        case Qt::Key_F2: xkeysym = XK_F2; break;
        case Qt::Key_F3: xkeysym = XK_F3; break;
        case Qt::Key_F4: xkeysym = XK_F4; break;
        case Qt::Key_F5: xkeysym = XK_F5; break;
        case Qt::Key_F6: xkeysym = XK_F6; break;
        case Qt::Key_F7: xkeysym = XK_F7; break;
        case Qt::Key_F8: xkeysym = XK_F8; break;
        case Qt::Key_F9: xkeysym = XK_F9; break;
        case Qt::Key_F10: xkeysym = XK_F10; break;
        case Qt::Key_F11: xkeysym = XK_F11; break;
        case Qt::Key_F12: xkeysym = XK_F12; break;
        case Qt::Key_F13: xkeysym = XK_F13; break;
        case Qt::Key_F14: xkeysym = XK_F14; break;
        case Qt::Key_F15: xkeysym = XK_F15; break;
        case Qt::Key_F16: xkeysym = XK_F16; break;
        case Qt::Key_F17: xkeysym = XK_F17; break;
        case Qt::Key_F18: xkeysym = XK_F18; break;
        case Qt::Key_F19: xkeysym = XK_F19; break;
        case Qt::Key_F20: xkeysym = XK_F20; break;
        case Qt::Key_F21: xkeysym = XK_F21; break;
        case Qt::Key_F22: xkeysym = XK_F22; break;
        case Qt::Key_F23: xkeysym = XK_F23; break;
        case Qt::Key_F24: xkeysym = XK_F24; break;
        case Qt::Key_F25: xkeysym = XK_F25; break;
        case Qt::Key_F26: xkeysym = XK_F26; break;
        case Qt::Key_F27: xkeysym = XK_F27; break;
        case Qt::Key_F28: xkeysym = XK_F28; break;
        case Qt::Key_F29: xkeysym = XK_F29; break;
        case Qt::Key_F30: xkeysym = XK_F30; break;
        case Qt::Key_F31: xkeysym = XK_F31; break;
        case Qt::Key_F32: xkeysym = XK_F32; break;
        case Qt::Key_F33: xkeysym = XK_F33; break;
        case Qt::Key_F34: xkeysym = XK_F34; break;
        case Qt::Key_F35: xkeysym = XK_F35; break;
        case Qt::Key_Super_L: xkeysym = XK_Super_L; break;
        case Qt::Key_Super_R: xkeysym = XK_Super_R; break;
        case Qt::Key_Menu: xkeysym = XK_Menu; break;
        case Qt::Key_Hyper_L: xkeysym = XK_Hyper_L; break;
        case Qt::Key_Hyper_R: xkeysym = XK_Hyper_R; break;
        case Qt::Key_Help: xkeysym = XK_Help; break;
        case Qt::Key_Multi_key: xkeysym = XK_Multi_key; break;
        case Qt::Key_Codeinput: xkeysym = XK_Codeinput; break;
        case Qt::Key_SingleCandidate: xkeysym = XK_SingleCandidate; break;
        case Qt::Key_PreviousCandidate: xkeysym = XK_PreviousCandidate; break;
        case Qt::Key_Mode_switch: xkeysym = XK_Mode_switch; break;
        case Qt::Key_Kanji: xkeysym = XK_Kanji; break;
        case Qt::Key_Muhenkan: xkeysym = XK_Muhenkan; break;
        case Qt::Key_Henkan: xkeysym = XK_Henkan_Mode; break;
        case Qt::Key_Romaji: xkeysym = XK_Romaji; break;
        case Qt::Key_Hiragana: xkeysym = XK_Hiragana; break;
        case Qt::Key_Katakana: xkeysym = XK_Katakana; break;
        case Qt::Key_Hiragana_Katakana: xkeysym = XK_Hiragana_Katakana; break;
        case Qt::Key_Zenkaku: xkeysym = XK_Zenkaku; break;
        case Qt::Key_Hankaku: xkeysym = XK_Hankaku; break;
        case Qt::Key_Zenkaku_Hankaku: xkeysym = XK_Zenkaku_Hankaku; break;
        case Qt::Key_Touroku: xkeysym = XK_Touroku; break;
        case Qt::Key_Massyo: xkeysym = XK_Massyo; break;
        case Qt::Key_Kana_Lock: xkeysym = XK_Kana_Lock; break;
        case Qt::Key_Kana_Shift: xkeysym = XK_Kana_Shift; break;
        case Qt::Key_Eisu_Shift: xkeysym = XK_Eisu_Shift; break;
        case Qt::Key_Eisu_toggle: xkeysym = XK_Eisu_toggle; break;

        case Qt::Key_Hangul: xkeysym = XK_Hangul; break;
        case Qt::Key_Hangul_Start: xkeysym = XK_Hangul_Start; break;
        case Qt::Key_Hangul_End: xkeysym = XK_Hangul_End; break;
        case Qt::Key_Hangul_Jamo: xkeysym = XK_Hangul_Jamo; break;
        case Qt::Key_Hangul_Romaja: xkeysym = XK_Hangul_Romaja; break;
        case Qt::Key_Hangul_Jeonja: xkeysym = XK_Hangul_Jeonja; break;
        case Qt::Key_Hangul_Banja: xkeysym = XK_Hangul_Banja; break;
        case Qt::Key_Hangul_PreHanja: xkeysym = XK_Hangul_PreHanja; break;
        case Qt::Key_Hangul_PostHanja: xkeysym = XK_Hangul_PostHanja; break;
        case Qt::Key_Hangul_Special: xkeysym = XK_Hangul_Special; break;
        default: xkeysym = qkey; break;
    }

    return xkeysym;
}

uint InputListener::parseKeycode(QByteArray string)
{

    QKeyEvent eventti = QKeyEvent((QEvent::Type)6, string.toInt(), Qt::NoModifier);

    return handle_qkey(&eventti);
}

void InputListener::processPendingDatagrams()
{
    do {
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;
        uint keycode;

        udpSocket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);

        if(QString(datagram).contains("stop"))
        {
            ffmpeg->close();
        }
        else if(QString(datagram).contains("start"))
        {
            if(ffmpeg->state() == QProcess::NotRunning)
            {
                glcplay->setStandardOutputProcess(ffmpeg);

                glcplay->start("glc-play ../fifos/stream -o - -y 1");
                QString ffmpeg_run = QString("ffmpeg -i - -vcodec h263p -f rtp -s 1000x600 -cropright 200 rtp://").append(sender.toString()).append(":45456");
                cout << ffmpeg_run.data() << endl;
                ffmpeg->start(ffmpeg_run);
            }

            if(game->state() == QProcess::NotRunning  && QString(datagram).contains("start"))
                emit startGameProcess("glc-capture -f 30 -s -o ../fifos/stream ../darkplaces/darkplaces-linux-686-glx -basedir ../darkplaces/");
        }
        else
        {
            switch(datagram[0]){
                case InputListener::KEYPRESS:
                    keycode = parseKeycode(datagram.right(datagram.size()-1));
                    //cout << "tuli " << datagram.right(datagram.size()-1).toInt() << " - " << keycode << endl;
                    XTestFakeKeyEvent( QX11Info::display(), XKeysymToKeycode(QX11Info::display(), keycode), true, CurrentTime );
                    break;

                case InputListener::KEYRELEASE:
                    XTestFakeKeyEvent( QX11Info::display(), XKeysymToKeycode(QX11Info::display(), parseKeycode(datagram.right(datagram.size()-1))), false, CurrentTime );
                    break;

                case InputListener::MOUSEX:
                    XTestFakeRelativeMotionEvent( QX11Info::display(), datagram.right(datagram.size()-1).toInt(), 0, CurrentTime );
                    break;

                case InputListener::MOUSEY:
                    XTestFakeRelativeMotionEvent( QX11Info::display(), 0, datagram.right(datagram.size()-1).toInt(), CurrentTime );
                    break;

                case InputListener::MOUSE1PRESS:
                    XTestFakeButtonEvent( QX11Info::display(), 1, true, CurrentTime );
                    break;

                case InputListener::MOUSE1RELEASE:
                    XTestFakeButtonEvent( QX11Info::display(), 1, false, CurrentTime );
                    break;

                case InputListener::MOUSE2PRESS:
                    XTestFakeButtonEvent( QX11Info::display(), 2, true, CurrentTime );
                    break;

                case InputListener::MOUSE2RELEASE:
                    XTestFakeButtonEvent( QX11Info::display(), 2, false, CurrentTime );
                    break;

            }
        }
      
    } while (udpSocket->hasPendingDatagrams());
}
