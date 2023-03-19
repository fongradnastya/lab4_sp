/*!
 * \file struct.h
 * \brief Заголовочный файл с описанием структуры
 *
 * Данный файл содержит в себе определение основных
 * структур, используемых в программе.
*/

#ifndef WORK3_STRUCT_H
#define WORK3_STRUCT_H

/*!
 * \brief Страна
 */
typedef struct{
    char* name; /*!< Название страны */
    long population; /*!< Население страны */
    long area; /*!< Общая площадь страны */
}Country;

/*!
 * \brief Узел односвязного списка
 */
typedef struct Node{
    Country value; /*!< Значение узла */
    struct Node* next; /*!< Ссылка на следующий узел */
}Node;



#endif
