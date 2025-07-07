@echo off
g++ -std=c++17 -Wall -Wextra ^
 main.cpp ^
 CmdRender/CmdRender.cpp ^
 CmdRender/utils/fileInteract.cpp ^
 CmdRender/2dEntity/Shape2d.cpp ^
 -o main.exe
