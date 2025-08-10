#include "DockWidgetParams.h"
#include "ui_DockWidgetParams.h"

DockWidgetParams::DockWidgetParams(QWidget *parent)
    : QDockWidget(parent)
    , ui(new Ui::DockWidgetParams)
{
    ui->setupUi(this);
}

DockWidgetParams::~DockWidgetParams()
{
    delete ui;
}
