import QtQuick 2.0

Item {

    Image{
        x:80
        width:  600
        height: 600
        source: "icon.png"
    }

    Image{
        x:190
        width:  600
        height: 600
        source: "icon.png"
        fillMode: Image.Tile
        opacity: 0.2 //透明度
        z:2 //堆叠顺序,越大越靠近用户
    }
}
