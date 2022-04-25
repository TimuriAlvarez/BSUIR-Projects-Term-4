default:
	clear
	make mount
	make clean
	sudo cp sources/* bin
	sudo cp scripts/* bin
	make unmount
	echo "In VB DOS type: cd bin and run.bat"
	VirtualBoxVM --startvm DOS

clean:
	sudo rm -f bin/*

mount:
	sudo modprobe nbd
	#path to your vhd
	sudo qemu-nbd -c /dev/nbd0 /home/timurialvarez/VirtualBox\ VMs/DOS/DOS.vhd
	#path to folder that will pretend to be a dos (to_send_dos for me)
	sudo mount /dev/nbd0p1 /home/timurialvarez/VBDOS

unmount:
	#path as in line 12
	sudo umount /home/timurialvarez/VBDOS
	sudo qemu-nbd -d /dev/nbd0
