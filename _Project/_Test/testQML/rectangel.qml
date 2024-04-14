import QtQuick 2.0 //导入内建的qml类型
/*
矩形元素
*/


Item
{
    width: 500;
    height: 500;

    Rectangle {
        id: red_rectangle
        width:parent.width - 200
        height:parent.height - 200
        color: "red"
        border.color: "black"
        border.width: 5
        radius: 10 * 2  //支持表达式
    }
}

