#! /bin/bash
# Compiler for the main programs from this repo
# v1

g++ client.cpp -o client.exe -lncurses
g++ server.cpp -o server.exe -lncurses