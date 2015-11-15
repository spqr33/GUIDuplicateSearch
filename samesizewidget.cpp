#include "samesizewidget.h"
#include <QVBoxLayout>
#include <QModelIndex>
#include <QDebug>
//#include <QMap>
#include <QHash>
#include "samesizeholder.h"

SameSizeWidget::SameSizeWidget(QWidget* parrent) :
    QWidget(parrent), stubModel_(1, 1)
{
    p_view_                 = new QTreeView;
    QVBoxLayout* p_layout   = new QVBoxLayout;
    thread_ = new SameSizeHolderBuildThread(this);
    spFilesInfoHolder_.reset();

    setStubModel(QString(tr("Choose a directory from the menu...")));

    connect(thread_, SIGNAL(SameSizeHolderBuilt(QSharedPointer<SameSizeHolder>)),
            this, SLOT(slot_setModel(QSharedPointer<SameSizeHolder>)));

    p_layout->addWidget(p_view_);
    setLayout(p_layout);
}

void SameSizeWidget::setStubModel(const QString& text)
{
    QModelIndex index = stubModel_.index(0, 0);

    stubModel_.setHorizontalHeaderLabels(QStringList() << "");
    stubModel_.setData(index, text);
    p_view_->setModel(&stubModel_);
}

void SameSizeWidget::slot_generateSameSizeHolder(QSharedPointer<FilesInfoHolder> spFilesInfoHolder)
{
    setStubModel(QString(tr("Generating, please wait...")));
    thread_->build(spFilesInfoHolder);
}

void SameSizeWidget::slot_setModel(QSharedPointer<SameSizeHolder> spSameSizeHolder)
{
    QSharedPointer<QStandardItemModel>  spSameSizeModel(
                new QStandardItemModel(spSameSizeHolder->holder_.size(), 2)
                );
    auto iter = spSameSizeHolder->holder_.begin();
    auto iterEnd = spSameSizeHolder->holder_.end();

    for ( quint32 counter = 0; iter != iterEnd; ++iter, ++counter ) {
        QModelIndex index = spSameSizeModel->index(counter, 0);
        spSameSizeModel->setData(index, QString::number(iter.key()) + " Bytes");

        spSameSizeModel->insertRows(0, iter.value().size(), index);
        spSameSizeModel->insertColumns(0, 2, index);

        auto iterList    = iter.value().begin(); //
        auto iterListEnd = iter.value().end();

        for ( quint32 row = 0; iterList != iterListEnd; ++iterList, ++row ) {
            QModelIndex j0 = spSameSizeModel->index(row, 0, index);
            QModelIndex j1 = spSameSizeModel->index(row, 1, index);

            spSameSizeModel->setData(j0, (*iterList)->fullName());
            spSameSizeModel->setData(j1, (*iterList)->tag());
        }
    }

    spSameSizeModel_ = spSameSizeModel;
    spSameSizeHolder_ = spSameSizeHolder;

    spSameSizeModel_->setHorizontalHeaderLabels(QStringList() << "Absolute path" << "Tag");
    p_view_->setModel(spSameSizeModel_.data());
}
