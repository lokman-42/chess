/*
 * Author : Lokman Pehlivan
*/

#include <QCoreApplication>
#include <QDebug>
#include "publicfunctions.h"
#include "chessfunction.h"

int main(int argc, char *argv[])
{
    /*
     * Dosyadan okunan satranc board bilgisi, iki boyutlu listeye yuklenir.
     * Daha sonra bu liste bastan itibaren( 0,0  0,1  0,2 ... 8,7  8,8 seklinde)
     * taranarak liste üzerinde tespit edilen her tas icin tehlike kontrolu yapilir.
     * Kontroller neticesinde tasin rengine gore puani belirlenir.
    */
    QCoreApplication a(argc, argv);

    QByteArray array;
    publicfunctions::fileReadOperation("../board.txt",array);
    qInfo() << array.toStdString().c_str() << "\n";

    chessfunction chessOpt(array);
    chessOpt.gameRoutine();

    return a.exec();
}
