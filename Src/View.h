#ifndef VIEW_H
#define VIEW_H

#include <QDialog>

#include "ViewModel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class View; }
QT_END_NAMESPACE

class View : public QDialog
{
    Q_OBJECT

public:
    View(QWidget *parent = nullptr);
    ~View();

signals:
    void imageFolderChanged(QString folder);

private:
    Ui::View* m_ui;
    ViewModel m_viewmodel;
};
#endif // VIEW_H
