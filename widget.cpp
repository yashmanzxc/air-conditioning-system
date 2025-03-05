#include "widget.h"
#include "parametersdialog.h"
#include <QWidget>
#include <QFrame>
#include <QLabel>
#include <QComboBox>
#include <QVBoxLayout>
#include <QLayout>
#include <QSlider>
#include <QPushButton>
#include <QGraphicsView>
#include <QFile>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QString>
#include <QApplication>
#include <QIcon>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{

      // Установка параметров окна
      Qt::WindowFlags flags =Qt::Window;
      flags|= Qt::WindowMaximizeButtonHint;
      flags|= Qt::WindowCloseButtonHint;
      flags|= Qt::CustomizeWindowHint;
      setWindowFlags(flags);
    //Заголовок
    setWindowTitle (tr("Аir conditioning control"));

    QIcon icon("climat.png");
    setWindowIcon(icon);

    frame = new QFrame(this);
    frame->setFrameStyle(QFrame::Box|QFrame::Sunken);

    layout = new QVBoxLayout(this);

    //добавление горид во фрейм
    vblayout = new QVBoxLayout();
    vblayout->addLayout(createVBoxLayout());
    frame->setLayout(vblayout);

    // Выбор темы
    designStyle = new QComboBox();
    designStyle->addItem(tr("Theme: White"));
    designStyle->addItem(tr("Theme: Black"));
    designStyle->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Preferred);
    designStyle->setMinimumWidth(100);

    // Кнопки управления
    onOf = new QPushButton(tr("on/off"));
    setParam = new QPushButton(tr("Set Parameters"));

    // QGraphicsScene для отображения состояния системы
    scene = new MyScene(this);
    view = new QGraphicsView(scene,this);

    // Подключение сигналов и слотов
    connect(temperatureSlider,SIGNAL(valueChanged(int)),this,SLOT(updateTemperatureSlider(int)));
    connect(scaleSettings,SIGNAL(activated(int)),this,SLOT(updateTemperature(int)));
    connect(pressureSettings,SIGNAL(activated(int)),this,SLOT(updatePressure(int)));
    connect(humiditySlider,SIGNAL(valueChanged(int)),this,SLOT(updateHumiditySlider(int)));
    connect(onOf,SIGNAL(clicked(bool)),SLOT(systemOnoff()));
    connect(airDirection,SIGNAL(activated(QString)),this,SLOT(updateairSupply(QString)));
    connect(setParam,SIGNAL(clicked(bool)),this,SLOT(openParamDialog()));
    connect(scaleSettings,SIGNAL(currentIndexChanged(int)),this,SLOT(saveUserSettings()));
    connect(pressureSettings,SIGNAL(currentIndexChanged(int)),this,SLOT(saveUserSettings()));
    connect(designStyle,SIGNAL(activated(QString)),this,SLOT(themeWhiteBlack(QString)));

    //Начальное состояние системы
    onOf->setText(tr("On"));
    frame->setEnabled(false);
    //scene->updateBlock(false);

    // Добавление виджетов в нижнию вертикальную компоновку
    vblayoutTwo = new QVBoxLayout();
    vblayout->addWidget(view);
    vblayoutTwo->addWidget(onOf);
    vblayoutTwo->addWidget(setParam);
    vblayoutTwo->addWidget(designStyle);

    layout->addWidget(frame);//добавляют виджеты в компоновку
    layout->addLayout(vblayoutTwo);//установливает компоновки в виджите
    setLayout(layout);// присвоин виджет предка

    setMaximumSize(1024,768);
    setMinimumSize(800,600);

    loadUserSettings();
}

// Обновление значения температуры при изменении ползунка
void Widget::updateTemperatureSlider(int value){

    temperature->setText(tr("Temperature: %1°C").arg(value));
}

// Обновление температуры в зависимости от выбранной шкалы
void Widget::updateTemperature(int index){

            QString temperatureText;
            switch (index) {
                case 0://цельсий
                    temperatureText = QString("Temperature: %1°C").arg(currentTemperature);
                    break;
                case 1://фаренг
                    temperatureText = QString("Temperature: %1°F").arg(currentTemperature * 9/5 + 32);
                    break;
                case 2://кельвин
                    temperatureText = QString("Temperature: %1 K").arg(currentTemperature + 273.15);
                    break;
            }
            temperature->setText(temperatureText);

}
// Обновление давления в зависимости от выбранной шкалы
void Widget::updatePressure(int index){
            QString pressureText;
            switch (index) {
                case 0://Паскаль
                    pressureText = QString("Pressure: %1 Pa").arg(currentPressure);
                    break;
                case 1://миллиметры ртутного столба
                    pressureText = QString("Pressure: %1 mmHg").arg(currentPressure / 133.322);
                    break;
            }
            pressure->setText(pressureText);

}

// Обновление влажности при изменении ползунка
void Widget::updateHumiditySlider(int value){

    humidity->setText(tr("Humidity: %1 %").arg(value));
}

// Включение/выключение системы
void Widget::systemOnoff(){

    isSystemOn=!isSystemOn;

    if(isSystemOn){

        frame->setEnabled(true);
        onOf->setText(tr("Off"));
        scene->updateBlock(true);

    }else{
        frame->setEnabled(false);
        onOf->setText(tr("On"));
        scene->updateBlock(false);
      }

    }

// Обновление направления подачи воздуха
void Widget::updateairSupply(QString str){
    airSupply->setText(tr("Air supply: %1").arg(str));
}

