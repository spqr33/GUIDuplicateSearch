#ifndef DUPLICATESBUILDTHREAD_H
#define DUPLICATESBUILDTHREAD_H

#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QSharedPointer>
#include "samesizeholder.h"
#include "duplicatesholder.h"

//class SameSizeHolder;
class DuplicatesHolder;

class DuplicatesBuildThread : public QThread
{
    Q_OBJECT
private:
    bool abort_;
    bool restart_;
    QMutex mutex_;
    QWaitCondition waitCondition_;
    QSharedPointer<SameSizeHolder> spSameSize_;
public:
    DuplicatesBuildThread(QObject* parrent = 0);
    virtual ~DuplicatesBuildThread();
    void build(QSharedPointer<SameSizeHolder>);
protected:
    void run();// override;
signals:
    void DuplicatesHolderBuilt(QSharedPointer<DuplicatesHolder>);
};

#endif // DUPLICATESBUILDTHREAD_H
