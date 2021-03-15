import QtQuick 2.4

HistogramForm
{
    id: rootHistogram

    property var masRects: []
    readonly property int countRects: 15

    //Создание спрайта компонента отображения слова
    function createSpriteObjects(source, settings)
    {
        var component = Qt.createComponent(source);
        var sprite = component.createObject(rootHistogram, {idStatic: settings["idStatic"],
                                                y: 60 + settings["y"]});

        if (sprite === null)
            console.log("Error creating object");

        return sprite
    }

    //Создание 15 компонент слова
    function createHistogramsRects(mas, count)
    {
        var paddingRect = 25;
        for(var i = 0; i < count; ++i)
        {
            var sprite = createSpriteObjects("DynamicRect.qml", {idStatic: i, y: paddingRect*i})
            mas.push(sprite)
        }
    }

    Component.onCompleted:
    {
        createHistogramsRects(rootHistogram.masRects, countRects)
    }

    //!!!!Второй вариант ловли сигналов Filemaanger для обновления данных на гистограме!!!!!
    //Connections
    //{
    //    target: rootWindow
    //    function onMasMapChanged()
    //    {
    //        for(var i = 0; i < rootWindow.mapKeys.length; ++i)
    //        {
    //            rootHistogram.masRects[i].textElement.text = rootWindow.mapKeys[i]
    //            rootHistogram.masRects[i].rectFrontCount.width = rootWindow.mapValues[i]  / rootWindow.sum * 1000
    //        }

    //        //textElement1.text = rootWindow.mapKeys[0]
    //        //rectFrontCount.width =   rootWindow.mapValues[0]  / rootWindow.sum * 1000
    //    }
    //}
}
