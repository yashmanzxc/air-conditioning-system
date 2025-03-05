#include "widget.h"
#include<QTranslator>
#include <QApplication>
#include<QString>
#include<QLibraryInfo>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Widget w;
    w.show();
    return a.exec();
}
