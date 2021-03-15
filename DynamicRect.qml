import QtQuick 2.4

//Кастомный элемент отображения столбца гистограммы
//Повторяется при генерации в предке 15 раз
DynamicRectForm
{
    //Уникальный айди для выборки из массива ключей и значений нужных элеменетов
    property int idStatic: 0

    rectFrontCount.color: Qt.rgba(Math.random(),Math.random(),Math.random(),1);

    Connections
    {
        target: rootWindow
        function onMasMapChanged()
        {
            //Если текущий айди меньше, чем есть элементов в мапе
            if(idStatic < rootWindow.mapKeys.length )
            {
                //то обновляем текст и ширину прямоугольника
                textElement.text = rootWindow.mapKeys[idStatic]

                var normValue = rootWindow.mapValues[idStatic] / rootWindow.maxCount
                rectFrontCount.anchors.rightMargin = rectBackground.width - normValue * rectBackground.width;
            }
        }
    }
}
