/**
 * @file myscene.cpp
 * @brief Реализация методов класса MyScene
 */

#include "myscene.h"
#include <QBrush>
#include<QPen>
/**
 * @brief Конструктор MyScene cоздает три графических блока и добавляет их на сцену
 * @param parent Указатель на родительский виджет
 */
MyScene::MyScene(QWidget  *parent) : QGraphicsScene(parent)
{
    block1 = new QGraphicsRectItem(20,30,50,50);
    block2 = new QGraphicsRectItem(120,30,50,50);
    block3 = new QGraphicsRectItem(220,30,50,50);

    // Настраиваем цвет
        block1->setBrush(QBrush(Qt::red));
        block2->setBrush(QBrush(Qt::red));
        block3->setBrush(QBrush(Qt::red));

        // Добавляем блоки
            addItem(block1);
            addItem(block2);
            addItem(block3);

}
/**
 * @brief Метод updateBlock обновляет цвет всех блоков в зависимости от состояния системы
 * @param system если true то блоки окрашиваются в зеленый,а иначе в красный
 */
void MyScene::updateBlock(bool system)
{
    QColor color;
    if(system){
        color=Qt::green;
    }else{
        color=Qt::red;
    }
    block1->setBrush(QBrush(color));
    block2->setBrush(QBrush(color));
    block3->setBrush(QBrush(color));

}
