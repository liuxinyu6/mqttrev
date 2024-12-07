#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DynamicWidget w;
    w.setSubWidgetCount(9);
    w.start();
    w.showMaximized();
    return a.exec();
}
