#include "canvas.h"

Canvas::Canvas(QString docName,
         int width, int height,
         DimensionUnit dimensionUnit,
         int resolution,
         ResolutionUnit resUnit
         ):
    _docName(docName),
    _width (width), _height (height),
    _dimensionUnit (dimensionUnit),
    _resolution (resolution),
    _resolutionUnit (resUnit)
{

}


Canvas::Canvas(const Canvas &other)
{
    _docName = other.getName();
    _width = other.getWidth();
    _height = other.getHeight();
    _dimensionUnit = other.getDimensionUnit();
    _resolution = other.getResolution();
    _resolutionUnit = other.getResolutionUnit();
}

Canvas* Canvas::clone() const
{
    return new Canvas(*this);
}
