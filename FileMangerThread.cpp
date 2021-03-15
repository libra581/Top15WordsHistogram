#include "FileMangerThread.h"

#include <QDebug>

FileMangerThread::FileMangerThread(QObject *parent /*= nullptr*/):
    QThread(parent)
{
    m_mng_ptr = std::make_unique<FileManager>("text.txt");
}

void FileMangerThread::setFilePath(const QString &str)
{
    m_mng_ptr->setFilePath(str);
}

FileMangerThread::~FileMangerThread()
{
    this->quit();
    this->wait();
}

void FileMangerThread::run()
{
    QObject::connect(&*m_mng_ptr, &FileManager::progressChanged, this, &FileMangerThread::progressChanged);
    //Qt::BlockingQueuedConnection - для замедления отображения
    QObject::connect(&*m_mng_ptr, &FileManager::dataMapChanged, this, &FileMangerThread::dataMapChanged);

    m_mng_ptr->readFile();
}

