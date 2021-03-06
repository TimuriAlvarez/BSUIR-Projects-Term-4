# Program Design And Programming Languages Labs

## General information

| Information |                                          |
|-------------|------------------------------------------|
| Year        | 2nd                                      |
| Term        | 4th                                      |
| Discipline  | Program Design And Programming Languages |
| Quantity    | 8                                        |
| OS          | DOS (DOSBOX)                             |

# Lab 1

## Написать программу «Hello, world!»

### Terms of reference

1. При выполнении работы постараться рассмотреть как можно больше доступных программных сред для формирования и сборки ассемблерной программы.
2. Создать ассемблерные программы для двух вариантов исполняемых модулей (com и exe).

# Lab 2

## Удалить слово в строке, стоящее после заданного слова

### Terms of reference

1. Выделить буфер для хранения 200 символов.
2. Строку символов ввести с клавиатуры, при этом ввод строки символов может быть завершен клавишей Enter или по заполнению буфера полностью.
3. Дополнительный буфер для хранения промежуточных результатов обработки строки в памяти не выделять.
4. При использовании констант задавать их с помощью директивы EQU.
5. Старт программы, ввод-вывод данных и обработку ошибок оформлять выводом в консоль поясняющих строк.

# Lab 3

## Ввести массив целых чисел размерностью 30 элементов. Найти отношение разности максимального и минимального значений элементов к максимальному значению

### Terms of reference

1. Вид буфера для хранения массива и адресацию для доступа к его элементам выбрать самостоятельно.
2. Числовые данные вводятся с клавиатуры в виде строк символов (по умолчанию используется десятичная система счисления), при этом требуется производить проверку на переполнение разрядной сетки числа (по умолчанию используются знаковые 16-битные данные), для знаковых данных знак требуется хранить в представлении самого числа (в дополнительном коде).
3. При вводе числовых массивов можно указать число вводимых элементов.
4. При операциях с целыми числами требуется проверять полученный результат на возникновение ошибок и переполнений.
5. Формирование чисел с дробной частью по условию задачи выполнять в виде массива символов на основе только целочисленных арифметических операций (без использования FPU). Выполнить округление полученного числа до N-го символа дробной части.
6. Для лучшего оформления программы ввод-вывод чисел и часто повторяющиеся действия реализовать в виде процедур.
7. Старт программы, ввод-вывод данных и обработку ошибок оформлять выводом в консоли поясняющих строк.

# Lab 4

## Игра «Змейка»

### Gameplay

Ползаем, едим случайно появляющиеся в свободных местах яблочки и растем от этого в длину.

Выход за границы экрана означает возврат в поле с противоположной стороны (круглый мир).

|            |                                            |
|------------|--------------------------------------------|
| Окончание  | проигрыш – укус самого себя, выигрыш – нет |
| Информация | счет                                       |
| Усложнение | смена уровня (увеличение скорости)         |

### Terms of reference

1. Видеоигра должна иметь простую логику работы и только одно игровое поле (уровень).
2. Для работы с игровым полем использовать прямой доступ к видеопамяти в текстовом режиме (желательно 80×25 символов).
3. Для отображения объектов подобрать адекватные символы, а также установить отвечающие ситуации атрибуты – цвет, моргание.
4. Игровое поле должно также предоставлять игроку дополнительную информацию (счет, сообщения и т. п.).
5. Желательно рассмотреть работу с системными часами или таймером (с целью формирования задержек игрового цикла, а также генерации случайных чисел).

# Lab 5

## В выходной файл поместить только те строки входного файла, которые содержат указанное слово

### Terms of reference

1. Параметры обработки (включая описание путей к файлам) передавать в программу через параметры командной строки.
2. Буфер для обработки данных должен быть меньше обрабатываемого файла.
3. Под словом будем понимать набор символов, ограниченный пробелами, табуляциями, границами строки; максимальный размер слова – 50 символов.
4. Алгоритм обработки должен выполнять проверку на возникновение ошибок.
5. Старт программы, ввод-вывод данных и обработку ошибок оформлять выводом в консоли поясняющих строк.
6. Для тестирования программы подготовить файл размером больше 64 Кбайт.

# Lab 6

## Ввести массив чисел с плавающей точкой на 10 элементов. Для каждого элемента массива вычислить: {если Xi < 0, то Хi = (Xi)^2; если Xi > 0, то Хi = (Xi)^3}

### Terms of reference

1. Головная программа, включающая описание переменных, ввод-вывод данных и вызов ассемблерной процедуры, должна быть реализована на языке программирования C\C++ (система программирования (компилятор) выбирается студентом).
2. Реализовать основной алгоритм обработки данных на математическом сопроцессоре как процедуру на языке ассемблера. Создание тела процедуры допускается с использованием встроенного ассемблера (актуально для головной программы, написанной для Windows).
3. Алгоритм обработки данных должен выполнять проверку на возникновение ошибок.
4. Для головной программы, написанной для Windows (модель памяти FLAT), в процедуре использовать работу с расширенными регистрами процессора.
5. Старт программы, ввод-вывод данных и обработку ошибок оформлять выводом в консоли поясняющих строк.

# Lab 7

## Написать программу для обработки строки вида «A1 x 1 A2 x2 ... xN-1 AN», где Ai – числа (i в диапазоне [ 1...N ]), xi – одна из ариф-метических операций (для обработки арифметических операций сформировать оверлейные функции, в память одновременно может быть загружена только одна функция, загрузку функций оптимизировать)

### Terms of reference

1. Для передачи изменяемых параметров в программу использовать командную строку.
2. Алгоритм обработки данных должен выполнять проверку на возникновение ошибок.
3. Старт программы, ввод-вывод данных и обработку ошибок оформлять выводом в консоли поясняющих строк.

# Lab 8

## Написать резидентную программу «просмотрщик текстового файла» (viewer). Имя файла для просмотра задавать при запуске программы

### Terms of reference

1. Для передачи параметров в программу использовать командную строку.
2. Алгоритм обработки данных должен выполнять проверку на возникновение ошибок.
3. Резидентная программа должна строить обработчик перехваченного прерывания с учетом других возможных резидентных программ, связанных с этим прерыванием.
4. Вывод данных на экран в резидентной части программы рекомендуется не выполнять с использованием прерываний DOS, лучше использовать прямой доступ к видеопамяти.
5. Старт программы, ввод-вывод данных и обработку ошибок оформлять выводом в консоли поясняющих строк.

# Contributing

Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

# Copyright

This repository is under exclusive copyright.

I do grant each User of GitHub a nonexclusive, worldwide license to use, display, and perform My Content through the GitHub Service and to reproduce My Content solely on GitHub as permitted through GitHub's functionality but that is all. No other licences are provided for Users of GitHub.

© All rights reserved, 2022
