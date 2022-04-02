## Basics of Algorithmization and Programming Lab 1
Year and term: 2nd year, 4th term.

Discipline:    Basics of Algorithmization and Programming.

OS:            DOS (VM on Linux/Windows).

## Terms of reference
Написать программу для вывода на экран строки символов.

## Compilation and Running
To compile the program you will need tasm.exe and tl.exe:

Mounting folder C:
```
Z:\>    mount C ~/DOS
Z:\>    C:
```
Building, linking and running COM applicatiion:
```
C:\>    bin\tasm.exe t\Lab1com.asm t\l1c.obj
C:\>    bin\tlink.exe /t t\l1c.obj t\l1c
C:\>    t\l1c.com
```
Building, linking and running EXE applicatiion:
```
C:\>    bin\tasm.exe t\Lab1exe.asm t\l1e.obj
C:\>    bin\tlink.exe t\l1e.obj t\l1e
C:\>    t\l1e.exe
```

## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

## Copyright
This repository is under exclusive copyright.

I do grant each User of GitHub a nonexclusive, worldwide license to use, display, and perform My Content through the GitHub Service and to reproduce My Content solely on GitHub as permitted through GitHub's functionality but that is all. No other licences are provided for Users of GitHub.

© All rights reserved, 2022