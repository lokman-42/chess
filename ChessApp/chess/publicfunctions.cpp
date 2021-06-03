#include "publicfunctions.h"
#include <QFile>

publicfunctions::publicfunctions()
{

}

void publicfunctions::fileReadOperation(QString filePath, QByteArray &Data)
{
    QFile file;
    file.setFileName(filePath);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    Data = file.readAll();
    file.close();
}

bool publicfunctions::fileWritingOperation(QString filePath, QByteArray Data)
{
    QFile fileDriver(filePath);
    if(fileDriver.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text)) {
        QTextStream textStream(&fileDriver);
        textStream << Data;
        fileDriver.close();
        return true;
    }
    return false;
}
