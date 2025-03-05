#include "parametersdialog.h"
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QPalette>
#include <QApplication>
/**
 * @brief Конструктор диалогового окна параметров
 * Инициализирует поля ввода, кнопки и макет
 * @param parent Родительский виджет
 */
ParametersDialog::ParametersDialog(QWidget *parent) : QDialog(parent)
{
    // Заголовок
    setWindowTitle (tr("Аir conditioning control"));
    // Создание полей ввода
    paramTemperature = new QLineEdit();
    paramPressure = new QLineEdit();
    paramHumidity = new QLineEdit();

    // Создание меток
    temperature = new QLabel(tr("Temperature (°C):"));
    pressure = new QLabel(tr("Pressure (Pa)"));
    humidity = new QLabel(tr("Humidity (%)"));

     // Связываем метки с полями ввода
     temperature->setBuddy(paramTemperature);
     pressure->setBuddy(paramPressure);
     humidity->setBuddy(paramHumidity);

     //Кнопоки
     buttonOk =new QPushButton(tr("Ok"));
     buttonCancel = new QPushButton(tr("Cancel"));

     // Создание макета
     layout = new QHBoxLayout(this);
     layout->addWidget(temperature);
     layout->addWidget(paramTemperature);
     layout->addWidget(pressure);
     layout->addWidget(paramPressure);
     layout->addWidget(humidity);
     layout->addWidget(paramHumidity);

     layout->addWidget(buttonOk);
     layout->addWidget(buttonCancel);

     setLayout(layout);

    // Подключение
     connect(buttonOk,SIGNAL(clicked(bool)),this,SLOT(clickedOkCan()));
     connect(buttonCancel,SIGNAL(clicked(bool)),this,SLOT(reject()));



}

void ParametersDialog::diapogTheme(const QString &theme)
{


    if(theme=="Theme Black"){

        buttonOk->setStyleSheet("QPushButton{background-color: #353535; color: green; border-radius 5px;padding 5px 10px;}");

        buttonCancel->setStyleSheet("QPushButton{background-color: #353535; color: green;border-radius 5px;padding 5px 10px;}");
    }else{

        buttonOk->setStyleSheet("QPushButton{background-color: #f0f0f0; color: black; border-radius 5px;padding 5px 10px;}");

        buttonCancel->setStyleSheet("QPushButton{background-color: #f0f0f0; color: black; border-radius 5px;padding 5px 10px;}");
    }



}
/**
 * @brief Проверяет корректность введенных данных и отправляет сигнал
 * Если введенные данные корректны, сигнал enterParameters передает значения температуры,
 * давления и влажности в противном случае окно остается открытым для исправления данных
 */
void ParametersDialog::clickedOkCan()
{
    bool Temp, Press, Hum;
    double temp = paramTemperature->text().toDouble(&Temp);
    double press = paramPressure->text().toDouble(&Press);
    double hum = paramHumidity->text().toDouble(&Hum);

     //Проверка корректности
    if (Temp && Press && Hum)
    {
        emit enterParameters(temp, press, hum);
        accept();
    }
}


