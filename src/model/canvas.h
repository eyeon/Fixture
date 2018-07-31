#ifndef CANVAS_H
#define CANVAS_H

#include <QString>
#include <QSharedData>
#include <QDataStream>

class Canvas : public QSharedData
{
public:
    enum DimensionUnit {
        PIXELS, INCHES, CENTIMETERS, MILLIMETERS, POINTS, PICAS
    };

    enum ResolutionUnit{
        PPI, PPC
    };

    Canvas(QString docName,
             int width, int height,
             DimensionUnit dimensionUnit,
             int resolution,
             ResolutionUnit resUnit);
    Canvas(const Canvas&);
    Canvas();

    Canvas * clone() const;
    inline int getHeight() const { return _height; }
    inline int getWidth() const { return _width; }
    inline int getResolution() const { return _resolution; }
    inline QString getName() const {return _docName; }
    inline DimensionUnit getDimensionUnit() const { return _dimensionUnit; }
    inline ResolutionUnit getResolutionUnit() const { return _resolutionUnit; }

    void write(QDataStream&) const;
    void read(QDataStream&);
    friend QDataStream& operator>>(QDataStream& ds, Canvas &canvas);
    friend QDataStream& operator<<(QDataStream& ds, const Canvas &canvas);

private:
    QString _docName;
    int _width;
    int _height;
    DimensionUnit _dimensionUnit;
    int _resolution;
    ResolutionUnit _resolutionUnit;
};

#endif // CANVAS_H
