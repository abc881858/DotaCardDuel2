#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QTranslator>
#include "engine.h"
#include "introduction.h"
#include <QIcon>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator translator;
    if (translator.load("dc_zh_cn"))
    {
        QApplication::installTranslator(&translator);
    }
    Engine::instance()->loadAllClass();
    Introduction introduction;
    introduction.setWindowIcon(QIcon("title/qtcreator.png"));
    introduction.setWindowTitle("Dota Card");
//    introduction.move(900,100);
    introduction.show();

    return QApplication::exec();
}
