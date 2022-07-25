#ifndef VIDEOCAP_H
#define VIDEOCAP_H

#include<QPixmap>
#include<qimage.h>
#include<QThread>
#include<opencv2/opencv.hpp>
#include "ctello.h"

using ctello::Tello;

#define ID_CAMARA 0

class VideoCap : public QThread
{
    Q_OBJECT;
public:
    VideoCap(QObject *parent = nullptr);
    QPixmap pixmap() const
    {
        return mPixmap;
    }
signals:
    void newPixmapCapture();
protected:
    void run() override;
private:
    QPixmap mPixmap;
    cv::Mat mFrame;
    cv::VideoCapture mVideoCap;

    QImage cvMatToImage(const  cv::Mat &inMat);
    QPixmap cvMatToQpixmap(const cv::Mat &inMat);
    Tello tello{};

};

#endif // VIDEOCAPTURE_H
