#include "abstractselection.h"

AbstractSelection::AbstractSelection(QIcon ico, const QString &name,
                                     QCursor cur, ToolGroup group,
                                     ToolType type, QWidget *parent)
    : Tool(ico, name, cur, group, type, parent)
{
    _scene = nullptr;
}
