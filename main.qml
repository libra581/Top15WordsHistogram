import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Dialogs 1.2

Window {
    id: rootWindow
    width: 640
    height: 480
    visible: true
    title: qsTr("Histogram Words")

    property var mapWords: (new Map())
    property var mapKeys: []
    property var mapValues: []
    property int sum: 0         //Сумма всех повторений в топ15 словах
    property int maxCount: 1    //Максимальное подсчитанное коилчество слова в мапе

    signal masMapChanged()

    //Элемент работы с диалоговым окном выбора файла
    FileDialog
    {
        id: fileDialog
        title: "Please choose a file"
        onAccepted:
        {
            controller.setFilePath(fileDialog.fileUrls[0])
            controller.start();
        }
        onRejected:
        {
            console.log("Canceled")
        }

        Component.onCompleted: visible = true
    }

    //Кастомный элемент гистограммного отображения топ15 слов
    Histogram
    {
        id: histogram
        anchors.fill: parent

        Connections
        {
            target: controller

            //Захват значения от FileManager для отображения прогресс бара
            function onProgressChanged(value)
            {
               histogram.valueProgressBar = value
            }

            //Захват значения от FileManager для отображения гистограм
            function onDataMapChanged(map, sum, max)
            {
                rootWindow.mapWords = map
                rootWindow.sum = sum
                rootWindow.maxCount = max

                rootWindow.mapKeys = []
                rootWindow.mapValues = []

                //Разбивка объекта на массивы: ключи и значения
                for (var prop in mapWords)
                {
                    rootWindow.mapKeys.push(prop)
                    rootWindow.mapValues.push(mapWords[prop])
                }

                rootWindow.masMapChanged();
            }
        }
    }
}
