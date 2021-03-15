#include <QDebug>
#include <QtGlobal>
#include <QUrl>
#include <QList>
#include <QPair>

#include "FileManager.h"

FileManager::FileManager(const QString &file_path /*= "data.txt"*/, QObject *parent /*= nullptr*/):
    QObject(parent)
{
    m_file_path = file_path;
    m_file_ptr = std::make_unique<QFile>(m_file_path, this);
}

QString FileManager::getFilePath() const
{
    return this->m_file_path;
}

void FileManager::setFilePath(const QString &str)
{
    Q_ASSERT_X(!str.isEmpty(), "FileManager", "getFilePath( str = null )");

    this->m_file_path = QUrl(str).toLocalFile();
    m_file_ptr = std::make_unique<QFile>(m_file_path, this);
}

void FileManager::readFile(QMap<QString, QVariant> &map)
{
    if(!m_file_ptr->open(QIODevice::ReadOnly | QIODevice::Text))
        throw std::runtime_error("Error file open");

    //Подсчет слов в каждой линии считывания
    QTextCodec *codec = QTextCodec::codecForName("CP1251");
    qint64 size_file = m_file_ptr->size();
    float precent{0.0};
    while(!m_file_ptr->atEnd())
    {
        QByteArray tmp_text(m_file_ptr->readLine());
        this->counterWords(codec->toUnicode(tmp_text), map);

        //Высылаем сигнал для отображения ProgressBar GUI
        if(size_file - m_file_ptr->bytesAvailable() != 0)
        {
            //Подсчет процентного соотношения: количество данных оставшихся для чтения в файле
            //от общего объема файла
            precent = (1.0 - ((1.0 * m_file_ptr->bytesAvailable()) /  size_file));
            emit progressChanged(precent);
            if(!map.isEmpty())
                top15Words(map);
        }
        else
        {
            emit progressChanged(0.0);
        }
    }

    m_file_ptr->close();
}

QVariantMap FileManager::readFile()
{
    this->readFile(m_map);
    return m_map;
}

void FileManager::counterWords(const QString &str, QMap<QString, QVariant> &map)
{
    std::stringstream str_stream(str.toStdString());
    std::string tmp_str;

    //Считывание по словам строки
    QString key_map = "";
    while(str_stream >> tmp_str)
    {
        key_map = QString::fromStdString(tmp_str).toLower();
        map[key_map] = map[key_map].toInt() + 1;
    }
}

QVariantMap FileManager::top15Words(QMap<QString, QVariant> &map)
{
    QMap<QString, QVariant> map_top_15;
    QVector<QPair<QVariant, QString>> pair_lst;

    //Разворачивание ключей и значений для сортировки
    for (auto k : map.keys())
    {
        pair_lst.append(QPair<QVariant, QString>(map[k], k));
    }

    std::sort(pair_lst.rbegin(), pair_lst.rend());

    //Разворачивание массива в Map и взятие топ 15 слов для отправки на GUI
    int max_top_words {15};
    int sum{0};

    //Если в Мапе меньше элементов чем топ 15
    if (pair_lst.length() < 15)
        max_top_words = pair_lst.length();

    for (int i = 0; i < max_top_words; ++i)
    {
        map_top_15[ pair_lst.at(i).second ] = pair_lst.at(i).first;
        sum += pair_lst.at(i).first.toInt();
    }

    emit dataMapChanged(map_top_15, sum, pair_lst.at(0).first.toInt());

    return map_top_15;
}

FileManager::~FileManager()
{

}

void FileManager::testCounterWords()
{
    QString str = "Лунный Мешкать Микрометр Перетянуться Подписать Провозной Расцвет Угорь Упрочить Ущипнуть";
    QMap<QString, QVariant> map;

    this->counterWords(str, map);

    QMapIterator<QString, QVariant> i(map);
    while (i.hasNext())
    {
        i.next();
        qDebug() << i.key() << ": " << i.value() << Qt::endl;
    }
}

void FileManager::textReadFile()
{
    QMap<QString, QVariant> map;

    this->readFile(map);

    QMapIterator<QString, QVariant> i(map);
    while (i.hasNext())
    {
        i.next();
        qDebug() << i.key() << ": " << i.value() << Qt::endl;
    }
}


