#ifndef DUPLICATESEARCHMAINWINDOW_H
#define DUPLICATESEARCHMAINWINDOW_H

#include <QMainWindow>
#include "leftwidget.h"
#include "samesizewidget.h"
#include <QWidget>


class DuplicateSearchMainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QWidget*        p_container_;
    LeftWidget*     p_left_widget_;
    SameSizeWidget* p_same_size_widget_;

public:
    DuplicateSearchMainWindow(QWidget *parent = 0);
    ~DuplicateSearchMainWindow();

protected:
    void generate_menu();
};

#endif // DUPLICATESEARCHMAINWINDOW_H
