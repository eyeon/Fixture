#include "document.h"

Document::Document(QString docName,
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


