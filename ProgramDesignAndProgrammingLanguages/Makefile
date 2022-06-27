# Variables
lab	=

default:
	make clean
	cp -f run.bat dos
	cp -f Lab$(lab)/*.asm dos/BIN
	cp -f Lab$(lab)/*.bat dos/BIN
	dosbox

clean:
	clear
	rm -f dos/run.bat
	rm -f dos/BIN/*
