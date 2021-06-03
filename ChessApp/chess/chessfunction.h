#ifndef CHESSFUNCTION_H
#define CHESSFUNCTION_H
#include <QDebug>
#include <QList>

class chessfunction
{
public:
    chessfunction();
    ~chessfunction();
    chessfunction(QByteArray byteArray);

    QList<QList<QByteArray>> chessTable;
    double blackTotalPoint;
    double whiteTotalPoint;

    void gameRoutine();

    double getPiecePoint(QString pieceType);
    bool blackKingMoveControl(qint16 positionX, qint16 positionY);
    bool whiteKingMoveControl(qint16 positionX, qint16 positionY);

    bool blackKnightDanger(qint16 positionX, qint16 positionY);
    bool blackKingDanger(qint16 positionX, qint16 positionY);
    bool blackQueenDanger(qint16 positionX, qint16 positionY);
    bool blackBishopDanger(qint16 positionX, qint16 positionY);
    bool blackCastleDanger(qint16 positionX, qint16 positionY);
    bool blackPawnDanger(qint16 positionX, qint16 positionY);

    bool whiteKnightDanger(qint16 positionX, qint16 positionY);
    bool whiteKingDanger(qint16 positionX, qint16 positionY);
    bool whiteQueenDanger(qint16 positionX, qint16 positionY);
    bool whiteBishopDanger(qint16 positionX, qint16 positionY);
    bool whiteCastleDanger(qint16 positionX, qint16 positionY);
    bool whitePawnDanger(qint16 positionX, qint16 positionY);
};

#endif // CHESSFUNCTION_H
