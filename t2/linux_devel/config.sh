#!/bin/sh

cp -f ./Makefile_Grafo ../grafo/Makefile
cp -f ./Makefile_Lista ../lista/Makefile
cp -rf ./headers ../
mkdir -p ../bin
mkdir -p ../obj
mkdir -p ../lib
cp -f ./libArcaboucoTeste.a ../lib/
