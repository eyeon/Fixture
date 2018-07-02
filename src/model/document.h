#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <QString>

class Document
{
public:
    enum DimensionUnit
    {
        PIXELS, INCHES, CENTIMETERS
    };
    enum ResolutionUnit
    {
        PPI, DPI
    };

    Document(QString docName,
             int width,
             int height,
             DimensionUnit dimensionUnit,
             int resolution,
             ResolutionUnit resUnit);

    inline int getHeight() const { return _height; }
    inline int getWidth() const { return _width; }
    inline int getResolution() const { return _resolution; }
    inline QString getName() const {return _docName; }
    inline DimensionUnit getDimensionUnit() const { return _dimensionUnit; }
    inline ResolutionUnit getResolutionUnit() const { return _resolutionUnit; }

private:
    QString _docName;
    int _width;
    int _height;
    DimensionUnit _dimensionUnit;
    int _resolution;
    ResolutionUnit _resolutionUnit;
};

#endif // DOCUMENT_H