// Открытие диалогового окна для параметров
void Widget::openParamDialog()
{
    ParametersDialog dialog(this);
    connect(&dialog, &ParametersDialog::enterParameters, this, &Widget::settingParam);
    //isBlack?"Theme Black":"Theme White"
    QString curentTheme;

    if(isBlack){
        curentTheme = "Theme Black";
    }else{
        curentTheme = "Theme White";
    }

    dialog.diapogTheme(curentTheme);
    dialog.exec();

}

// Установка параметров температуры, давления и влажности
void Widget::settingParam(double temper,double pres,double humid)
{

        currentTemperature = temper;
        currentPressure = pres;
        temperatureSlider->setValue(temper);
        humiditySlider->setValue(humid);

        updateTemperature(scaleSettings->currentIndex());
        updatePressure(pressureSettings->currentIndex());
}

// Загрузка пользовательских настроек
void Widget::loadUserSettings()
{
    QString temper,press;

    if(UserSettings::loadS(temper,press)){
        scaleSettings->setCurrentText(temper);
        pressureSettings->setCurrentText(press);
    }
}

// Сохранение пользовательских настроек
void Widget::saveUserSettings()
{
    UserSettings::saveS(scaleSettings->currentText(),pressureSettings->currentText());
}

// Переключение темы оформления
void Widget::themeWhiteBlack(QString str)
{
    QPalette pal;

    // Сбрасываем  стили перед сменой темы
        onOf->setStyleSheet("");
        setParam->setStyleSheet("");
        scaleSettings->setStyleSheet("");
        pressureSettings->setStyleSheet("");
        airDirection->setStyleSheet("");
        designStyle->setStyleSheet("");
        humiditySlider->setStyleSheet("");
        temperatureSlider->setStyleSheet("");

    if(str =="Theme: White"){
        pal = QApplication::style()->standardPalette();
        isBlack = false;
    }else if(str =="Theme: Black"){

        pal.setColor(QPalette::Window, QColor(53, 53, 53));
        pal.setColor(QPalette::WindowText, Qt::green);
        pal.setColor(QPalette::Button, QColor(53, 53, 53));
        pal.setColor(QPalette::ButtonText, Qt::green);

        QString button = "QPushButton { background-color: #333; color: green; border: 1px solid #555; }"
                                      "QPushButton:hover { background-color: #444; }"
                                      "QPushButton:pressed { background-color: #222; }";

        QString combo = "QComboBox { background-color: #333; color: green; border: 1px solid #555; }"
                                      "QComboBox::drop-down { border: none; }"
                                      "QComboBox QAbstractItemView { background-color: #222; color: green; border: 1px solid #555; }";

        humiditySlider->setStyleSheet(R"(
                QSlider::groove:horizontal {
                    background: green;
                    height: 6px;
                }
                QSlider::handle:horizontal {
                    background: blue;
                    width: 9px;
                    margin: -6px 0;
                })");
        temperatureSlider->setStyleSheet(R"(
               QSlider::groove:horizontal {
                   background: green;
                   height: 6px;
               }
               QSlider::handle:horizontal {
                   background: blue;
                   width: 9px;
                   margin: -6px 0;

               })");


         onOf->setStyleSheet(button);
         setParam->setStyleSheet(button);
         scaleSettings->setStyleSheet(combo);
         pressureSettings->setStyleSheet(combo);
         airDirection->setStyleSheet(combo);
         designStyle->setStyleSheet(combo);
        isBlack = true;
    }

    QApplication::setPalette(pal);

}


// Создание вертикального компоновщика
QLayout* Widget::createVBoxLayout(){

    temperature = new QLabel(tr("Temperature: °C"));


    humidity = new QLabel(tr("Humidity: %"));

    scaleSettings = new QComboBox();
    scaleSettings->addItem(tr("Celsius"));
    scaleSettings->addItem(tr("Fahrenheit"));
    scaleSettings->addItem(tr("Kelvin"));
    scaleSettings->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Preferred);
    scaleSettings->setMinimumWidth(70);

    pressure = new QLabel(tr("Pressure: Pa"));


    pressureSettings = new QComboBox();
    pressureSettings->addItem(tr("Pascals"));
    pressureSettings->addItem(tr("mmHg"));
    pressureSettings->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Preferred);
    pressureSettings->setMinimumWidth(70);



    humiditySlider = new QSlider(Qt::Horizontal);
    humiditySlider->setRange(0,60);


    temperatureSlider = new QSlider(Qt::Horizontal);
    temperatureSlider->setRange(-50,50);


    airSupply = new QLabel(tr("Air supply: "));


    airDirection = new QComboBox();
    airDirection->addItem(tr("Up"));
    airDirection->addItem(tr("Down"));
    airDirection->addItem(tr("Left"));
    airDirection->addItem(tr("Right"));
    airDirection->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Preferred);
    airDirection->setMinimumWidth(70);

    QVBoxLayout *l = new QVBoxLayout(); //горизонт

    l->addWidget(temperature);
    l->addWidget(humidity);
    l->addWidget(pressure);
    l->addWidget(scaleSettings);
    l->addWidget(pressureSettings);
    l->addWidget(humiditySlider);
    l->addWidget(temperatureSlider);
    l->addWidget(airSupply);
    l->addWidget(airDirection);

    return l;


}

Widget::~Widget()
{
}

