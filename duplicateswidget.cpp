#include "duplicateswidget.h"
#include <QVBoxLayout>
#include <QDebug>

DuplicatesWidget::DuplicatesWidget(QWidget *parent) :
    QWidget(parent), stubModel_(1, 1)
{
    p_tree_view_            = new QTreeView;
    thread_                 = new  DuplicatesBuildThread(this);

    QVBoxLayout* vLayout    = new QVBoxLayout;
    vLayout->addWidget(p_tree_view_);
    setLayout(vLayout);

    slot_setStubModel(QString(tr("Choose a directory from the menu...")));

    connect (thread_, SIGNAL(DuplicatesHolderBuilt(QSharedPointer<DuplicatesHolder>)),
             this, SLOT(slot_setModel(QSharedPointer<DuplicatesHolder>))
             );
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
void DuplicatesWidget::slot_setModel(QSharedPointer<DuplicatesHolder> spDupHolder) {
    qDebug() << "<<<<<Generate Duplicate Model>>>>>>>";
     p_tree_view_->setSortingEnabled(false);

    QSharedPointer<QStandardItemModel>  spDupModel(
                new QStandardItemModel(spDupHolder->holder_.size(), 4)
                );
    auto iter = spDupHolder->holder_.cbegin();
    auto iterEnd = spDupHolder->holder_.cend();

    for ( quint32 counter = 0; iter != iterEnd; ++iter, ++counter ) {
        QModelIndex index = spDupModel->index(counter, 0);


        spDupModel->insertRows(0, iter.value().size(), index);
        spDupModel->insertColumns(0, 4, index);

        auto iterList    = iter.value().cbegin(); //
        auto iterListEnd = iter.value().cend();

        QModelIndex j0, j1, j2;
        for ( quint32 row = 0; iterList != iterListEnd; ++iterList, ++row ) {
            j0 = spDupModel->index(row, 1, index); // full path
            j1 = spDupModel->index(row, 2, index); // hash
            j2 = spDupModel->index(row, 3, index); // tag

            spDupModel->setData(j0, (*iterList)->fullName());
            spDupModel->setData(j1, iter.key());
            spDupModel->setData(j2, (*iterList)->tag());
        }
        spDupModel->setData(index, (*iter.value().cbegin())->size() );
    }

    spModel_ = spDupModel;
    spDupHolder_ = spDupHolder;

    //emit sameSizeHolderBuilt(spDupHolder_);

    spModel_->setHorizontalHeaderLabels(QStringList() << "Size" << "Absolute path" << "Md5 hash" << "Tag");
    p_tree_view_->setModel(spModel_.data());
    p_tree_view_->setSortingEnabled(true);
    p_tree_view_->sortByColumn(0, Qt::AscendingOrder);
}

