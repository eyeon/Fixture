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
             double width,
             double height,
             DimensionUnit dimensionUnit,
             double resolution,
             ResolutionUnit resUnit);
    double getHeight() const;
    double getWidth() const;
    double getResolution() const;
    QString getName() const;
    DimensionUnit getDimensionUnit() const;
    ResolutionUnit getResolutionUnit() const;

private:
    double _width;
    double _height;
    DimensionUnit _dimensionUnit;
    double _resolution;
    ResolutionUnit _resolutionUnit;
    QString _docName;
};

#endif // DOCUMENT_H
