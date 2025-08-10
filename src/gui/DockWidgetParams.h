#ifndef DOCKWIDGETPARAMS_H
#define DOCKWIDGETPARAMS_H

#include <QDockWidget>

namespace Ui {
class DockWidgetParams;
}

class DockWidgetParams : public QDockWidget
{
    Q_OBJECT

public:
    explicit DockWidgetParams(QWidget *parent = nullptr);
    ~DockWidgetParams();

private:
    Ui::DockWidgetParams *ui;
};

#endif // DOCKWIDGETPARAMS_H
