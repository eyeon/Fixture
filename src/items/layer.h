#ifndef LAYER_H
#define LAYER_H

#include <QString>
#include <QImage>
#include <QListWidgetItem>

enum class LayerType{
    RasterLayer,
    VectorLayer,
    TextLayer,
    AdjustmentLayer
};

class Layer
{
public:
    Layer(QString name, QImage &image,
          int x, int y,
          int height, int width);

    ~Layer();

    inline QImage getImage() { return _image; }
    inline QString getName() { return _name; }
    inline QListWidgetItem* getListItem() { return _item; }
    inline int getX() { return _x; }
    inline int getY() { return _y; }
    inline int getWidth() { return _width; }
    inline int getHeight() { return _height; }

    inline void setWidth(int width) {  _width = width; }
    inline void setHeight(int height) { _height = height; }
    void setScale(double factor);
    void setPos(int x, int y);

private:
    QString _name;
    QImage _image;
    int _x,_y,_width,_height;
    LayerType _type;
    QListWidgetItem *_item;
};

#endif // LAYER_H
