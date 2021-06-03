#include "chessfunction.h"

chessfunction::chessfunction()
{

}

chessfunction::chessfunction(QByteArray byteArray)
{
    QList<QByteArray> list = byteArray.split('\n');
    for (int var = 0; var < list.size(); ++var) {
        QList <QByteArray>value = list[var].split(' ');
        chessTable.append(value);
    }

    this->blackTotalPoint = 0;
    this->whiteTotalPoint = 0;
}

void chessfunction::gameRoutine()
{
    /*
     Game routine, board üzerindeki taşların teklike durumlarına göre puanlarının hesaplandığı fonksiyondur.
     Board baştan sona taranarak indexlerde bulunan taşların renk ve tipine göre puan hesapları yapılmaktadır.
     Board tamamen tarandıktan sonra, siyah ve beyaz taşlar için toplam puana göre kazanan belirlenmektedir.
    */

    for (qint16 indexX = 0; indexX < 8; ++indexX) {
        for (qint16 indexY = 0; indexY < 8; ++indexY) {
            QString piece = chessTable[indexX][indexY];

            if (piece.at(1) == 's') {
                // Tasin siyah oldugunu anliyoruz. Siyah icin tehlike kontorlu.
                QString value = piece.at(0);// Tasin tipini aliyoruz(Ornek: ps | p -> 0.index piyan)
                double piecePoint = getPiecePoint(value);


                if (!whitePawnDanger(indexX, indexY)) {
                    if (!whiteQueenDanger(indexX, indexY)) {
                        if (!whiteBishopDanger(indexX, indexY)) {
                            if (!whiteCastleDanger(indexX, indexY)) {
                                if (!whiteKnightDanger(indexX, indexY)) {
                                    if (!whiteKingDanger(indexX, indexY)) {
                                        blackTotalPoint += piecePoint;
                                    } else {
                                        if (whiteKingMoveControl(indexX, indexY)) {
                                            blackTotalPoint += piecePoint;
                                        } else {
                                            blackTotalPoint += piecePoint/2;
                                        }
                                    }
                                } else {
                                    blackTotalPoint += piecePoint/2;
                                }
                            } else {
                                blackTotalPoint += piecePoint/2;
                            }
                        } else {
                            blackTotalPoint += piecePoint/2;
                        }
                    } else {
                        blackTotalPoint += piecePoint/2;
                    }
                } else {
                    blackTotalPoint += piecePoint/2;
                }

            } else if (piece.at(1) == 'b') { // Tasin beyaz oldugunu anliyoruz.
                QString value = piece.at(0);// Tasin tipini aliyoruz(Ornek: ps | p -> 0.index piyan)
                double piecePoint = getPiecePoint(value);



                if (!blackPawnDanger(indexX, indexY)) {
                    if (!blackQueenDanger(indexX, indexY)) {
                        if (!blackBishopDanger(indexX, indexY)) {
                            if (!blackCastleDanger(indexX, indexY)) {
                                if (!blackKnightDanger(indexX, indexY)) {
                                    if (!blackKingDanger(indexX, indexY)) {
                                        whiteTotalPoint += piecePoint;
                                    } else {

                                        if (blackKingMoveControl(indexX, indexY)) {
                                            whiteTotalPoint += piecePoint;
                                        } else {
                                            whiteTotalPoint += piecePoint/2;
                                        }
                                    }
                                } else {
                                    whiteTotalPoint += piecePoint/2;
                                }
                            } else {
                                whiteTotalPoint += piecePoint/2;
                            }
                        } else {
                            whiteTotalPoint += piecePoint/2;
                        }
                    } else {
                        whiteTotalPoint += piecePoint/2;
                    }
                } else {
                    whiteTotalPoint += piecePoint/2;
                }

            }
        }
    }


    qInfo() << "=============SONUC=============";
    qInfo() << "SIYAH TOPLAM PUAN : " << blackTotalPoint;
    qInfo() << "BEYAZ TOPLAM PUAN : " << whiteTotalPoint;
    qInfo() << "===============================";

    QString vs = "ESITLIK";
    if (blackTotalPoint > whiteTotalPoint) {
        vs = "KAZANAN SIYAH";
    }
    else if(blackTotalPoint < whiteTotalPoint) {
        vs = "KAZANAN BEYAZ";
    }
    qInfo() << vs;
}

