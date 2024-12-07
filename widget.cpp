#include "widget.h"
#include "ui_widget.h"
#include <QLabel>
#include <QPushButton>
#include <QDebug>

DynamicWidget::DynamicWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DynamicWidget),_count(1)
{
    ui->setupUi(this);
    _layout = new QVBoxLayout(this);
    setLayout(_layout);

}

void DynamicWidget::setSubWidgetCount(int count)
{
    if(count<=1)
    {
        _count = 1;
    }
    else if(count <=4)
    {
        _count = 4;
    }
    else
    {
        _count = 9;
    }
    // 删除当前布局中的所有子窗口
    while (_layout->count() > 0)
    {
        QLayoutItem *item = _layout->takeAt(0);
        delete item->widget();
        delete item;
        _vlist.clear();
    }

    // 根据新的输入个数添加子窗口
    switch (_count)
    {
    case 1:
    default:
        for (int i = 0; i < _count; ++i)
        {
            char str[1024]{0};
            sprintf(str, "TOPIC_%d", i);
            QHBoxLayout* layout = new QHBoxLayout;
            QIndexWidget *subWidget = new QIndexWidget(this, "127.0.0.1",
                                                       1883, "abc", "123", str);


            layout->addWidget(subWidget);

            _vlist.append(subWidget);

            _layout->addLayout(layout);
        }
        break;
    case 4:
        {
            for (int i = 0; i < 2; ++i)
            {
                char str[1024]{0};
                sprintf(str, "TOPIC_%d", i * 2);
                QHBoxLayout* layout = new QHBoxLayout;
                QIndexWidget *subWidget = new QIndexWidget(this, "127.0.0.1",
                                                           1883 + i * 2, "abc", "123", str);

                char str2[1024]{0};
                sprintf(str2, "TOPIC_%d", i * 2 + 1);
                QIndexWidget *subWidget2 = new QIndexWidget(this, "127.0.0.1",
                                                            1883 + i * 2 + 1, "abc", "123", str2);

                layout->addWidget(subWidget);
                layout->addWidget(subWidget2);

                _vlist.append(subWidget);
                _vlist.append(subWidget2);

                _layout->addLayout(layout);
            }
        }
        break;
    case 9:
        {
            for (int i = 0; i < 3; ++i)
            {
                QHBoxLayout* layout = new QHBoxLayout;
                char str[1024]{0};
                sprintf(str, "TOPIC_%d", i * 3);
                QIndexWidget *subWidget = new QIndexWidget(this, "127.0.0.1",
                                                           1883 + i * 3, "abc", "123", str);

                char str2[1024]{0};
                sprintf(str2, "TOPIC_%d", i * 3 + 1);
                QIndexWidget *subWidget2 = new QIndexWidget(this, "127.0.0.1",
                                                            1883 + i * 3 + 1, "abc", "123", str2);

                char str3[1024]{0};
                sprintf(str3, "TOPIC_%d", i * 3 + 2);
                QIndexWidget *subWidget3 = new QIndexWidget(this, "127.0.0.1",
                                                            1883 + i * 3 + 2, "abc", "123", str3);

                layout->addWidget(subWidget);
                layout->addWidget(subWidget2);
                layout->addWidget(subWidget3);


                _vlist.append(subWidget);
                _vlist.append(subWidget2);
                _vlist.append(subWidget3);

                _layout->addLayout(layout);
            }
        }
        break;

    }
}

void DynamicWidget::start()
{
    qDebug()<<_vlist.size();
    for(auto it = _vlist.begin(); it != _vlist.end(); ++it)
    {
        (*it)->open();
    }
}

DynamicWidget::~DynamicWidget()
{
    // 删除当前布局中的所有子窗口
    while (_layout->count() > 0)
    {
        QLayoutItem *item = _layout->takeAt(0);
        delete item->widget();
        delete item;
        _vlist.clear();
    }
    delete ui;
}

