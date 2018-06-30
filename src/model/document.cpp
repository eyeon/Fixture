#include "document.h"

Document::Document(QString docName,
         double width,
         double height,
         DimensionUnit dimensionUnit,
         double resolution,
         ResolutionUnit resUnit
         )
{
    _docName = docName;
    _width = width;
    _height = height;
    _dimensionUnit = dimensionUnit;
    _resolution = resolution;
    _resolutionUnit = resUnit;
}

double Document::getHeight() const
{
    return _height;
}

double Document::getWidth() const
{
    return _width;
}

double Document::getResolution() const
{
    return _resolution;
}

QString Document::getName() const
{
    return _docName;
}

Document::DimensionUnit Document::getDimensionUnit() const
{
    return _dimensionUnit;
}

Document::ResolutionUnit Document::getResolutionUnit() const
{
    return _resolutionUnit;
}

