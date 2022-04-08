// ЮФУ, ИКТИБ, МОП ЭВМ, КТБО 1-10
// Алгоритмизация и программирование
// Индивидуальное задание 2021
// Белоконь Данил Дмитриевич
// 09.01.2021
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Source.h"
#include "Source2.h"
#include <fstream>
using namespace std;
// Структура в которой хранятся данные об ОДПУ из файла details.txt
struct details1
{
    // ml - месяц, yl - год
    long long int ml, yl;
    // bq - массив показаний для каждого вида ресурсов
    long long int bq[7];
};
// Структура в которой хранятся данные о ИПУ из файла details.txt
struct details2
{
    // ml2 - месяц, yl2 - год
    long long int ml2, yl2;
    // bq2 - массив показаний для каждого вида ресурсов
    long long int bq2[7];
    // n2 - номер квартиры
    long long int n2;
};
// Структура с результирующими значениями
struct result
{
    // expflat – потребление заданного в запросе ресурса на основании показаний ИПУ
    // costflat - начисление за потребленный ресурс на основании показаний ИПУ
    // expodn - потребление заданного в запросе ресурса, относящееся на ОДН
    // costodn - начисление за ОДН по данному ресурсу
    long long int expflat, costflat, expodn, costodn;
    // dom - потребление всего дома по ОДПУ в указанный период
    // ipusum - сумма потребления всех квартир по ИПУ в указанный период
    long long int dom, ipusum, razndip;
    // ml3 - месяц, yl3 - год
    long long int ml3, yl3;
};
// Подпрограмма сортирует показания ОДПУ из фала details.txt по дате
void upor(long long int a, struct details1* ptr3) // Подпрограмма получает массив структур details1* ptr3 и его размерность а
{
    for (int k = 0; k < a - 1; k++)
    {
        for (int l = 0; l < a - k - 1; l++)
        {
            if (ptr3[l].yl == ptr3[l + 1].yl)
            {
                if (ptr3[l].ml > ptr3[l + 1].ml)
                {
                    swap(*(ptr3 + l), *(ptr3 + l + 1));
                }
            }
            else
            {
                if (ptr3[l].yl > ptr3[l + 1].yl)
                {
                    swap(*(ptr3 + l), *(ptr3 + l + 1));
                }
            }
        }
    }
}
// Подпрограмма делает первую сортировку показаний ИПУ из фала details.txt по дате
void upor2(long long int a, struct details2* ptr4) // Подпрограмма получает массив структур details2* ptr4 и его размерность а
{
    for (int k = 0; k < a - 1; k++)
    {
        for (int l = 0; l < a - k - 1; l++)
        {
            if (ptr4[l].yl2 == ptr4[l + 1].yl2)
            {
                if (ptr4[l].ml2 > ptr4[l + 1].ml2)
                {
                    swap(*(ptr4 + l), *(ptr4 + l + 1));
                }
            }
            else
            {
                if (ptr4[l].yl2 > ptr4[l + 1].yl2)
                {
                    swap(*(ptr4 + l), *(ptr4 + l + 1));
                }
            }
        }
    }
}
// Подпрограмма делает вторую сортировку показаний ИПУ из фала details.txt по квартирам
void upor3(long long int a, struct details2* ptr4) // Подпрограмма получает массив структур details2* ptr4 и его размерность а
{
    for (int k = 0; k < a - 1; k++)
    {
        for (int l = 0; l < a - k - 1; l++)
        {
            if (ptr4[l].n2 > ptr4[l + 1].n2)
            {
                swap(*(ptr4 + l), *(ptr4 + l + 1));
            }
        }
    }
}
int main()
{
    // n - колличество квартир в доме
    // sd - общая площадь всех (жилых и нежилых) помещений в доме
    // q - количество различных ресурсов, которые потребляют жильцы дома
    // l - общее количество записей о показаниях общедомовых приборов учета
    // m - общее количество записей о показаниях ИПУ
    // flat - номер квартиры из файла input.txt
    // startmonth - cтартовый месяц из файла input.txt
    // startyear - стартовый год из файла input.txt
    // endmonth - конечный месяц из файла input.txt
    // endyear - конечный год из файла input.txt
    // vremper1 - временная переманная для хранения требуемого тарифа оплаты за единицу расхода данного ресурса по запросу
    // vremper2 - временная переменная для хранения порядкового номера vremper1
    // k = переменая для будущего, в ней будет хранится размерность массива структур для структуры result
    // sumExpFlat - суммарное потребление заданного в запросе ресурса в указанной квартире по ИПУ
    // sumCostFlat - суммарное начисление за потребленный ресурс указанной квартирой по ИПУ
    // sumExpODN - суммарное потребление заданного в запросе ресурса, относящееся на ОДН
    // sumCostODN - суммарное начисление за ОДН по данному ресурсу
    long long int n, sd, q, l, m, flat, startmonth, startyear, endmonth, endyear, vremper1, vremper2, k = 0, sumExpFlat = 0, sumCostFlat = 0, sumExpODN = 0, sumCostODN = 0;
    // skv - переменная для вычисления формулы: (площадь квартиры)/(площадь всего дома)
    double skv;
    // resource - наименование ресурса из файла input.txt
    char resource[6];
    // Открытие выходного файла answet.txt
    FILE* outfile = fopen("answer10.txt", "w");
    // Создание массива структур ptr1
    home ptr1[1001];
    // Вызов функции из библиотеки "Source.h"
    vvodhome(ptr1, &n, &sd);
    // Создание массива структур ptr2
    taxes ptr2[7];
    // Вызов функции из библиотеки "Source2.h"
    vvodtaxes(ptr2, &q);
    // Открытие файла details.txt
    FILE* inf1 = fopen("details.txt", "r");
    fscanf(inf1, "%lld", &l);
    // Создание массива структур ptr3
    struct details1* ptr3 = new struct details1[l];
    for (int i = 0; i < l; i++)
    {
        fscanf(inf1, "%lld.%lld", &ptr3[i].ml, &ptr3[i].yl);
        for (int j = 0; j < q; j++)
        {
            fscanf(inf1, "%lld", &ptr3[i].bq[j]);
        }
    }
    fscanf(inf1, "%lld", &m);
    // Создание массива структур ptr4
    struct details2* ptr4 = new struct details2[m];
    for (int i = 0; i < m; i++)
    {
        fscanf(inf1, "%lld.%lld", &ptr4[i].ml2, &ptr4[i].yl2);
        fscanf(inf1, "%lld", &ptr4[i].n2);
        for (int j = 0; j < q; j++)
        {
            fscanf(inf1, "%lld", &ptr4[i].bq2[j]);
        }
    }
    fclose(inf1);
    // Вызов функции upor
    upor(l, ptr3);
    // Вызов функции upor1
    upor2(m, ptr4);
    // Вызов функции upor2
    upor3(m, ptr4);
    FILE* inf2 = fopen("input.txt", "r");
    fscanf(inf2, "%lld", &flat);
    fscanf(inf2, "%s", &resource);
    fscanf(inf2, "%lld.%lld-%lld.%lld", &startmonth, &startyear, &endmonth, &endyear);
    fclose(inf2);
    // vremper3 - вспомогательная переменная для присваивания резервированного значения
    int vremper3 = 0;
    for (int i = 0; i < q; i++)
    {
        if (strcmp(resource, ptr2[i].rq) == 0)
        {
            vremper1 = ptr2[i].p;
            vremper2 = i;
            vremper3 = ptr2[i].kq;
        }
    }
    for (int i = 0; i < m; i++)
    {
        if (ptr4[i].n2 == flat && (ptr4[i].ml2 + ptr4[i].yl2 * 12) >= (startmonth + startyear * 12) && (ptr4[i].ml2 + ptr4[i].yl2 * 12) <= (endmonth + endyear * 12))
        {
            k++;
        }
    }
    // Создание массива структур ptr5
    struct result* ptr5 = new struct result[k];
    // pot - переменная для индекса массива структур
    long long int pot = 0;
    for (int i = 0; i < l; i++)
    {
        if ((ptr3[i].ml + ptr3[i].yl * 12) >= (startmonth + startyear * 12) && (ptr3[i].ml + ptr3[i].yl * 12) <= (endmonth + endyear * 12))
        {
            if ((ptr3[i].ml + ptr3[i].yl * 12) == (ptr3[0].ml + ptr3[0].yl * 12))
            {
                ptr5[pot].ml3 = ptr3[i].ml;
                ptr5[pot].yl3 = ptr3[i].yl;
                ptr5[pot].dom = 0;
                pot++;
            }
            else
            {
                ptr5[pot].ml3 = ptr3[i].ml;
                ptr5[pot].yl3 = ptr3[i].yl;
                ptr5[pot].dom = ptr3[i].bq[vremper2] - ptr3[i - 1].bq[vremper2];
                pot++;
            }
        }
    }
    pot = 0;
    for (int i = 0; i < m; i++)
    {
        if ((ptr4[i].ml2 + ptr4[i].yl2 * 12) >= (startmonth + startyear * 12) && (ptr4[i].ml2 + ptr4[i].yl2 * 12) <= (endmonth + endyear * 12) && ptr4[i].n2 == 1)
        {
            if ((ptr4[i].ml2 + ptr4[i].yl2 * 12) == (ptr3[0].ml + ptr3[0].yl * 12))
            {
                ptr5[pot].ipusum = 0;
                pot++;
            }
            else
            {
                ptr5[pot].ipusum = 0;
                for (int j = 0; j < n; j++)
                {
                    ptr5[pot].ipusum += (ptr4[i + l * j].bq2[vremper2] - ptr4[i + l * j - 1].bq2[vremper2]);
                }
                pot++;
            }
        }
    }
    pot = 0;
    // sumpn - вспомогательная переменная для счета всех жителей в доме
    long long int sumpn = 0;
    for (int i = 0; i < n; i++)
    {
        sumpn += ptr1[i].pn;
    }
    if (vremper3 == 0)
    {
        skv = static_cast<double>(ptr1[flat - 1].sn) / static_cast<double>(sd);
    }
    else
    {
        if (vremper3 == 1)
        {
            skv = static_cast<double>(ptr1[flat - 1].pn) / static_cast<double>(sumpn);
        }
    }
    for (int i = 0; i < k; i++)
    {
        ptr5[i].razndip = ptr5[i].dom - ptr5[i].ipusum;
        ptr5[i].expodn = ptr5[i].razndip * skv;
        ptr5[i].costodn = ptr5[i].expodn * vremper1;
    }
    for (int i = 0; i < m; i++)
    {
        if (ptr4[i].n2 == flat && (ptr4[i].ml2 + ptr4[i].yl2 * 12) >= (startmonth + startyear * 12) && (ptr4[i].ml2 + ptr4[i].yl2 * 12) <= (endmonth + endyear * 12))
        {
            if ((ptr4[i].ml2 + ptr4[i].yl2 * 12) == (ptr3[0].ml + ptr3[0].yl * 12))
            {
                ptr5[pot].expflat = 0;
                ptr5[pot].costflat = 0;
                pot++;
            }
            else
            {
                ptr5[pot].expflat = ptr4[i].bq2[vremper2] - ptr4[i - 1].bq2[vremper2];
                ptr5[pot].costflat = ptr5[pot].expflat * vremper1;
                pot++;
            }
        }
    }
    for (int i = 0; i < k; i++)
    {
        sumExpFlat = sumExpFlat + ptr5[i].expflat;
        sumCostFlat = sumCostFlat + ptr5[i].costflat;
        sumExpODN = sumExpODN + ptr5[i].expodn;
        sumCostODN = sumCostODN + ptr5[i].costodn;
    }
    fprintf(outfile, "%lld %lld %lld %lld\n", sumExpFlat, sumCostFlat, sumExpODN, sumCostODN);
    fprintf(outfile, "%lld\n", k);
    for (int i = 0; i < k; i++)
    {
        if (ptr5[i].ml3 < 10)
        {
            fprintf(outfile, "%d", 0);
            fprintf(outfile, "%lld.%lld", ptr5[i].ml3, ptr5[i].yl3);
        }
        else
        {
            fprintf(outfile, "%lld.%lld", ptr5[i].ml3, ptr5[i].yl3);
        }
        fprintf(outfile, " %lld %lld %lld %lld", ptr5[i].expflat, ptr5[i].costflat, ptr5[i].expodn, ptr5[i].costodn);
        fprintf(outfile, "\n");
    }
    fclose(outfile);
    return 0;
}