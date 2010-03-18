#ifndef SOLUTIONPOOL_H
#define SOLUTIONPOOL_H

#include <QAbstractTableModel>
#include <QList>

namespace CCP{
class Solution;
}

class SolutionItem{
public:
    SolutionItem(SolutionItem * parent, CCP::Solution * sol);
    ~SolutionItem();

    SolutionItem* child(int row);
    int childCount();

    void appendChild(SolutionItem* child);
    int row();

    QVariant data(int column);

    SolutionItem * parent();

    CCP::Solution * solution(){return _solution;}
    SolutionItem* findSolution(CCP::Solution * sol);
private:
    SolutionItem * _parent;
    CCP::Solution * _solution;
    QList <SolutionItem *> _childs;


};

class SolutionTreeModel: public QAbstractItemModel
{
    Q_OBJECT

public:
    SolutionTreeModel(QObject *parent = 0);
    ~SolutionTreeModel();

    QVariant data(const QModelIndex &index, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &index) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;

public slots:
    void newSolution(CCP::Solution * sol);

    void selectedItem(QModelIndex index);

    void clear();
signals:
    void selectedSolution(CCP::Solution * sol);

private:

    SolutionItem *rootItem;
};

//    : public QAbstractTableModel
//{
//Q_OBJECT
//    QList <CCP::Solution*> _solutions;
//
//public:
//    SolutionTreeModel(const QList<CCP::Solution*> solutions, QObject *parent = 0):QAbstractTableModel(parent), _solutions(solutions)
//    { }
//
//    int rowCount(const QModelIndex &parent = QModelIndex()) const;
//    int columnCount(const QModelIndex &parent = QModelIndex()) const;
//    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
//    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;


//};

#endif // SOLUTIONPOOL_H
