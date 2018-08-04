#ifndef DOCUMENT_H
#define DOCUMENT_H

#include "../layers/layer.h"
#include "canvas.h"

class Document
{
public:
    Document(const QList<Layer *>         layers,
         const QSharedDataPointer<Canvas> canvas);
    Document(const QString &name);
    void write(QDataStream&) const;
    void read(QDataStream&);
    friend QDataStream& operator >> (QDataStream& ds, Document& document);
    friend QDataStream& operator << (QDataStream& ds, const Document &document);
    static bool isDocumentValid(const QString &fileName);
    inline QList<Layer *> getLayerList(){ return _layers; }
    inline QSharedDataPointer<Canvas> getCanvas(){ return _canvas; }

private:
    QList<Layer *> _layers;
    QSharedDataPointer<Canvas> _canvas;

    qint64 _magicNum = 0x798F138BA; // Hex value of multiplication of the two authors' dob
    qint32 _version  = 1;
    QString _name;
};

#endif // DOCUMENT_H
