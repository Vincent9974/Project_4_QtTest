import QtQuick 2.0


//动画作为属性值的来源
//语法: 动画on属性

//1.动画作为属性值来源
//Rectangle {
//    width:  100
//    height: 100
//    color: "red"

//    PropertyAnimation on x{
//        to:50
//        duration: 1000
//        loops: Animation.Infinite
//    }

//    PropertyAnimation on y{
//        to:50
//        duration: 1000
//        loops: Animation.Infinite
//    }
//}

//2.行为动画, Behavior为一个属性值来指定默认的动画
//Item {
//    width:  100
//    height: 100

//    Rectangle{
//        id:green_rect
//        width: 100
//        height: 100
//        color: "green"

//        Behavior on x{PropertyAnimation{duration: 500}}
//        Behavior on y{PropertyAnimation{duration: 500}}
//    }

//    MouseArea{
//        anchors.fill: parent
//        onClicked: {
//            green_rect.x = mouse.x
//            green_rect.y = mouse.y
//        }
//    }
//}

//3.信号处理器中的动画
Rectangle{
    id:green_rect
    width: 100
    height: 100
    color: "green"

    MouseArea{
        anchors.fill: parent
        onClicked: PropertyAnimation{
            target: green_rect
            properties: "x, y"
            to:50
            duration: 2000
        }
    }
}

//4.独立动画(动画作为普通的QML对象来创建)