double chessfunction::getPiecePoint(QString pieceType)
{
    /*
     * Tas tipine gore puan bilgisini veren fonksiyon
    */
    double resultPoint = 0;
    if (pieceType == "p") {
        resultPoint = 1;
    }
    else if (pieceType == "a") {
        resultPoint = 3;
    }
    else if (pieceType == "f") {
        resultPoint = 3;
    }
    else if (pieceType == "k") {
        resultPoint = 5;
    }
    else if (pieceType == "v") {
        resultPoint = 9;
    }
    else if (pieceType == "s") {
        resultPoint = 100;
    }
    else {
        resultPoint = 0;
    }

    return resultPoint;
}

bool chessfunction::blackKingMoveControl(qint16 positionX, qint16 positionY)
{
    /*
     * Siyah Sah'in diger renkteki taslara tehlike olusturmasi durumunda mat olma durumunu tespit eden fonksiyon
    */
    bool result = false;
    if (!whitePawnDanger(positionX, positionY)) {
        if (!whiteQueenDanger(positionX, positionY)) {
            if (!whiteBishopDanger(positionX, positionY)) {
                if (!whiteCastleDanger(positionX, positionY)) {
                    if (!whiteKnightDanger(positionX, positionY)) {
                        if (!whiteKingDanger(positionX, positionY)) {
                            return false;
                        } else {
                            result = true;
                        }
                    } else {
                        result = true;
                    }
                } else {
                    result = true;
                }
            } else {
                result = true;
            }
        } else {
            result = true;
        }
    } else {
        result = true;
    }
    return result;
}

bool chessfunction::whiteKingMoveControl(qint16 positionX, qint16 positionY)
{
    /*
     * Beyaz Sah'in diger renkteki taslara tehlike olusturmasi durumunda mat olma durumunu tespit eden fonksiyon
    */
    bool result = false;
    if (!blackPawnDanger(positionX, positionY)) {
        if (!blackQueenDanger(positionX, positionY)) {
            if (!blackBishopDanger(positionX, positionY)) {
                if (!blackCastleDanger(positionX, positionY)) {
                    if (!blackKnightDanger(positionX, positionY)) {
                        if (!blackKingDanger(positionX, positionY)) {
                            return false;
                        } else {
                            result = true;
                        }
                    } else {
                        result = true;
                    }
                } else {
                    result = true;
                }
            } else {
                result = true;
            }
        } else {
            result = true;
        }
    } else {
        result = true;
    }

    return result;
}

bool chessfunction::blackKnightDanger(qint16 positionX, qint16 positionY)
{
    /*
     * Siyah atin tehlike kontrolunu yapan fonksiyon
    */
    if ((positionX+2)<8 && (positionY+1)<8) {
        QString value = chessTable[positionX+2][positionY+1];
        if (value == "as") {
            return true;
        }
    }

    if ((positionX+2)<8 && (positionY-1)>=0) {
        QString value = chessTable[positionX+2][positionY-1];
        if (value == "as") {
            return true;
        }
    }

    if ((positionX-2)>=0 && (positionY+1)<8) {
        QString value = chessTable[positionX-2][positionY+1];
        if (value == "as") {
            return true;
        }
    }

    if ((positionX-2)>=0 && (positionY-1)>=0) {
        QString value = chessTable[positionX-2][positionY-1];
        if (value == "as") {
            return true;
        }
    }
    /**/
    if ((positionX+1)<8 && (positionY+2)<8) {
        QString value = chessTable[positionX+1][positionY+2];
        if (value == "as") {
            return true;
        }
    }

    if ((positionX-1)>=0 && (positionY+2)<8) {
        QString value = chessTable[positionX-1][positionY+2];
        if (value == "as") {
            return true;
        }
    }

    if ((positionX+1)<8 && (positionY-2)>=0) {
        QString value = chessTable[positionX+1][positionY-2];
        if (value == "as") {
            return true;
        }
    }

    if ((positionX-1)>=0 && (positionY-2)>=0) {
        QString value = chessTable[positionX-1][positionY-2];
        if (value == "as") {
            return true;
        }
    }

    return false;
}

