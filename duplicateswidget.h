#ifndef DUPLICATESWIDGET_H
#define DUPLICATESWIDGET_H

#include <QWidget>
#include <QTreeView>
#include <QStandardItemModel>
#include <QSharedPointer>
#include "duplicatesholder.h"
#include "duplicatesbuild_thread.h"
//#include "samesizeholder.h"

class SameSizeHolder;

class DuplicatesWidget : public QWidget
{
    Q_OBJECT
private:
    QTreeView*          p_tree_view_;
    QStandardItemModel  stubModel_;

    DuplicatesBuildThread*              thread_;
    QSharedPointer<QStandardItemModel>  spModel_;
    QSharedPointer<DuplicatesHolder>    spDupHolder_;
public:
    explicit DuplicatesWidget(QWidget *parent = 0);

public slots:
    void slot_generateDuplicatesHolder(QSharedPointer<SameSizeHolder> spSameSizeHolder);
    void slot_setStubModel(const QString& stubText);
    void slot_setWaitingMessage();
    void slot_setModel(QSharedPointer<DuplicatesHolder>);
};

#endif // DUPLICATESWIDGET_H
