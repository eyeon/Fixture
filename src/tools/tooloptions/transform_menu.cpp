#include "transform_menu.h"

TransformMenu::TransformMenu(QWidget *parent) :
    ToolMenu(parent)
{
    generateUI(parent);
    setLayout(_box);
    addStyleSheet();
    connectSignals();
}

TransformMenu::~TransformMenu()
{ }

void TransformMenu::generateUI(QWidget *parent)
{
    showTransformCheck = new QCheckBox(parent);
    autoSelectCheck    = new QCheckBox(parent);
    showTransformCheck->setText("Show Transform Controls");
    autoSelectCheck->setText("Auto Select");

    acceptBtn = new QPushButton(parent);
    acceptBtn->setIcon(QIcon(":/icons/check-tick.svg"));
    rejectBtn = new QPushButton(parent);
    rejectBtn->setIcon(QIcon(":/icons/close-white.svg"));
    _box = new QHBoxLayout(parent);
    acceptBtn->setVisible(false);
    rejectBtn->setVisible(false);
    _box->addWidget(autoSelectCheck);
    _box->addWidget(showTransformCheck);
    _box->addWidget(acceptBtn);
    _box->addWidget(rejectBtn);
}

void TransformMenu::connectSignals()
{
    connect(acceptBtn, SIGNAL(clicked()), this, SLOT(on_acceptBtn_clicked()));
    connect(rejectBtn, SIGNAL(clicked()), this, SLOT(on_rejectBtn_clicked()));
    connect(showTransformCheck, SIGNAL(stateChanged(int)), this,
            SLOT(on_showTransfromCheck_stateChanged(int)));
    connect(autoSelectCheck, SIGNAL(stateChanged(int)), this,
            SLOT(on_autoSelectCheck_stateChanged(int)));
}

void TransformMenu::on_showTransfromCheck_stateChanged(int arg1)
{
    emit showTransform(arg1 == Qt::Checked);
}

void TransformMenu::on_autoSelectCheck_stateChanged(int arg1)
{
    emit autoSelect(arg1 == Qt::Checked);
}

void TransformMenu::enterTransformMode(bool enter)
{
    acceptBtn->setVisible(enter);
    rejectBtn->setVisible(enter);
    showTransformCheck->setEnabled(!enter);
    autoSelectCheck->setEnabled(!enter);
}

void TransformMenu::on_acceptBtn_clicked()
{
    emit changesAccepted(true);
    emit autoSelect(autoSelectCheck->checkState() == Qt::Checked);
}

void TransformMenu::on_rejectBtn_clicked()
{
    emit changesAccepted(false);
    emit autoSelect(autoSelectCheck->checkState() == Qt::Checked);
}