bool chessfunction::blackKingDanger(qint16 positionX, qint16 positionY)
{
    /*
     * Siyah Sah tehlike kontrolunu yapan fonksiyon
    */
    if ((positionX+1)<8 && (positionY+1)<8) {
        QString value = chessTable[positionX+1][positionY+1];
        if (value == "ss") {
            return true;
        }
    }

    if ((positionX+1)<8 && (positionY-1)>0) {
        QString value = chessTable[positionX+1][positionY-1];
        if (value == "ss") {
            return true;
        }
    }

    if ((positionX-1)>=0 && (positionY+1)<8) {
        QString value = chessTable[positionX-1][positionY+1];
        if (value == "ss") {
            return true;
        }
    }

    if ((positionX-1)>=0 && (positionY-1)>=0) {
        QString value = chessTable[positionX-1][positionY-1];
        if (value == "ss") {
            return true;
        }
    }

    if ((positionX)>=0 && (positionY-1)>=0) {
        QString value = chessTable[positionX][positionY-1];
        if (value == "ss") {
            return true;
        }
    }

    if ((positionX)>=0 && (positionY+1)<8) {
        QString value = chessTable[positionX][positionY+1];
        if (value == "ss") {
            return true;
        }
    }

    if ((positionX+1)<8 && (positionY)>=0) {
        QString value = chessTable[positionX+1][positionY];
        if (value == "ss") {
            return true;
        }
    }

    if ((positionX-1)>=0 && (positionY)>=0) {
        QString value = chessTable[positionX-1][positionY];
        if (value == "ss") {
            return true;
        }
    }

    return false;
}

bool chessfunction::blackQueenDanger(qint16 positionX, qint16 positionY)
{
    /*
     * Siyah vezir tehlike kontrolunu yapan fonksiyon
    */

    for (int xIndex = positionX+1, yIndex = positionY+1; xIndex < 8 && yIndex < 8; xIndex++,yIndex++) {
        QString value = chessTable[xIndex][yIndex];
        if (value != "xx") {
            if (value == "vs") {
                return  true;
            } else {
                break;
            }
        }
    }

    for (int xIndex = positionX+1, yIndex = positionY-1; xIndex < 8 && yIndex >= 0; xIndex++,yIndex--) {
        QString value = chessTable[xIndex][yIndex];
        if (value != "xx") {
            if (value == "vs") {
                return  true;
            } else {
                break;
            }
        }
    }

    for (int xIndex = positionX-1, yIndex = positionY+1; xIndex >= 0 && yIndex < 8; xIndex--,yIndex++) {
        QString value = chessTable[xIndex][yIndex];
        if (value != "xx") {
            if (value == "vs") {
                return  true;
            } else {
                break;
            }
        }
    }

    for (int xIndex = positionX-1, yIndex = positionY-1; xIndex >= 0 && yIndex >= 0; xIndex--,yIndex--) {
        QString value = chessTable[xIndex][yIndex];
        if (value != "xx") {
            if (value == "vs") {
                return  true;
            } else {
                break;
            }
        }
    }

    for (int index = positionY+1; index < 8; ++index) {
        QString value = chessTable[positionX][index];
        if (value != "xx") {
            if (value == "vs") {
                return true;
            } else {
                break;
            }
        }
    }

    for (int index = positionY-1; index >= 0; --index) {
        QString value = chessTable[positionX][index];
        if (value != "xx") {
            if (value == "vs") {
                return true;
            } else {
                break;
            }
        }
    }

    for (int index = positionX-1; index >= 0; --index) {
        QString value = chessTable[index][positionY];
        if (value != "xx") {
            if (value == "vs") {
                return true;
            } else {
                break;
            }
        }
    }

    for (int index = positionX+1; index < 8; ++index) {
        QString value = chessTable[index][positionY];
        if (value != "xx") {
            if (value == "vs") {
                return true;
            } else {
                break;
            }
        }
    }

    return false;
}

