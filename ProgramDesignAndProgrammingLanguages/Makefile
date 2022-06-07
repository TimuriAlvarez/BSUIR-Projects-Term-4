# Variables
lab	=

default:
	make clean
	cp -f Lab$(lab)/*.asm bin
	cp -f Lab$(lab)/*.bat bin
	cp -f run.bat dosbox

	#
	# In DOSBOX type: `run`
	#

	dosbox

clean:
	clear
	rm -f bin/*
