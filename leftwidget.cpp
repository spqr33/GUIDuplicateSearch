#include "leftwidget.h"
#include <QVBoxLayout>
#include <QSplitter>
#include <QFileSystemModel>
#include <QToolBox>
#include <QLabel>
#include <QDebug>
#include <QFileDialog>

LeftWidget::LeftWidget(QWidget *parent) : QWidget(parent)
{

    QToolBox*           p_tool_box = new QToolBox;
    p_fs_model_ = new QFileSystemModel(this);
    p_fs_view_  = new QTreeView;
    QVBoxLayout*        p_vbox_layout = new QVBoxLayout;
    QLabel*             p_label1 = new QLabel;
    QLabel*             p_label2 = new QLabel;

    p_tool_box->addItem(p_fs_view_, "Directory");
    p_label1->setText("Hello1_label");
    p_label2->setText("Hello2_label");
    p_tool_box->addItem(p_label1, "Stub_tab");
    p_tool_box->addItem(p_label2, "Stub_tab");

    p_vbox_layout->addWidget(p_tool_box);
    setLayout(p_vbox_layout);

    thread_ = new FileSystemTraverserThread(this);
}

void LeftWidget::slot_set_init_path()
{
    qDebug() << "LeftWidget::set_init_path()";

    QString dir_name = QFileDialog::getExistingDirectory();
    if (dir_name.isEmpty()) {
        return;
    }
    init_path_ = dir_name;

    p_fs_model_->setRootPath(init_path_);
    p_fs_view_->setModel(p_fs_model_);

    QModelIndex root_index = p_fs_model_->index(init_path_);
    p_fs_view_->setRootIndex(root_index);

    thread_->traverse(init_path_);

}
