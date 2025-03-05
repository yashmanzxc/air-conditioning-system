#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "myscene.h"
#include "parametersdialog.h"
#include <QXmlStreamReader>
#include <QFile>
#include "usersettings.h"

class QFrame;
class QLabel;
class QComboBox;
class QVBoxLayout;
class QSlider;
class QPushButton;
class QGraphicsView;
/**
 * @brief Класс главного окна приложения
 * Этот класс управляет графическим интерфейсом пользователя включая отображение текущего состояния системы
 * настройку параметров и выбор темы оформления
 */
class Widget : public QWidget
{
    Q_OBJECT

public:
    /**
       * @brief Конструктор главного окна
       */
    Widget(QWidget *parent = nullptr);

    /**
       * @brief Создание вертикального компоновщика
       */
     QLayout* createVBoxLayout();


     /**
       * @brief Деструктор
       */
    ~Widget();

private slots:
     /**
        * @brief Обновляет отображаемое значение температуры при изменении шкалы
        */
    void updateTemperature(int index);

    /**
       * @brief Обновляет отображаемое значение давления при изменении шкалы
       */
    void updatePressure(int index);

    /**
       * @brief Обновляет значение влажности при изменении ползунка
       */
    void updateHumiditySlider(int value);

    /**
       * @brief Включает или выключает систему кондиционирования
       */
    void systemOnoff();

    /**
       * @brief Обновляет значение температуры при изменении ползунка
       */
    void updateTemperatureSlider(int value);

    /**
       * @brief Обновляет направление подачи воздуха
       */
    void updateairSupply(QString str);

    /**
       * @brief Открывает диалоговое окно для настройки параметров
       */
    void openParamDialog();

    /**
       * @brief Устанавливает параметры температуры, давления и влажности
       */
    void settingParam(double temper,double pres,double humid);

    /**
       * @brief Загружает пользовательские настройки из XML-файла
       */
    void loadUserSettings();

    /**
       * @brief Сохраняет пользовательские настройки в XML-файл
       */
    void saveUserSettings();

    /**
      * @brief Переключает между светлой и темной темой интерфейса
      */
    void themeWhiteBlack(QString str);

private:
    QFrame *frame;///< Фрейм для размещения элементов интерфейса

    QLabel *temperature;///< Метка для отображения температуры
    QLabel *humidity;///< Метка для отображения влажности
    QLabel *pressure;///< Метка для отображения давления
    QLabel *airSupply;///< Метка для отображения направления подачи воздуха

    QSlider *humiditySlider;///< Ползунок для настройки влажности
    QSlider *temperatureSlider;///< Ползунок для настройки температуры

    QPushButton *onOf;///< Кнопка включения и выключения системы
    QPushButton *setParam;///< Кнопка вызова окна настроек

    QComboBox *scaleSettings;///< Выпадающий список для выбора шкалы температуры
    QComboBox *pressureSettings;///< Выпадающий список для выбора шкалы давления
    QComboBox *airDirection;///< Выпадающий список для выбора направления подачи воздуха
    QComboBox *designStyle;///< Выпадающий список для выбора темы оформления

    QVBoxLayout *layout;///< Основной вертикальный компоновщик
    QVBoxLayout *vblayout;///< Дополнительный вертикальный компоновщик
    QVBoxLayout *vblayoutTwo;///< Дополнительный вертикальный компоновщик

    QGraphicsView *view;///< Виджет для отображения графической сцены
    MyScene *scene;///< Сцена отображающая текущее состояние системы


    double currentTemperature;///< Текущее значение температуры
    double currentPressure;///< Текущее значение давления

    bool isSystemOn = false;///< Флаг состояния системы включена/выключена
    bool isBlack = false;
};
#endif // WIDGET_H
