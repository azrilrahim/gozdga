/*
#-----------------------------------#
#                                   #
# Copyright (C) 2016 Azril Rahim    #
#                                   #
# azrilazam@gmail.com               #
#                                   #
#-----------------------------------#
*/

#ifndef GOZDGA_H
#define GOZDGA_H

#include <QObject>
#include <QCryptographicHash>
#include <QDebug>
#include <QFile>

class GozDga : public QObject
{
    Q_OBJECT
public:
    explicit GozDga(QObject *parent = 0);
    ~GozDga();
    int executeA(int argc, char *argv[]);
    void generate(quint32 maxDomain,quint16 day, quint16 month, quint16 year,QString outfile = NULL);

private:

    QString getDomainName(quint32 id, quint16 day, quint16 month, quint16 year);
    QString getSeedHEX(quint32 id, quint16 day, quint16 month, quint16 year);
    QString getDomainPart(quint32 seed,quint8 maxSize);
    quint32 hexToInt(QString hex);

    bool isBE();

    bool imBE;
    quint16 toLE(quint16 val);
    quint32 toLE(quint32 val);

    //QString seedHEX1;
    //QString seedHEX2;

signals:

public slots:
};

#endif // GOZDGA_H
