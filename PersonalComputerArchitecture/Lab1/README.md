## Personal Computer Architecture Lab 1
Year and term: 2nd year, 4th term.

Discipline:    Personal Computer Architecture.

OS:            Linux (files), DOS (bios, registers).

## Terms of reference
Разработать  программный  модуль  реализации  процедуры  передачи (приема) байта информации через последовательный интерфейс.

Программа должна демонстрировать программное взаимодействие с последовательным интерфейсом с использованием следующих механизмов:

1.	прямое взаимодействие с портами ввода-вывода (write, read)
2.	использование BIOS прерывания 14h,
3.	работа с COM-портом через регистры как с устройством ввода-вывода.

## Compilation and Running
Option 1:	Ports as files (direct usage)

You will need gcc and make installed first, then you can use commands below:

1.	Compilation:	`make build`
2.	Running:		`make run`
3.	Cleaning:		`make clear`

Option 2:	Using BIOS 14h interruption

Compilation, linking and runing:

In the directory C:\DOS> type:

```
cd DOS
bin\tasm.exe t\lab1bios.asm t\l1b.obj
bin\tlink.exe t\l1b.obj t\l1b
t\l1b.exe
```

Clearing: `DEL T`, then type `Y`

Option 3:	Ports as registers (devices)

```
bin\tasm.exe t\lab1regs.asm t\l1r.obj
bin\tlink.exe t\l1r.obj t\l1r
t\l1r.exe
```

## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

## Copyright
This repository is under exclusive copyright.

I do grant each User of GitHub a nonexclusive, worldwide license to use, display, and perform My Content through the GitHub Service and to reproduce My Content solely on GitHub as permitted through GitHub's functionality but that is all. No other licences are provided for Users of GitHub.

© All rights reserved, 2022
