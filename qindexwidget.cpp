#include "qindexwidget.h"
#include <QString>
#include <QVariant>
#include <QPainter>
#include <QDebug>
#include <thread>
#include <QThread>
#include <QDir>

QIndexWidget::QIndexWidget(QWidget *parent,
                           const char* addr, int port,
                           const char* username, const char* password, const char* topic)
    : QWidget(parent),
    _mqttserver(addr, port, username, password, this)
{
    strcpy(_topic, topic);
    _path = QString("img//") + QString(_topic) + QString(".jpg");
    QDir dir(QString("img//"));

    if (!dir.exists())
    {
        dir.mkpath(".");
    };
    connect(this, &QIndexWidget::setUpdate, this, &QIndexWidget::OnTimeOut);
}

void QIndexWidget::OnTimeOut()
{
    update();
}

QIndexWidget::~QIndexWidget()
{

}

void QIndexWidget::setIndex(int _idx)
{

}

int  QIndexWidget::getIndex()
{
    return 1;
}

bool QIndexWidget::open()
{
    _mqttserver.Init();
    _mqttserver.Connect(60);
    qDebug()<<QString(_topic);
    _mqttserver.Subsribe(nullptr, _topic, 1);
    std::thread f([&](){
        _mqttserver.Loop(-1,1);
    });
    f.detach();

    return  true;
}

void QIndexWidget::proc(void* data, int len)
{
    unsigned char* _data = (unsigned char*)data;


    int width = 0;
    int height = 0;
    int type = 0;
    memcpy(&width, _data, sizeof(int));
    memcpy(&height, _data + sizeof(int),sizeof(int));
    memcpy(&type, _data + sizeof(int) * 2, sizeof(int));
    QImage::Format imgtype = QImage::Format::Format_RGB888;
    if(type == CV_8UC3)
    {
        imgtype = QImage::Format::Format_RGB888;
    }
    img = QImage(_data + sizeof(int) * 3, width, height, imgtype);
    bRead = true;
    if(isRunning == false)
    {
        img.save(_path);
        emit setUpdate();
    }


  //  memcmp(p + sizeof(int) * 3, frame.data, frame.total() * frame.elemSize());
}
void QIndexWidget::setVideoCapture(const cv::VideoCapture& cap)
{
}

void QIndexWidget::paintEvent(QPaintEvent *event)
{
      isRunning = true;
      Q_UNUSED(event);

      QPainter painter(this);
      QRect rect = this->rect();

      painter.setPen(QColor(255,0,0));

      painter.drawRect(rect.adjusted(0, 0, -1, -1)); // 绘制边框，注意调整rect以避免线条过粗

      if(bRead)
      {
        QString path = QString("img//") + QString(_topic) + QString(".jpg");
        QImage _img(_path);
        painter.drawImage(rect, _img);
        time_t t = time(nullptr);
        struct tm _tm;
        localtime_s(&_tm, &t);
        char str[1024]{0};
        sprintf(str, "%d-%d-%d %d:%d:%d", _tm.tm_year + 1900, _tm.tm_mon + 1,
                _tm.tm_mday, _tm.tm_hour, _tm.tm_min, _tm.tm_sec);
        QFont ft("微软雅黑", 16);
        painter.setFont(ft);
        painter.drawText(50, 50, str);
      }
      isRunning = false;
}
