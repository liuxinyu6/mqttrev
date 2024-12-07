#ifndef WIDGET_H
#define WIDGET_H


#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QList>
#include <qindexwidget.h>

QT_BEGIN_NAMESPACE
namespace Ui { class DynamicWidget; }
QT_END_NAMESPACE

class DynamicWidget : public QWidget
{
    Q_OBJECT

public:
    DynamicWidget(QWidget *parent = nullptr);
    ~DynamicWidget();

    void setSubWidgetCount(int count);

    void start();

private:
    QVBoxLayout* _layout;
    int _count;
    QList<QIndexWidget*> _vlist;

private:
    Ui::DynamicWidget *ui;
};
#endif // WIDGET_H
