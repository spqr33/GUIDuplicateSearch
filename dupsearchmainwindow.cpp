#include "dupsearchmainwindow.h"
#include <QHBoxLayout>
#include <QDebug>
#include <QMenu>
#include <QAction>
#include <QMenuBar>
#include <QSplitter>

DuplicateSearchMainWindow::DuplicateSearchMainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    p_container_ = new QWidget;
    p_left_widget_ = new LeftWidget;
    p_same_size_widget_ = new SameSizeWidget;
    p_dup_widget_ = new DuplicatesWidget;

    QSplitter* p_first_hor_splitter = new QSplitter(Qt::Horizontal);
    QSplitter* p_second_hor_splitter = new QSplitter(Qt::Horizontal);
    p_first_hor_splitter->addWidget(p_left_widget_);
    p_first_hor_splitter->addWidget(p_same_size_widget_);
    p_second_hor_splitter->addWidget(p_first_hor_splitter);
    p_second_hor_splitter->addWidget(p_dup_widget_);

    connect(p_left_widget_, SIGNAL(filesInfoHolderBuilded(QSharedPointer<FilesInfoHolder>)),
            p_same_size_widget_, SLOT(slot_generateSameSizeHolder(QSharedPointer<FilesInfoHolder>))
            );
    connect(p_same_size_widget_, SIGNAL(sameSizeHolderBuilt(QSharedPointer<SameSizeHolder>)),
            p_dup_widget_, SLOT(slot_generateDuplicatesHolder(QSharedPointer<SameSizeHolder>))
            );

    QHBoxLayout*    p_hbox_lay = new QHBoxLayout;

    //p_hbox_lay->addWidget(p_first_hor_splitter);
    p_hbox_lay->addWidget(p_second_hor_splitter);
    //p_hbox_lay->addWidget(p_same_size_widget_);
    //p_hbox_lay->addWidget(p_dup_widget_);

    p_container_->setLayout(p_hbox_lay);
    setCentralWidget(p_container_);

    generate_menu();
}

DuplicateSearchMainWindow::~DuplicateSearchMainWindow()
{

}

void DuplicateSearchMainWindow::generate_menu()
{
    QMenu *p_menu_file = new QMenu("&File");

    QAction *p_action_select_dir = new QAction("Select a directory", 0);
    p_action_select_dir->setText("Select dir...");
    p_action_select_dir->setStatusTip("Select a directory in which you want to find file duplicates.");

    connect(p_action_select_dir, SIGNAL(triggered(bool)), p_left_widget_, SLOT(slot_set_init_path()));
    p_menu_file->addAction(p_action_select_dir);
    connect(p_action_select_dir, SIGNAL(triggered(bool)), p_same_size_widget_, SLOT(slot_setWaitingMessage()));
    connect(p_action_select_dir, SIGNAL(triggered(bool)), p_dup_widget_, SLOT(slot_setWaitingMessage()));

    menuBar()->addMenu(p_menu_file);
}
