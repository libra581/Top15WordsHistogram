/**********************************************************************
** FileManager - класс-интерфейс (посредник), реализующий функционал потока-обертки FileManager,
** используется для регистрации в QML и является посредником между C++(FileManager) и QML(UI).
**
** Дата создания: 15.03.2021
** Семенов Д.С.
**
** Версия: 1.0
** Среда разработки: Qt Creater 4.14.0
** Язык программирования: C++14 / Qt 5.15.2
**
** Основные переменные:
** m_mng_ptr - умный уникальный указатель типа FileManager.
**********************************************************************/
#ifndef FILEMANGERTHREAD_H
#define FILEMANGERTHREAD_H

#include <memory>
#include <thread>

#include <QObject>
#include <QThread>
#include <QVariantMap>

#include "FileManager.h"

class FileMangerThread : public QThread
{
    Q_OBJECT
private:
    std::unique_ptr<FileManager> m_mng_ptr;

public:
    FileMangerThread(QObject *parent = nullptr);

    Q_INVOKABLE void setFilePath(const QString &str);

    ~FileMangerThread();

signals:
    void progressChanged(float value);
    void dataMapChanged(QVariantMap map, int sum, int max);

protected:
    void run();
};

#endif // FILEMANGERTHREAD_H
