/**********************************************************************
** FileManager - класс, реализующий функционал парсинга файла, обработку
** топ 15 слов и отсылку сигналов.
**
** Дата создания: 15.03.2021
** Семенов Д.С.
**
** Версия: 1.0
** Среда разработки: Qt Creater 4.14.0
** Язык программирования: C++14 / Qt 5.15.2
**
** Основные переменные:
** m_file_path - путь к файлу;
** m_file_ptr - умный уникальный указатель на рабочий файл;
** m_map - ассоциативный контейнер хранения всех слов из файла.
**
** Основные методы:
** readFile - чтение файла по строкам (readLine);
** counterWords - пословный просчет слов в строке;
** top15Words - определение топ 15 слов по количеству упорядоченные
** в алфавитном порядке.
**
** Основные сигналы:
** progressChanged - сигнал изменения коилчества слов (срабатывает,
** когда полностью проанализирована строка).
** dataMapChanged - сигнал изменения контейнера, высылает контейнер с топ15 словами,
** общую сумму для приведения к нормированным числам, а также максимальное число в контейнере.
**********************************************************************/
#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <memory>
#include <sstream>

#include <QObject>
#include <QString>
#include <QFile>
#include <QMap>
#include <QTextCodec>
#include <QVariantMap>

class FileManager : public QObject
{
    Q_OBJECT

private:
    QString m_file_path;
    std::unique_ptr<QFile> m_file_ptr;
    QMap<QString, QVariant> m_map;

public:
    FileManager(const QString &file_path = "data.txt", QObject *parent = nullptr);

    QString getFilePath() const;
    void setFilePath(const QString &str);

    void readFile(QMap<QString, QVariant> &map);
    QVariantMap readFile();

    void counterWords(const QString &str, QMap<QString, QVariant> &map);
    QVariantMap top15Words(QMap<QString, QVariant> &map);

    ~FileManager();

//Юнит-тесты
    void testCounterWords();
    void textReadFile();

signals:
    void progressChanged(float value);
    void dataMapChanged(QVariantMap map, int sum, int max);
};

#endif // FILEMANAGER_H
