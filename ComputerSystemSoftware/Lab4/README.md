## Computer System Software Lab 4
Year and term: 2nd year, 4th term.

Discipline:	Computer System Software.

OS:			Linux.

WSL is also acceptable, but I cannot guarantee that the program will execute correctly.

## Terms of reference
Взаимодействие и синхронизация процессов

Синхронизация процессов с помощью сигналов и обработка сигналов таймера.

Задача — управление дочерними процессами и упорядочение вывода в stdout от них, используя сигналы SIGUSR1 и SIGUSR2.

Действия родительского процесса

1.	При вводе символа «+» pодительский процесс (P) порождает дочерний процесс (C_k) и сообщает об этом.
2.	При вводе символа «-» P удаляет последний порожденный C_k, сообщает об этом и о количестве оставшихся.
3.	При вводе символа «k» P удаляет все C_k и сообщает об этом.
4.	При вводе символа «m» P запрещает всем C_k выводить статистику (см. ниже).
5.	При вводе символа «u» P разрешает всем C_k выводить статистику.
6.	При вводе символов «k <num>» P удаляет C_<num> и сообщает об этом.
7.	При вводе символов «m <num>» P запрещает C_<num> выводить статистику.
8.	При вводе символов «u <num>» P разрешает C_<num> выводить статистику.
9.	При вводе символов «p <num>» P запрещает всем C_k вывод и запрашивает C_<num> вывести свою статистику. По истечению заданного времени (5 с, например), если не введен символ «g», разрешает всем C_k снова выводить статистику.
10.	По нажатию клавиши «q» P удаляет все C_k, сообщает об этом и завершается.

Действия дочернего процесса

1.	Дочерний процесс во внешнем цикле заводит будильник (nanosleep(2)) и входит в вечный цикл, в котором в режиме чередования заполняет структуру, содержащую пару переменных типа int, значениями {0, 0} и {1, 1} (см. раздел «Проблемы неатомарного доступа» темы «Сигналы»).
2.	При получении сигнала от будильника проверяет содержимое структуры, собирает статистику и повторяет тело внешнего цикла.
3.	Через заданное количество повторений внешнего цикла (например, через 100) дочерний процесс, если ему разрешено, выводит свои PPID, PID и 4 числа — количество разных пар, зарегистрированных к моменту получения сигнала от будильника.
4.	Вывод осуществляется посимвольно.
5.	C_k запрашивает доступ к stdout у P и осуществляет вывод после подтверждения. По завершению вывода C_k сообщает P об этом.
6.	Следует подобрать интервал времени ожидания и количество повторений внешнего цикла, чтобы статистика была значимой.

## Compilation and Running
To compile the program you will need GCC, gbd and make:

Build executable, run it and both commands:
```
make build
make run
make default    or just    make
```
Build executable with debug information, debug it with gdb and both commands:
```
make dbuild
make drun
make debug
```
Clean gcc folder:
```
make clean
```


## Test / Preview
PROGRAMM tests / previews:

## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

## Copyright
This repository is under exclusive copyright.

I do grant each User of GitHub a nonexclusive, worldwide license to use, display, and perform My Content through the GitHub Service and to reproduce My Content solely on GitHub as permitted through GitHub's functionality but that is all. No other licences are provided for Users of GitHub.

© All rights reserved, 2022
