#ifndef SAMESIZEWIDGET_H
#define SAMESIZEWIDGET_H
#include <QTreeView>
#include <QSharedPointer>
#include "filesinfoholder.h"
#include <QStandardItemModel>
#include "samesizeholderbuild_thread.h"
#include <QWidget>

class FilesInfoHolder;
class SameSizeHolderBuildThread;
class SameSizeHolder;

class SameSizeWidget : public QWidget
{
    Q_OBJECT
private:
    QTreeView*  p_view_;
    QSharedPointer<FilesInfoHolder> spFilesInfoHolder_;
    SameSizeHolderBuildThread* thread_;

    QStandardItemModel stubModel_;

    QSharedPointer<QStandardItemModel>  spSameSizeModel_;
    QSharedPointer<SameSizeHolder>      spSameSizeHolder_;
public:
    SameSizeWidget(QWidget* parrent = 0);
signals:
    void sameSizeHolderBuilt(QSharedPointer<SameSizeHolder>);
public slots:
    void setStubModel(const QString& text);
    void slot_setWaitingMessage();
    void slot_generateSameSizeHolder(QSharedPointer<FilesInfoHolder> spFilesInfoHolder);
    void slot_setModel(QSharedPointer<SameSizeHolder>);
};

#endif // SAMESIZEWIDGET_H