bool chessfunction::blackBishopDanger(qint16 positionX, qint16 positionY)
{
    /*
     * Siyah fil tehlike kontrolunu yapan fonksiyon
    */
    for (int xIndex = positionX+1, yIndex = positionY+1; xIndex < 8 && yIndex < 8; xIndex++,yIndex++) {
        QString value = chessTable[xIndex][yIndex];
        if (value != "xx") {
            if (value == "fs") {
                return  true;
            } else {
                break;
            }
        }
    }

    for (int xIndex = positionX+1, yIndex = positionY-1; xIndex < 8 && yIndex >= 0; xIndex++,yIndex--) {
        QString value = chessTable[xIndex][yIndex];
        if (value != "xx") {
            if (value == "fs") {
                return  true;
            } else {
                break;
            }
        }
    }

    for (int xIndex = positionX-1, yIndex = positionY+1; xIndex >= 0 && yIndex < 8; xIndex--,yIndex++) {
        QString value = chessTable[xIndex][yIndex];
        if (value != "xx") {
            if (value == "fs") {
                return  true;
            } else {
                break;
            }
        }
    }

    for (int xIndex = positionX-1, yIndex = positionY-1; xIndex >= 0 && yIndex >= 0; xIndex--,yIndex--) {
        QString value = chessTable[xIndex][yIndex];
        if (value != "xx") {
            if (value == "fs") {
                return  true;
            } else {
                break;
            }
        }
    }

    return  false;
}

bool chessfunction::blackCastleDanger(qint16 positionX, qint16 positionY)
{
    /*
     * Siyah kale tehlike kontrolunu yapan fonksiyon
    */
    for (int index = positionY+1; index < 8; ++index) {
        QString value = chessTable[positionX][index];
        if (value != "xx") {
            if (value == "ks") {
                return true;
            } else {
                break;
            }
        }
    }

    for (int index = positionY-1; index >= 0; --index) {
        QString value = chessTable[positionX][index];
        if (value != "xx") {
            if (value == "ks") {
                return true;
            } else {
                break;
            }
        }
    }

    for (int index = positionX-1; index >= 0; --index) {
        QString value = chessTable[index][positionY];
        if (value != "xx") {
            if (value == "ks") {
                return true;
            } else {
                break;
            }
        }
    }

    for (int index = positionX+1; index < 8; ++index) {
        QString value = chessTable[index][positionY];
        if (value != "xx") {
            if (value == "ks") {
                return true;
            } else {
                break;
            }
        }
    }

    return false;
}

bool chessfunction::blackPawnDanger(qint16 positionX, qint16 positionY)
{
    /*
     * Siyah piyon tehlike kontrolunu yapan fonksiyon
    */
    if ((positionX-1)>=0 && (positionY-1)>=0) {
        QString value = chessTable[positionX-1][positionY-1];
        if (value == "ps") {
            return true;
        }
    }

    if ((positionX-1)>=0 && (positionY+1)<8) {
        QString value = chessTable[positionX-1][positionY+1];
        if (value == "ps") {
            return true;
        }
    }

    return false;
}

/*==============================================================================================================================================*/
/* WHITE */
/*==============================================================================================================================================*/

