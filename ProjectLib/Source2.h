/**
* \file Source2.h
* \brief Реализация функции ввода данных из файла taxes.txt.
* \details Основная функция - ввод данных
* \author Белоконь Д.Д.
* \date Дата последней модификации - 10.01.2021
*/

#pragma once

/**
* \struct taxes
* \brief Структура для хранения данных из файла taxes.txt.
* \details Очень важная структура - подробное описание
*/
typedef struct
{
	char rq[6]; ///< Поле структуры - наименование ресурса из файла taxes.txt
	long long int p; ///< Поле структуры - тариф оплаты за единицу расхода данного ресурса из файла taxes.txt
	long long int kq; ///< Поле структуры - зарезервированное значение из файла taxes.txt.
}taxes;

/**
* \brief Вводит данные из фала taxes.txt.
* \param p - массив структур taxes* p
* \param n - колличество ресурсов, которое потребляют жильцы дома
*/
void vvodtaxes(taxes* p, long long* n);