#ifndef PARAMETERSDIALOG_H
#define PARAMETERSDIALOG_H

#include <QDialog>

class QLineEdit;
class QPushButton;
class QHBoxLayout;
class QLabel;

/**
 * @brief Класс диалогового окна для ввода параметров системы кондиционирования
 */
class ParametersDialog : public QDialog
{
    Q_OBJECT

public:
    /**
      * @brief Конструктор класса ParametersDialog
      */
    explicit ParametersDialog(QWidget *parent = nullptr);

    void diapogTheme(const QString &theme );

signals:
    /**
      * @brief Сигнал для передачи введенных параметров
      * @param temperature Температура в градусах Цельсия
      * @param pressure Давление в Паскалях
      * @param humidity Влажность в процентах
      */
    void enterParameters(double temperature,double pressure,double humidity);
private slots:
    /**
      * @brief Обработчик нажатия кнопки
      * Выполняет проверку введенных данных и отправляет их через сигнал enterParameters
      */
       void clickedOkCan();
public:
    QHBoxLayout *layout;///< Основной макет диалогового окна

    QLineEdit *paramTemperature;///< Поле ввода температуры
    QLineEdit *paramPressure;///< Поле ввода давления
    QLineEdit *paramHumidity;///< Поле ввода влажности

    QLabel *temperature;///< Метка для температуры
    QLabel *pressure;///< Метка для давления
    QLabel *humidity;///< Метка для влажности

    QPushButton * buttonOk;///< Кнопка подтверждения ввода
    QPushButton * buttonCancel;///< Кнопка отмены


};


#endif // PARAMETERSDIALOG_H
