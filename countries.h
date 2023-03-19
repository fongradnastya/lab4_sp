/*!
 * \file countries.h
 * \brief Заголовочный файл с описанием функций
 *
 * Данный файл содержит в себе определения основных
 * функций, работающих со странами
 */

#ifndef COUNTRIES_H
#define COUNTRIES_H
#include"struct.h"

/*!
* \brief Считывает информацию о стране от пользователя
* \return Созданная страна
*/
Country getCountry();

/*!
* \brief Создаёт новый элемент односвязного списка
* \param[in] country Созданная страна
* \return Созданный элемент списка
*/
Node* createNewNode(Country country);

/*!
* \brief Получает последний элемент списка
* \param[in] head Начальный элемент списка
* \return Последний элемент
*/
Node* getTail(Node* head);

/*!
* \brief Получает общее число стран
* \param[in] head Начальный элемент списка
* \return Общее число стран
*/
int getCountriesQuantity(Node* head);

/*!
* \brief Добавляет новую страну в список
* \param[in] head Начальный элемент списка
* \param[in] newNode Добавляемый элемент списка
*/
void appendCountry(Node** head, Node* newNode);

/*!
* \brief Удаляет элемент списка
* \param[in] head Ссылка на начальный элемент списка
*/
void deleteCountry(Node** head);

/*!
* \brief Выводит в консоль информацию о стране
* \param[in] country Выводимая страна
*/
void printCountry(Country country);

/*!
* \brief Выводит в консоль список всех стран
* \param[in] head Начальный элемент списка
*/
void printAllCountries(Node* head);

/*!
* \brief Ищет в списке страну по названию
* \param[in] head Начальный элемент списка
* \return Найденная страна
*/
Node* findCountry(Node* head);

/*!
* \brief Выводит в консоль меню изменения страны
*/
void printChangeMenu();

/*!
* \brief Изменяет данные о стране
* \param[in] head Ссылка на начальный элемент списка
*/
void changeCountry(Node** head);

/*!
* \brief Освобождает список стран
* \param[in] head Начальный элемент списка
*/
void freeCountries(Node* head);

/*!
* \brief Сортирует элементы списка по возрастанию
* \param[in] root Начальный элемент списка
* \return Новый начальный элемент
*/
Node* sort(Node* root);

/*!
* \brief Получает самые густонаселённые страны
* \param[in] head Начальный элемент списка
*/
void getHightPopulate(Node* head);

/*!
* \brief Получает упорядоченные страны с высоким населением
* \param[in] head Начальный элемент списка
*/
void getTheMostPopulous(Node* head);

#endif