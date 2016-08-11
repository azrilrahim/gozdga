/*
#-----------------------------------#
#                                   #
# Copyright (C) 2016 Azril Rahim    #
#                                   #
# azrilazam@gmail.com               #
#                                   #
#-----------------------------------#
*/

#include "gozdga.h"

GozDga::GozDga(QObject *parent) : QObject(parent)
{

}

GozDga::~GozDga()
{

}

int GozDga::executeA(int argc, char *argv[])
{
    quint32 numOfDomain;
    QString outfile;
    QString agStr;
    quint16 DD,MM,YY;
    QString dateAttack;

    numOfDomain = 0;
    outfile.clear();

    DD = 0;
    MM = 0;
    YY = 0;

    for (int i = 1; i < argc; i++){
        agStr = agStr + argv[i] + " ";
    }

    agStr = agStr.replace("&", " ");

    QStringList agStrL = agStr.trimmed().split(" ");

    for (int ag = 0; ag < agStrL.size(); ag++)
    {
        //qDebug() << "ag:" << ag;
        agStr = agStrL[ag];
        agStr = agStr.trimmed();

        if (agStr.isEmpty()){
            continue;
        }



        //printf("%s\n",agStr.toStdString().c_str());
        QStringList argvL = agStr.split("=");

        if (argvL.size() != 2){
            printf("Invalid argument for input #%d\n",ag);
            return 0;
        }

        if (argvL.at(0) == "n"){
            numOfDomain = argvL.at(1).toInt();
            continue;
        }


        if (argvL.at(0) == "d")
        {
            dateAttack = argvL.at(1);
            QList<QString>dt = dateAttack.trimmed().split("-");

            DD = dt.at(0).toInt();
            MM = dt.at(1).toInt();
            YY = dt.at(2).toInt();
            //qDebug() << "done date";
            continue;
        }

        if (argvL.at(0) == "f"){

            outfile = argvL.at(1);
            continue;
        }

    }

    //qDebug() << "of looping";

    if (numOfDomain == 0)
    {
        printf("GoZ: Missing or Invalid number of domain to be generated\n");
        return -1;
    }

    if (dateAttack.trimmed().isEmpty())
    {
        printf("Missing or Invalid date\n");
        return -1;
    }

    this->generate(numOfDomain,DD,MM,YY,outfile);
    return 0;
}

void GozDga::generate(quint32 maxDomain, quint16 day, quint16 month, quint16 year, QString outfile)
{
    QString dgaDomainName;

    //check endian
    this->imBE = this->isBE();
    QFile fs;

    if (!outfile.trimmed().isEmpty()){

        fs.setFileName(outfile);
        fs.open(QIODevice::WriteOnly | QIODevice::Text);
    }
    //generate domain name for maxDomain
    for (quint32 id = 0; id < maxDomain; id++){

        dgaDomainName = this->getDomainName(id,day,month,year);
        if (!outfile.trimmed().isEmpty()){
            dgaDomainName.append('\n');
            fs.write(dgaDomainName.toLocal8Bit());
        }
        else
        {
            printf("%s\n",dgaDomainName.toStdString().c_str());
        }
    }

    if (!outfile.trimmed().isEmpty()){
        fs.close();
    }

}

QString GozDga::getDomainName(quint32 id, quint16 day, quint16 month, quint16 year){

    QString seedHex1;
    QString seedHex2;
    quint8 mask;
    quint8 start;
    quint32 seedInt;
    QString domain;

    mask = 0;
    start = 0;
    domain.clear();
    seedHex1 = this->getSeedHEX(id,day,month,year);

    for (mask = 0; mask < 16; mask+=4){
        start = mask * 2;
        seedHex2 = seedHex1.mid(start,8);
        seedInt = this->hexToInt(seedHex2);//seedHex2.toUInt(0,16);
        domain.append(this->getDomainPart(seedInt,8));
    }

    //qDebug() << "id:" << id;

    if ((id % 4) == 0)
    {   domain.append(".com");
        return domain;
    }

    if ((id % 3) == 0){
        domain.append(".org");
        return domain;
    }

    if ((id % 2) == 0){
        domain.append(".biz");
        return domain;
    }


    domain.append(".net");
    return domain;

}
quint32 GozDga::hexToInt(QString hex){

    QString tmp;
    quint16 loc = hex.size();

    while(1){
        tmp.append(hex.mid(loc -2,2));
        loc = loc -2;
        if (loc == 0)
            break;
    }
    //qDebug() << "hextoint seed from hex" << tmp.toUInt(0,16);
    return tmp.toUInt(0,16);
}

quint16 GozDga::toLE(quint16 val){


    unsigned char *ptr = (unsigned char *)&val;
        return(ptr[0] << 8 | ptr[1]);
}

quint32 GozDga::toLE(quint32 val){
    unsigned char *ptr = (unsigned char *)&val;
        return (ptr[0] << 24) | (ptr[1] << 16) | (ptr[2] << 8) | ptr[3];
}

bool GozDga::isBE()
{
    quint16 id;
    unsigned char *p;

    id = 1;
    p = (unsigned char*)&id;
    if (p[0] == '\x01')
        return false;

    return true;
}

QString GozDga::getSeedHEX(quint32 id, quint16 day, quint16 month, quint16 year){

    QCryptographicHash md5(QCryptographicHash::Md5);
    QString key("\x01\x05\x19\x35");

    md5.reset();

    if (this->imBE){
        id = this->toLE(id);
        year = this->toLE(year);
        day = this->toLE(day);
        month = this->toLE(month);
    }

    md5.addData((const char*)&id,4);
    md5.addData((const char*)&year,2);
    md5.addData(key.toLatin1().data());
    md5.addData((const char*)&month,2);
    md5.addData(key.toLatin1().data());
    md5.addData((const char*)&day,2);
    md5.addData(key.toLatin1().data());

    return md5.result().toHex();


}

QString GozDga::getDomainPart(quint32 seed, quint8 maxSize){

    QString tmpd;
    QString tmpd2;
    QChar c;
    quint32 edx;

    for (quint8 i = 0; i < maxSize; i++){

        edx = seed % 36;
        seed /=36;

        if (edx > 9)
            c = QChar(QChar('a').toLatin1() + (edx - 10));
        else
            c = QChar(edx + QChar('0').toLatin1());
        tmpd2 = tmpd;
        tmpd = c;
        tmpd.append(tmpd2);

        if (seed == 0)
            break;
    }
    return tmpd;
}

