set oldpath=%path%
path=C:\BORLANDC/BIN
path=%path%;C:\BIN
cd BIN
lab.bat
cd ..
path=%oldpath%
set oldpath=
