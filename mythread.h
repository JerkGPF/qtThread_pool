#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>
#include <QThread>
#include <QVector>
#include <QRunnable>
class Generate : public QObject,public QRunnable
{
    Q_OBJECT
public:
    explicit Generate(QObject *parent = nullptr);

    void recvNum(int num);
    void run() override;
signals:
    void sendData(QVector<int> data);

private:
    int m_num;

};

class BubbleSort : public QObject,public QRunnable
{
    Q_OBJECT
public:
    explicit BubbleSort(QObject *parent = nullptr);

    void recvArray(QVector<int> data);
    void run() override;
signals:
    void finish(QVector<int> data);

private:
    QVector<int> m_data;

};

class QuickSort : public QObject,public QRunnable
{
    Q_OBJECT
public:
    explicit QuickSort(QObject *parent = nullptr);

    void recvArray(QVector<int> data);
    void run() override;
private:
    void quickSort(QVector<int> &data,int l,int r);
signals:
    void finish(QVector<int> data);

private:
    QVector<int> m_data;

};

#endif // MYTHREAD_H
