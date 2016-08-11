
#-----------------------------------#
#                                   #
# Copyright (C) 2016 Azril Rahim    #
#                                   #
# azrilazam@gmail.com               #
#                                   #
#-----------------------------------#

INTRODUCTION
============
GOZDGA is Qt C/C++ implementation to generate GameOver Zeus (GOZ)
possible C2, P2P BOTS domain name based on Domain Generated
algorithm. The codes is taking the reversed engineer SEED value
from GOZ family codes

The codes should produced significant possible results to
immediate variants of GoZ family Malware.

GoZ DGA is generated against date input. GoZ generates about
10000 domain per day. Using GOZDGA, a specific domains list can
be produced on targeted date.


REQUIREMENT
-------------
TIG is a cross platform application that runs on MAC, WIN32/64, UNIX,
OS2 and LINUX. It is a C/C++ application that is coded entirely on
C++ Qt framework. For 64bit compatiblity, all compiliation for TIG
requires the following minimum specifications library to be installed

    *Qt 5.4 (https://www.qt.io/download-open-source/)


INSTALLATION
-------------

    Compilation
    -----------
    1.  Please ensure all the dependencies libraries specified in the
        requirement sections are properly installed

    2.  Extract all the files in the desired working directory.
        e.g: /home/user/project/GOZDGA

    3.  The create a proper make file for compilation, you need to access
        to the qmake command that comes with Qt framework. qmake command
        must be issued inside the GOZDGA work directory.

        %> cd /home/user/project/GOZDGA
        %> /<qt install dir>/bin/qmake

    4.  After the qmake process is finish, you can called the make command
        to complete the compilation

        %> cd /home/user/project/GOZDGA
        %> make

    5. After a successful compilation, a TIG file will be created.
       To invoke GOZDGA application:

        %> cd /home/user/project/GOZDGA
        %> ./gozdga


COMMAND LINE ARGUMENTS
----------------------
    n=: number of domain to be generated (e.g 1000)
    f=: output filename if the result need to be write to a file
    d=: past, present or future date that DGA to be generated
        format: DD-MM-YYYY


EXAMPLE
-------------
    1.  Display result on screen
        %> ./gozdga n=1000 d=12-04-2016

    2.  Save result on a file
        %> ./gozdga n=1000 d=12-04-2016 f=./result.txt



OUTPUT
-------
The output will be a single domain per line
    e.g
    gdgdhdddjkdgh.com
    jdyeeje7653dfg.net
    ...
    ...



MAINTAINER
----------
* Azril Rahim <azrilazam@gmail.com>
