#! /usr/bin/env bash

jasper_home="ftp://ftp.remotesensing.org/gdal/jasper-1.900.1.uuid.tar.gz"


wget $jasper_home

./configure --enable-shared --with-pic --prefix=/opt/local