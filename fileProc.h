/*!
* \file fileProc.h
* \brief Заголовочный файл с описанием функций
* Данный файл содержит в себе определения основных
* функций, используемых для хранения стран в бинарном файле
*/

#ifndef FILE_PROC_H
#define FILE_PROC_H

/*!
* \brief Получает от пользователя популяцию страны
* \return популяция страны
*/
long inputPopulation();

/*!
* \brief Получает от пользователя площадь страны
* \return площадь страны
*/
long inputCountryArea();

/*!
* \brief Считывает информацию о стране из консоли
* \return созданная страна
*/
Country getCountry();

/*!
* \brief Выводит меню изменения записей
*/
void printChangeMenu();

/*!
* \brief Выводит в консоль информацию о стране
* \param[in] country страна для вывода
*/
void printCountry(Country country);

/*!
* \brief Получает от пользователя имя текстового или бинарного файла
* \return считанное имя файла
*/
char* inputFileName();

/*!
* \brief Добавляет в конец файла новую запись
*/
void addRecord();

/*!
* \brief Вычисляет количество записей в файле
* \param[in] fileName имя файла для проверки
* \return число записей в файле
*/
long countRecords(char* fileName);

/*! 
* \brief Получает от пользователя номер страны 
* \param[in] counter общее количество стран в файле
* \return считанный номер страны
*/
int inputCountryNumber(int counter);

/*!
* \brief Изменяет запись в файле
*/
void modifyRecord();

/*!
* \brief Удаляет запись из файла 
*/
void deleteRecord();

/*!
* \brief Считывает одну запись из файла
*/
void readRecord();

/*!
* \brief Считывает все записи из файла
*/
void readAllRecords();

/*!
* \brief Получает список самых густонаселённых стран
*/
void getTheMostPopulous();

/*!
* \brief Получает страны с заданным населением
*/
void getHighPopulate();

#endif