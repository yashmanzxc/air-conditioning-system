#ifndef USERSETTINGS_H
#define USERSETTINGS_H

#include <QString>
/**
 * @brief Класс для сохранения и загрузки пользовательских настроек
 * Класс позволяет сохранять и загружать настройки пользователя в XML-файл
 * так и из XML-файла
 */
class UserSettings
{
public:
    /**
       * @brief Сохраняет настройки в XML-файл
       * @param temper Значение температуры для сохранения
       * @param press Значение давления для сохранения
       */
   static void saveS(const QString &temper,const QString &press);
   /**
      * @brief Загружает настройки из XML-файла
      * @param temper переменная в которую будет загружено значение температуры
      * @param press переменная в которую будет загружено значение давления
      * @return Возвращает true если загрузка прошла успешно иначе false
      */
   static bool loadS(QString &temper,QString &press);
};

#endif // USERSETTINGS_H
