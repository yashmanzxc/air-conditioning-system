#ifndef MYSCENE_H
#define MYSCENE_H
/**
 * @file myscene.h
 * @brief Определение класса MyScene для управления графической сценой
 */

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
/**
 * @class MyScene
 * @brief Класс MyScene представляет собой пользовательскую графическую сцену с блоками
 */
class QGraphicsItem;
class MyScene : public QGraphicsScene
{
    Q_OBJECT

public:
    /**
     * @brief Конструктор класса MyScene
     */
    explicit MyScene(QWidget   *parent = nullptr);

    /**
     * @brief Обновляет цвет блоков в зависимости от состояния системы.
     * @param system Если true, блоки окрашиваются в зеленый, иначе в красный.
     */
    void updateBlock(bool system);

private:

    QGraphicsRectItem  *block1;///< Первый блок
    QGraphicsRectItem  *block2;///< Второй блок
    QGraphicsRectItem  *block3;///< Третий блок

};

#endif // MYSCENE_H
