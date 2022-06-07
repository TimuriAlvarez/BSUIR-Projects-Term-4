@ECHO OFF
tasm /m2 lab.asm
tlink /3 lab.obj
lab.exe
del *.obj
del *.map