bool chessfunction::whiteKnightDanger(qint16 positionX, qint16 positionY)
{
    /*
     * Beyaz atin tehlike kontrolunu yapan fonksiyon
    */
    if ((positionX+2)<8 && (positionY+1)<8) {
        QString value = chessTable[positionX+2][positionY+1];
        if (value == "ab") {
            return true;
        }
    }

    if ((positionX+2)<8 && (positionY-1)>=0) {
        QString value = chessTable[positionX+2][positionY-1];
        if (value == "ab") {
            return true;
        }
    }

    if ((positionX-2)>=0 && (positionY+1)<8) {
        QString value = chessTable[positionX-2][positionY+1];
        if (value == "ab") {
            return true;
        }
    }

    if ((positionX-2)>=0 && (positionY-1)>=0) {
        QString value = chessTable[positionX-2][positionY-1];
        if (value == "ab") {
            return true;
        }
    }
    /**/
    if ((positionX+1)<8 && (positionY+2)<8) {
        QString value = chessTable[positionX+1][positionY+2];
        if (value == "ab") {
            return true;
        }
    }

    if ((positionX-1)>=0 && (positionY+2)<8) {
        QString value = chessTable[positionX-1][positionY+2];
        if (value == "ab") {
            return true;
        }
    }

    if ((positionX+1)<8 && (positionY-2)>=0) {
        QString value = chessTable[positionX+1][positionY-2];
        if (value == "ab") {
            return true;
        }
    }

    if ((positionX-1)>=0 && (positionY-2)>=0) {
        QString value = chessTable[positionX-1][positionY-2];
        if (value == "ab") {
            return true;
        }
    }

    return false;
}

bool chessfunction::whiteKingDanger(qint16 positionX, qint16 positionY)
{
    /*
     * Beyaz Sah tehlike kontrolunu yapan fonksiyon
    */
    if ((positionX+1)<8 && (positionY+1)<8) {
        QString value = chessTable[positionX+1][positionY+1];
        if (value == "sb") {
            return true;
        }
    }

    if ((positionX+1)<8 && (positionY-1)>0) {
        QString value = chessTable[positionX+1][positionY-1];
        if (value == "sb") {
            return true;
        }
    }

    if ((positionX-1)>=0 && (positionY+1)<8) {
        QString value = chessTable[positionX-1][positionY+1];
        if (value == "sb") {
            return true;
        }
    }

    if ((positionX-1)>=0 && (positionY-1)>=0) {
        QString value = chessTable[positionX-1][positionY-1];
        if (value == "sb") {
            return true;
        }
    }

    if ((positionX)>=0 && (positionY-1)>=0) {
        QString value = chessTable[positionX][positionY-1];
        if (value == "sb") {
            return true;
        }
    }

    if ((positionX)>=0 && (positionY+1)<8) {
        QString value = chessTable[positionX][positionY+1];
        if (value == "sb") {
            return true;
        }
    }

    if ((positionX+1)<8 && (positionY)>=0) {
        QString value = chessTable[positionX+1][positionY];
        if (value == "sb") {
            return true;
        }
    }

    if ((positionX-1)>=0 && (positionY)>=0) {
        QString value = chessTable[positionX-1][positionY];
        if (value == "sb") {
            return true;
        }
    }

    return false;
}

bool chessfunction::whiteQueenDanger(qint16 positionX, qint16 positionY)
{
    /*
     * Beyaz vezir tehlike kontrolunu yapan fonksiyon
    */

    for (int xIndex = positionX+1, yIndex = positionY+1; xIndex < 8 && yIndex < 8; xIndex++,yIndex++) {
        QString value = chessTable[xIndex][yIndex];
        if (value != "xx") {
            if (value == "vb") {
                return  true;
            } else {
                break;
            }
        }
    }

    for (int xIndex = positionX+1, yIndex = positionY-1; xIndex < 8 && yIndex >= 0; xIndex++,yIndex--) {
        QString value = chessTable[xIndex][yIndex];
        if (value != "xx") {
            if (value == "vb") {
                return  true;
            } else {
                break;
            }
        }
    }

    for (int xIndex = positionX-1, yIndex = positionY+1; xIndex >= 0 && yIndex < 8; xIndex--,yIndex++) {
        QString value = chessTable[xIndex][yIndex];
        if (value != "xx") {
            if (value == "vb") {
                return  true;
            } else {
                break;
            }
        }
    }

    for (int xIndex = positionX-1, yIndex = positionY-1; xIndex >= 0 && yIndex >= 0; xIndex--,yIndex--) {
        QString value = chessTable[xIndex][yIndex];
        if (value != "xx") {
            if (value == "vb") {
                return  true;
            } else {
                break;
            }
        }
    }

    for (int index = positionY+1; index < 8; ++index) {
        QString value = chessTable[positionX][index];
        if (value != "xx") {
            if (value == "vb") {
                return true;
            } else {
                break;
            }
        }
    }

    for (int index = positionY-1; index >= 0; --index) {
        QString value = chessTable[positionX][index];
        if (value != "xx") {
            if (value == "vb") {
                return true;
            } else {
                break;
            }
        }
    }

    for (int index = positionX-1; index >= 0; --index) {
        QString value = chessTable[index][positionY];
        if (value != "xx") {
            if (value == "vb") {
                return true;
            } else {
                break;
            }
        }
    }

    for (int index = positionX+1; index < 8; ++index) {
        QString value = chessTable[index][positionY];
        if (value != "xx") {
            if (value == "vb") {
                return true;
            } else {
                break;
            }
        }
    }

    return false;
}

