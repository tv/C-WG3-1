#include <QApplication>
#include <QPushButton>
#include <iostream>

using namespace std;
#include "InputListener.h"
#include "VideoStreamer.h"

int main(int argc, char *argv[])
{
    cout << "socketti valmis, ehkä" << endl;
    QApplication app(argc, argv);
    
    InputListener *inputListener = new InputListener();
    VideoStreamer *videoStreamer = new VideoStreamer();
    
    inputListener->run();
    videoStreamer->run();
    
    inputListener->connect(inputListener, SIGNAL(startVideoStream(quint32)), videoStreamer, SLOT(StartVideoOutput(quint32)));
    
//     long int i = 0;
//     
//     while(true){
//         if(i==1000000) {
//             qDebug( "Ping!" );
//             i = 0;
//         } else {
//             i++;
//         }
//         
//     }
    
    return app.exec();
}