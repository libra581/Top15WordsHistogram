/**********************************************************************
**
** Тестовое задание.
**
** Задача:
** Построить гистограмму на top-15(по количество вхождений) слов в выбранном
** файле произвольного размера.
** После выбора файла, должен быть виден прогресс обработки файла.
** Хорошим бонусом станет обновление гистограммы в условно реальном
** времени(без видимых продолжительных задержек).
** Топ 15 слов, должны быть, отсортированы по алфавиту.
** Подсчет слов и построение UI должны быть разделены минимум на два разных
** потока.
** Важно учитывать соразмерность столбцов гистограммы и возможность их
** вместить в видимой области окна приложения. В остальном, требований к
** визуальной части гистограммы нет(на усмотрение разработчика).
** Приложение должно быть реализовано на базе фреймворка Qt.
**
** Дата создания: 15.03.2021
** Семенов Д.С.
**
** Версия: 1.0
** Среда разработки: Qt Creater 4.14.0
** Язык программирования: C++14 / Qt 5.15.2
**
** Основные классы:
** FileManager - реализует функционал парсинга файла, обработку
** топ 15 слов и отсылку сигналов.
** FileManagerThread - реализует функционал потока-обертки FileManager,
** используется для регистрации в QML и является посредником между C++(FileManager) и QML(UI).
**
** Фукнция main() содержит регистрацию типа в контексте:
**      ~QQmlContext *context = engine.rootContext();
**      ~context->setContextProperty("controller", &contr_thread);
**  а также подключение файла main.qml.
**
**********************************************************************/

#include <memory>

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <thread>

#include "FileMangerThread.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);
    app.setOrganizationName("freelance");
    app.setOrganizationDomain("ru");

    FileMangerThread contr_thread;

    //QML front-end
    QQmlApplicationEngine engine;

    QQmlContext *context = engine.rootContext();
    context->setContextProperty("controller", &contr_thread);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    engine.load(url);


    return app.exec();
}
