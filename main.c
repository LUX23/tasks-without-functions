#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>

char *stoupper(char *str) // функция, приводящая буквы в строке к верхнему регистру
{
    char s;
    for (int i = 0; i < strlen(str); i++)
    {
        s = str[i]; // один символ

        if (((s >= 'a') && (s <= 'z')) || ((s >= 'а') && (s <= 'я')))
            s = s - 32; // сдвиг на верхний регистр по таблице ASCII

        if (s == 'ё')
            s = 'Ё';

        str[i] = s; // замена символа в строке
    }

    return str;
}

int stonum(char *str) // функция, преобразующая строку цифр в целое число
{
    int num = 0, sign = 1, i = 0; // n - число
                                  // sign - для передачи знака
                                  // i - пометка для певрого символа


    if (*str == '-') // учет отрицательного знака
    {
        sign = -1;
        i++; // первый символ отведен под знак
    }

    else if (*str == '+') // учет положительного знака
    {
        sign = 1;
        i++;
    }

    for (i; i < strlen(str); i++) // чтобы не затронуть возможные буквы в строке
        num = 10 * num + str[i] - '0'; // сдвиг числа на освободившийся разряд

    str++; // проход по элементам строки

    return num * sign; // передача знака числу
}

char *numtos (int num) // функция, преобразующая целое число в строку цифр
{
    int i = 0, rank = 0; // i - пометка для певрого символа
                         // rank - количество разрядов
    char sign = '\0', *str; // sign - для передачи знака

    if (num < 0) // учет отрицательного знака
    {
        sign = '-';
        i++; // первый символ отведен под знак
    }

    else if (num > 0) // учет положительного знака
    {
        sign = '+';
        i++; // первый символ отведен под знак
    }

    num = abs(num); // берем модуль числа, чтобы не было проблем с отрицательными числами

    for (int tmp = num; tmp != 0; tmp = tmp / 10)
        rank++; // подсчет разрядов

    if (num == 0) // исключение, это единственный разряд
        rank++;

    str = (char*)malloc((rank + i + 1) * sizeof(char)); // выделение памяти для строки

    str[0] = sign; // запись знака
    str[i + rank] = '\0'; // конец строки

    for (int j = rank + i; j > i; j--)
    {
        str[j - 1] = '0' + num % 10; // перевод цифр в символы с конца числа
        num = num / 10;
    }
    return str;
}

char *bintodec (char *bin) // функция, преобразуюущая двоичную строку в десятичную
{
    int num = 0;

    for (int i = 0; i < strlen(bin); i++) // проход по всей строке
    {
        num *= 2; // перевод в десятичную
        num += bin[i] - '0'; // прибавляем следующий разряд (потом этот разряд умножим на 2, для перевода в десятичную)
                             // сдвиг числа на последующий разряд
    }

    return numtos(num);
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    char str[100];
    char *fun;

    int num, ch;

    printf("\tКакую функцию хотите протестировать?\n\n"
           "1 - stoupper (а -> А)\n"
           "2 - stonum ('123' -> 123)\n"
           "3 - numtos (123 -> '123')\n"
           "4 - bintodec (10010 -> 18)\n\n");
    scanf("%d", &ch);

    while ((ch < 1) | (ch > 4))
    {
        printf("\nВведите число от 1 до 4! ");
        scanf("%d", &ch);
    }

    if (ch == 1)
    {
        printf("\n\tПриведение букв в строке к верхнему регистру.\n\n"
               "Введите строку букв: ");
        scanf("%s", &str);

        fun = stoupper(str);
        printf("Получено: %s\n", fun);
    }

    if (ch == 2)
    {
        printf("\n\tПреобразование строки цифр в целое число.\n\n"
               "Введите строку цифр: ");
        scanf("%s", &str);

        printf("\nПолучилось число: %d\n", stonum(str));
        printf("Проверка: %d + 11 = %d", stonum(str), stonum(str) + 11);
    }

    if (ch == 3)
    {
        printf("\n\tПреобразование целого числа в строку цифр.\n\n"
               "Введите число: ");
        scanf("%d", &num);

        fun = numtos(num);
        printf("Получилась строка: %s\n", fun);
        free(fun);
    }

    if (ch == 4)
    {
        printf("\n\tПреобразование двоичной записи числа в десятичную.\n\n"
               "Введите строку цифр: ");
        scanf("%s", &str);

        fun = bintodec(str);
        printf("Получилась десятичная строка: %s\n", fun);
        free(fun);
    }

    getch();
    return 0;
}
