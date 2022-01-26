#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>

char *stoupper(char *str) // �������, ���������� ����� � ������ � �������� ��������
{
    char s;
    for (int i = 0; i < strlen(str); i++)
    {
        s = str[i]; // ���� ������

        if (((s >= 'a') && (s <= 'z')) || ((s >= '�') && (s <= '�')))
            s = s - 32; // ����� �� ������� ������� �� ������� ASCII

        if (s == '�')
            s = '�';

        str[i] = s; // ������ ������� � ������
    }

    return str;
}

int stonum(char *str) // �������, ������������� ������ ���� � ����� �����
{
    int num = 0, sign = 1, i = 0; // n - �����
                                  // sign - ��� �������� �����
                                  // i - ������� ��� ������� �������


    if (*str == '-') // ���� �������������� �����
    {
        sign = -1;
        i++; // ������ ������ ������� ��� ����
    }

    else if (*str == '+') // ���� �������������� �����
    {
        sign = 1;
        i++;
    }

    for (i; i < strlen(str); i++) // ����� �� ��������� ��������� ����� � ������
        num = 10 * num + str[i] - '0'; // ����� ����� �� �������������� ������

    str++; // ������ �� ��������� ������

    return num * sign; // �������� ����� �����
}

char *numtos (int num) // �������, ������������� ����� ����� � ������ ����
{
    int i = 0, rank = 0; // i - ������� ��� ������� �������
                         // rank - ���������� ��������
    char sign = '\0', *str; // sign - ��� �������� �����

    if (num < 0) // ���� �������������� �����
    {
        sign = '-';
        i++; // ������ ������ ������� ��� ����
    }

    else if (num > 0) // ���� �������������� �����
    {
        sign = '+';
        i++; // ������ ������ ������� ��� ����
    }

    num = abs(num); // ����� ������ �����, ����� �� ���� ������� � �������������� �������

    for (int tmp = num; tmp != 0; tmp = tmp / 10)
        rank++; // ������� ��������

    if (num == 0) // ����������, ��� ������������ ������
        rank++;

    str = (char*)malloc((rank + i + 1) * sizeof(char)); // ��������� ������ ��� ������

    str[0] = sign; // ������ �����
    str[i + rank] = '\0'; // ����� ������

    for (int j = rank + i; j > i; j--)
    {
        str[j - 1] = '0' + num % 10; // ������� ���� � ������� � ����� �����
        num = num / 10;
    }
    return str;
}

char *bintodec (char *bin) // �������, �������������� �������� ������ � ����������
{
    int num = 0;

    for (int i = 0; i < strlen(bin); i++) // ������ �� ���� ������
    {
        num *= 2; // ������� � ����������
        num += bin[i] - '0'; // ���������� ��������� ������ (����� ���� ������ ������� �� 2, ��� �������� � ����������)
                             // ����� ����� �� ����������� ������
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

    printf("\t����� ������� ������ ��������������?\n\n"
           "1 - stoupper (� -> �)\n"
           "2 - stonum ('123' -> 123)\n"
           "3 - numtos (123 -> '123')\n"
           "4 - bintodec (10010 -> 18)\n\n");
    scanf("%d", &ch);

    while ((ch < 1) | (ch > 4))
    {
        printf("\n������� ����� �� 1 �� 4! ");
        scanf("%d", &ch);
    }

    if (ch == 1)
    {
        printf("\n\t���������� ���� � ������ � �������� ��������.\n\n"
               "������� ������ ����: ");
        scanf("%s", &str);

        fun = stoupper(str);
        printf("��������: %s\n", fun);
    }

    if (ch == 2)
    {
        printf("\n\t�������������� ������ ���� � ����� �����.\n\n"
               "������� ������ ����: ");
        scanf("%s", &str);

        printf("\n���������� �����: %d\n", stonum(str));
        printf("��������: %d + 11 = %d", stonum(str), stonum(str) + 11);
    }

    if (ch == 3)
    {
        printf("\n\t�������������� ������ ����� � ������ ����.\n\n"
               "������� �����: ");
        scanf("%d", &num);

        fun = numtos(num);
        printf("���������� ������: %s\n", fun);
        free(fun);
    }

    if (ch == 4)
    {
        printf("\n\t�������������� �������� ������ ����� � ����������.\n\n"
               "������� ������ ����: ");
        scanf("%s", &str);

        fun = bintodec(str);
        printf("���������� ���������� ������: %s\n", fun);
        free(fun);
    }

    getch();
    return 0;
}
