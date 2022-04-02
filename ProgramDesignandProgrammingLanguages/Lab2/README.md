## Basics of Algorithmization and Programming Lab 2
Year and term: 2nd year, 4th term.

Discipline:    Basics of Algorithmization and Programming.

OS:            DOS (VM on Linux/Windows).

## Terms of reference
Common Terms of reference:

1.	Выделить буфер для хранения 200 символов.
2.	Строку символов ввести с клавиатуры, при этом ввод строки символов может быть завершен клавишей Enter или по заполнению буфера полностью.
3.	Дополнительный буфер для хранения промежуточных результатов обработки строки в памяти не выделять.
4.	При использовании констант задавать их с помощью директивы EQU.
5.	Старт программы, ввод-вывод данных и обработку ошибок оформлять выводом в консоль поясняющих строк.

Personal Terms of reference:

1.	Удалить слово в строке, стоящее после заданного слова.

## Compilation and Running
To compile the program you will need tasm.exe and tl.exe:

Mounting folder C:
```
mount C DOS
C
```
Building, linking and running the applicatiion:
```
bin\tasm.exe t\Lab2.asm t\l.obj
bin\tlink.exe t\l.obj t\l
t\l.exe
```

## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

## Copyright
This repository is under exclusive copyright.

I do grant each User of GitHub a nonexclusive, worldwide license to use, display, and perform My Content through the GitHub Service and to reproduce My Content solely on GitHub as permitted through GitHub's functionality but that is all. No other licences are provided for Users of GitHub.

© All rights reserved, 2022