#ifndef SAMESIZEHOLDERBUILDTHREAD_H
#define SAMESIZEHOLDERBUILDTHREAD_H

#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QSharedPointer>
#include "filesinfoholder.h"
#include "samesizeholder.h"

class FilesInfoHolder;
class SameSizeHolder;

class SameSizeHolderBuildThread : public QThread
{
    Q_OBJECT
public:
    explicit SameSizeHolderBuildThread(QObject* parrent = 0);
    virtual ~SameSizeHolderBuildThread();

    void build(QSharedPointer<FilesInfoHolder> spFilesInfoHolder);

protected:
    void run();

signals:
    void SameSizeHolderBuilt(QSharedPointer<SameSizeHolder> spSameSizeHolder);
private:
    bool abort_;
    bool restart_;
    QMutex mutex_;
    QWaitCondition waitCondition_;
    QSharedPointer<FilesInfoHolder> spFilesInfoHolder_;
};

#endif // SAMESIZEHOLDERBUILDTHREAD_H
