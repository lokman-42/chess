#include <QCoreApplication>
#include <QDebug>
#include "publicfunctions.h"
#include "chessfunction.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QByteArray array;
    publicfunctions::fileReadOperation("../board.txt",array);
    qInfo() << array.toStdString().c_str();

    chessfunction chessOpt(array);
    chessOpt.gameRoutine();

    return a.exec();
}
