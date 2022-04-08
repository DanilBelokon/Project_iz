/**
* \file Source.h
* \brief Реализация функции ввода данных из файла taxes.txt.
* \details Основная функция - ввод данных
* \author Белоконь Д.Д.
* \date Дата последней модификации - 10.01.2021
*/
#pragma once

/**
* \struct home
* \brief Структура для хранения данных из файла home.txt.
* \details Очень важная структура - подробное описание
*/
typedef struct
{
	long long int sn; ///< Поле структуры - площадь определенной квартиры
	long long int pn; ///< Поле структуры - количество жильцов в определенной квартире
}home;

/**
* \brief Вводит данные из фала home.txt.
* \param p - массив структур home* p
* \param n - колличество квартир в доме
* \param sd - общая площадь всех (жилых и нежилых) помещений в доме 
*/
void vvodhome(home* p, long long int* n, long long int* sd);