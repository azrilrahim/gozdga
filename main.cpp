/*
#-----------------------------------#
#                                   #
# Copyright (C) 2016 Azril Rahim    #
#                                   #
# azrilazam@gmail.com               #
#                                   #
#-----------------------------------#
*/

#include <QCoreApplication>
#include "gozdga.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    GozDga goz;

    goz.executeA(argc,argv);
    return 0;

    return a.exec();
}
