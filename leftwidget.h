#ifndef LEFTWIDGET_H
#define LEFTWIDGET_H

#include <QWidget>
#include <QTreeView>
//#include <QStandardItemModel>
#include <QFileSystemModel>

class LeftWidget : public QWidget
{
    Q_OBJECT
private:
    QString             init_path_;
    QTreeView*          p_fs_view_;
    QFileSystemModel*   p_fs_model_;
public:
    explicit LeftWidget(QWidget *parent = 0);

signals:
    void directory_loaded(const QString&);
public slots:
    void slot_set_init_path();
};

#endif // LEFTWIDGET_H
