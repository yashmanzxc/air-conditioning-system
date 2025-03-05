#include "usersettings.h"
#include <QFile>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QDebug>
#include <QString>
#include <QFileInfo>
/**
 * @brief Сохраняет значения температуры и давления в XML-файл
 * Файл создается в корневой директории под именем `settings.xml`
 * Если файл не удается открыть выводится сообщение об ошибке в консоль
 * @param temper значение температуры которое будет записано в файл
 * @param press значение давления которое будет записано в файл
 */
void UserSettings::saveS(const QString &temper, const QString &press)
{
    QFile file("settings.xml");
    if(!file.open(QIODevice::WriteOnly)){
        qDebug()<<"ERROR OPEN saveS "<< file.errorString();
    }

    QXmlStreamWriter wr(&file);
    wr.setAutoFormatting(true);

    wr.writeStartDocument();
    wr.writeStartElement("Settings");

    wr.writeTextElement("Temperature",temper);
    wr.writeTextElement("Pressure",press);

    wr.writeEndElement();
    wr.writeEndDocument();

    file.close();
}
/**
 * @brief Загружает значения температуры и давления из XML-файла по именем settings.xml
 * Если файл не найден или произошла ошибка чтения в консоль выводится сообщение об ошибке
 * @param temper Переменная для загрузки температуры
 * @param press Переменная для загрузки давления
 * @return true если загрузка прошла успешно иначе false
 */
bool UserSettings::loadS(QString &temper,  QString &press)
{

    QFile file("settings.xml");

    if(!file.open(QIODevice::ReadOnly)){
        qDebug()<<"ERROR OPEN loadS "<< file.errorString();;
        return false;
    }


    QXmlStreamReader sr(&file);
    while(!sr.atEnd()&& !sr.hasError()){
        sr.readNext();
        if(sr.isStartElement()){
            if(sr.name()=="Temperature"){
                temper = sr.readElementText();
            }else if(sr.name() == "Pressure"){
                press = sr.readElementText();
            }
        }
    }
    file.close();
    return !sr.hasError();


}
