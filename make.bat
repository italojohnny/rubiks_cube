echo off

windres resources.rc resources.o

mingw32-make Magic_Cube

del *.o
rem del *.exe

pause
cls