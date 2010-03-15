#ifndef SOLUTIONPOOL_H
#define SOLUTIONPOOL_H

#include <QAbstractTableModel>
#include <QList>

namespace CCP{
class Solution;
}


class SolutionPool : public QAbstractTableModel
{
Q_OBJECT
    QList <CCP::Solution*> _solutions;

public:
    SolutionPool(const QList<CCP::Solution*> solutions, QObject *parent = 0):QAbstractTableModel(parent), _solutions(solutions)
    { }

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;


public slots:
    void newSolution(CCP::Solution * sol);

    void clear();
};

#endif // SOLUTIONPOOL_H
