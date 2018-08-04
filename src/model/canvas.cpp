#include "canvas.h"

Canvas::Canvas(const QString &name) :
    _docName(name)
{ }

Canvas::Canvas(QString docName,
               int width, int height,
               DimensionUnit dimensionUnit,
               int resolution,
               ResolutionUnit resUnit
               ) :
    _docName(docName),
    _width(width), _height(height),
    _dimensionUnit(dimensionUnit),
    _resolution(resolution),
    _resolutionUnit(resUnit)
{ }

Canvas::Canvas(const Canvas &other)
{
    _docName        = other.getName();
    _width          = other.getWidth();
    _height         = other.getHeight();
    _dimensionUnit  = other.getDimensionUnit();
    _resolution     = other.getResolution();
    _resolutionUnit = other.getResolutionUnit();
}

Canvas * Canvas::clone() const
{
    return new Canvas(*this);
}

QDataStream& operator << (QDataStream& ds, const Canvas &canvas)
{
    canvas.write(ds);
    return ds;
}

QDataStream& operator >> (QDataStream& ds, Canvas &canvas)
{
    canvas.read(ds);
    return ds;
}

void Canvas::write(QDataStream &out) const
{
    out << _width << _height << (int) _dimensionUnit << _resolution
        << (int) _resolutionUnit;
}

void Canvas::read(QDataStream &in)
{
    int width, height, dimensionUnit, resolution, resolutionUnit;

    in >> width >> height >> dimensionUnit >> resolution >> resolutionUnit;

    _width          = width;
    _height         = height;
    _dimensionUnit  = static_cast<DimensionUnit>(dimensionUnit);
    _resolution     = resolution;
    _resolutionUnit = static_cast<ResolutionUnit>(resolutionUnit);
}
