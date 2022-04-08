/**
* \file Source.cpp
* \brief Реализация функции ввода данных из файла home.txt.
* \details Основная функция - ввод данных
* \author Белоконь Д.Д.
* \date Дата последней модификации - 10.01.2021
*/
#define _CRT_SECURE_NO_WARNINGS
#include "Source.h"
#include <iostream>
#include <assert.h>

/**
* \brief Вводит данные из фала home.txt.
*/
void vvodhome(home* p, long long int* n, long long int* sd)
{
	FILE* infh = fopen("home.txt", "r");
	assert((infh != NULL) && "Файл home.txt необнаружен");
	fscanf(infh, "%lld", n);
	fscanf(infh, "%lld", sd);
	for (int i = 0; i < *n; i++)
	{
		fscanf(infh, "%lld", &p[i].sn);
		fscanf(infh, "%lld", &p[i].pn);
	}
	fclose(infh);
}