bool chessfunction::whiteBishopDanger(qint16 positionX, qint16 positionY)
{
    /*
     * Beyaz fil tehlike kontrolunu yapan fonksiyon
    */
    for (int xIndex = positionX+1, yIndex = positionY+1; xIndex < 8 && yIndex < 8; xIndex++,yIndex++) {
        QString value = chessTable[xIndex][yIndex];
        if (value != "xx") {
            if (value == "fb") {
                return  true;
            } else {
                break;
            }
        }
    }

    for (int xIndex = positionX+1, yIndex = positionY-1; xIndex < 8 && yIndex >= 0; xIndex++,yIndex--) {
        QString value = chessTable[xIndex][yIndex];
        if (value != "xx") {
            if (value == "fb") {
                return  true;
            } else {
                break;
            }
        }
    }

    for (int xIndex = positionX-1, yIndex = positionY+1; xIndex >= 0 && yIndex < 8; xIndex--,yIndex++) {
        QString value = chessTable[xIndex][yIndex];
        if (value != "xx") {
            if (value == "fb") {
                return  true;
            } else {
                break;
            }
        }
    }

    for (int xIndex = positionX-1, yIndex = positionY-1; xIndex >= 0 && yIndex >= 0; xIndex--,yIndex--) {
        QString value = chessTable[xIndex][yIndex];
        if (value != "xx") {
            if (value == "fb") {
                return  true;
            } else {
                break;
            }
        }
    }

    return  false;
}

bool chessfunction::whiteCastleDanger(qint16 positionX, qint16 positionY)
{
    /*
     * Beyaz kale tehlike kontrolunu yapan fonksiyon
    */
    for (int index = positionY+1; index < 8; ++index) {
        QString value = chessTable[positionX][index];
        if (value != "xx") {
            if (value == "kb") {
                return true;
            } else {
                break;
            }
        }
    }

    for (int index = positionY-1; index >= 0; --index) {
        QString value = chessTable[positionX][index];
        if (value != "xx") {
            if (value == "kb") {
                return true;
            } else {
                break;
            }
        }
    }

    for (int index = positionX-1; index >= 0; --index) {
        QString value = chessTable[index][positionY];
        if (value != "xx") {
            if (value == "kb") {
                return true;
            } else {
                break;
            }
        }
    }

    for (int index = positionX+1; index < 8; ++index) {
        QString value = chessTable[index][positionY];
        if (value != "xx") {
            if (value == "kb") {
                return true;
            } else {
                break;
            }
        }
    }

    return false;
}

bool chessfunction::whitePawnDanger(qint16 positionX, qint16 positionY)
{
    /*
     * Beyaz piyon tehlike kontrolunu yapan fonksiyon
    */
    if ((positionX+1)<8 && (positionY-1)>=0) {
        QString value = chessTable[positionX+1][positionY-1];
        if (value == "pb") {
            return true;
        }
    }

    if ((positionX+1)<8 && (positionY+1)<8) {
        QString value = chessTable[positionX+1][positionY+1];
        if (value == "pb") {
            return true;
        }
    }

    return false;
}


chessfunction::~chessfunction()
{

}
