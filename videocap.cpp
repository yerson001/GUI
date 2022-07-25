#include "videocap.h"
#include <QDebug>

const char* const TELLO_STREAM_URL{"udp://0.0.0.0:11111"};
using namespace std;

using ctello::Tello;
using cv::CAP_FFMPEG;
using cv::imshow;
//using cv::VideoCapture;
using cv::waitKey;

VideoCap::VideoCap(QObject *parent)
    :QThread{parent},mVideoCap{TELLO_STREAM_URL, CAP_FFMPEG}
{
    Tello tello{};
    if(!tello.Bind())
    {
      qDebug()<<" error to conect";
      //return 0;
    }

}

void VideoCap::run()
{
    if(mVideoCap.isOpened())
    {
        tello.SendCommand("streamon");
        while(!(tello.ReceiveResponse()));
        //cv::VideoCapture cap{TELLO_STREAM_URL, CAP_FFMPEG};
        bool busy{false};

        while(true)
        {
            mVideoCap >> mFrame;
            if(const auto response = tello.ReceiveResponse())
            {
              std::cout <<"tello: "<< *response << std::endl;
              busy = false;
            }

            if(!mFrame.empty())
            {
                mPixmap = cvMatToQpixmap(mFrame);
                emit newPixmapCapture();
            }
        }
    }
}

QImage VideoCap::cvMatToImage( const cv::Mat &inMat )
{
  switch ( inMat.type() )
  {
     // 8-bit, 4 channel
     case CV_8UC4:
     {
        QImage image( inMat.data,
                      inMat.cols, inMat.rows,
                      static_cast<int>(inMat.step),
                      QImage::Format_ARGB32 );

        return image;
     }
     // 8-bit, 3 channel
     case CV_8UC3:
     {
        QImage image( inMat.data,
                      inMat.cols, inMat.rows,
                      static_cast<int>(inMat.step),
                      QImage::Format_RGB888 );

        return image.rgbSwapped();
     }
     // 8-bit, 1 channel
     case CV_8UC1:
     {
#if QT_VERSION >= QT_VERSION_CHECK(5, 5, 0)
        QImage image( inMat.data,
                      inMat.cols, inMat.rows,
                      static_cast<int>(inMat.step),
                      QImage::Format_Grayscale8 );
#else

#endif

        return image;
     }

     default:
        qWarning() << "ASM::cvMatToQImage() - cv::Mat image type not handled in switch:" << inMat.type();
        break;
  }

  return QImage();
}
QPixmap VideoCap::cvMatToQpixmap( const cv::Mat &inMat )
{
  return QPixmap::fromImage( cvMatToImage( inMat ) );
}
