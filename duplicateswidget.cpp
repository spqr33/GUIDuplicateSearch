#include "duplicateswidget.h"
#include <QVBoxLayout>

DuplicatesWidget::DuplicatesWidget(QWidget *parent) :
    QWidget(parent), stubModel_(1, 1)
{
    p_tree_view_            = new QTreeView;
    thread_                 = new  DuplicatesBuildThread(this);

    QVBoxLayout* vLayout    = new QVBoxLayout;
    vLayout->addWidget(p_tree_view_);
    setLayout(vLayout);

    slot_setStubModel(QString(tr("Choose a directory from the menu...")));
}

void DuplicatesWidget::slot_generateDuplicatesHolder(QSharedPointer<SameSizeHolder> spSameSizeHolder)
{
    slot_setStubModel(QString(tr("Generating, please wait...")));
    thread_->build(spSameSizeHolder);
}

void DuplicatesWidget::slot_setStubModel(const QString &stubText)
{
    QModelIndex index = stubModel_.index(0, 0);

    stubModel_.setHorizontalHeaderLabels(QStringList() << "Duplicates");
    stubModel_.setData(index, stubText);
    p_tree_view_->setModel(&stubModel_);
}

