/**
* \file Source2.cpp
* \brief Реализация функции ввода данных из файла taxes.txt.
* \details Основная функция - ввод данных
* \author Белоконь Д.Д.
* \date Дата последней модификации - 10.01.2021
*/
#define _CRT_SECURE_NO_WARNINGS
#include "Source2.h"
#include <iostream>
#include <assert.h>

/**
* \brief Вводит данные из фала taxes.txt.
*/
void vvodtaxes(taxes* p, long long* n)
{
	FILE* inft = fopen("taxes.txt", "r");
	assert((inft != NULL) && "Файл taxes.txt необнаружен");
	fscanf(inft, "%lld", n);
	for (int i = 0; i < *n; i++)
	{
		fscanf(inft, "%s", &p[i].rq);
		fscanf(inft, "%lld", &p[i].p);
		fscanf(inft, "%lld", &p[i].kq);
	}
	fclose(inft);
}