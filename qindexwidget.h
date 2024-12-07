#ifndef QINDEXWIDGET_H
#define QINDEXWIDGET_H

#include <QWidget>
#include <QImage>
#include <QTimer>
#include <opencv2/opencv.hpp>
#include <mutex>
#include <memory>
#include "mqttserver.h"

class QIndexWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QIndexWidget(QWidget *parent = nullptr,
                          const char* addr = "127.0.0.1", int port = 1883,
                          const char* username = nullptr, const char* password = nullptr, const char* topic = "");
    virtual ~QIndexWidget();

public:
    void setIndex(int _idx);
    int  getIndex();


    void setVideoCapture(const cv::VideoCapture& cap);

    bool open();

    void proc(void* data, int len);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    char _topic[1024];

    MqttServer<QIndexWidget> _mqttserver;

    QImage img;
    bool bRead{false};
    bool isRunning{false};
    QString _path;

signals:
    void setUpdate();

public slots:
    void OnTimeOut();
};

#endif // QINDEXWIDGET_H
