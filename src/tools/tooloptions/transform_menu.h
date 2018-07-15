#ifndef TRANSFORMOPTIONS_H
#define TRANSFORMOPTIONS_H

#include "toolmenu.h"

namespace Ui {
class TransformOptions;
}

class TransformMenu : public ToolMenu
{
    Q_OBJECT

public:
    explicit TransformMenu(QWidget *parent = 0);
    ~TransformMenu();

private:
    Ui::TransformOptions *ui;
};

#endif // TRANSFORMOPTIONS_H
