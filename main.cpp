#include <QApplication>
#include "mainwidget.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

#ifdef Q_OS_MAC
	QFont appFont("Helvetica Neue");
#else
	QFont appFont("Microsoft YaHei");
#endif
	app.setFont(appFont);

    MainWidget w;
    w.show();

    return app.exec();
}
