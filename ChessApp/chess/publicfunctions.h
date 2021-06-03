#ifndef PUBLICFUNCTIONS_H
#define PUBLICFUNCTIONS_H

#include <QDebug>

class publicfunctions
{
public:
    publicfunctions();
    static void fileReadOperation(QString filePath, QByteArray& Data);
    static bool fileWritingOperation(QString filePath, QByteArray Data);
};

#endif // PUBLICFUNCTIONS_H
