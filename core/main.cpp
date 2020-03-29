#include <QApplication>
#include "engine.h"
#include "net.h"
#include "view.h"
#include "menu.h"
#include "training.h"
#include "solo.h"
#include "exam.h"
#include "examfirst.h"
#include "room.h"

int main(int argc, char *argv[])
{
    qRegisterMetaType<QList<Card *>>("QList<Card *>");
    qRegisterMetaType<CardMoveStruct>("CardMoveStruct");

    QApplication a(argc, argv);
    qDebug() << QSslSocket::sslLibraryBuildVersionString();

    qEngine->initialize();

    qMenu->initialize();
    qNet->initialize();
    qTraining->initialize();
    qSolo->initialize();
    qExam->initialize();
    qExamFirst->initialize();
    qRoom->initialize();

    qView->initialize();
    qView->setScene(qMenu);
    qView->show();

    return a.exec();
}
