#include "SolutionPool.h"
#include <Solution.h>

using namespace CCP;

SolutionItem::SolutionItem(SolutionItem *parent, CCP::Solution *sol){
    _parent = parent;
    _solution = sol;
}

SolutionItem::~SolutionItem(){
    qDeleteAll(_childs);
}

int SolutionItem::row(){
    if (_parent){
        return _parent->_childs.indexOf(const_cast<SolutionItem*> (this));
    }
    return 0;
}

int SolutionItem::childCount(){
    return _childs.count();
}

SolutionItem * SolutionItem::child(int row){
    return _childs.value(row);
}

void SolutionItem::appendChild(SolutionItem *child){
    _childs.append(child);
}

QVariant SolutionItem::data(int column){
    if (_solution){
        switch (column){
        case 0: return QVariant(_solution->algorithmName());
        case 1: return QVariant(_solution->getValue());
        }
    }
    return QVariant();
}

SolutionItem * SolutionItem::parent(){
    return _parent;
}

SolutionItem * SolutionItem::findSolution(Solution * sol){
    if (_solution == sol){
        return this;
    }
    foreach (SolutionItem * item, _childs){
        SolutionItem * finded = item->findSolution(sol);
        if (finded != 0){
            return finded;
        }
    }
    return 0;
}



SolutionTreeModel::SolutionTreeModel(QObject *parent):QAbstractItemModel(parent){
    rootItem = new SolutionItem(0, 0);
}

SolutionTreeModel::~SolutionTreeModel(){

}

QVariant SolutionTreeModel::data(const QModelIndex &index, int role) const{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    SolutionItem *item = static_cast<SolutionItem*>(index.internalPointer());

    return item->data(index.column());

}
Qt::ItemFlags SolutionTreeModel::flags(const QModelIndex &index) const{
    if (!index.isValid())
        return 0;

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}
QVariant SolutionTreeModel::headerData(int section, Qt::Orientation orientation,int role) const{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole){
        switch (section){
        case 0: return QVariant(tr("Algorithm"));
        case 1: return QVariant(tr("Value"));
        }

    }
    return QVariant();
}
QModelIndex SolutionTreeModel::index(int row, int column,const QModelIndex &parent) const{
    if (!hasIndex(row, column, parent)){
        return QModelIndex();
    }

    SolutionItem *parentItem;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<SolutionItem*>(parent.internalPointer());

    SolutionItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}
QModelIndex SolutionTreeModel::parent(const QModelIndex &index) const{
    if (!index.isValid())
        return QModelIndex();

    SolutionItem *childItem = static_cast<SolutionItem*>(index.internalPointer());
    SolutionItem *parentItem = childItem->parent();

    if (parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}
int SolutionTreeModel::rowCount(const QModelIndex &parent) const{
    SolutionItem * parentItem;
    if (parent.column() > 0){
        return 0;
    }

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<SolutionItem*>(parent.internalPointer());

    return parentItem->childCount();

}
int SolutionTreeModel::columnCount(const QModelIndex &parent) const{
    return 2;
}

void SolutionTreeModel::newSolution(CCP::Solution * sol){
    SolutionItem * item = 0;
    if ( sol == 0)
        return;
    if (sol->isImprovement()){
        SolutionItem *parentItem = rootItem->findSolution(sol->solutionParent());
        if (parentItem){
            item = new SolutionItem(parentItem, sol);
            parentItem->appendChild(item);
            beginInsertRows( QModelIndex(), item->row(), item->row());
            endInsertRows();
            return;
        }
    }else{
        item = new SolutionItem(rootItem, sol);
        rootItem->appendChild(item);
        beginInsertRows( QModelIndex (), item->row(), item->row());
        endInsertRows();
    }



}

void SolutionTreeModel::clear(){
    beginRemoveRows(QModelIndex(),0,rowCount()-1);
    emit selectedSolution(0);
    delete rootItem;
    rootItem = new SolutionItem(0, 0);
    endRemoveRows();

}

void SolutionTreeModel::selectedItem(QModelIndex index){
    SolutionItem * item = static_cast<SolutionItem*>(index.internalPointer());
    emit selectedSolution(item->solution());
}

//int SolutionTreeModel::rowCount(const QModelIndex &/*parent*/) const
//{
//    return _solutions.count();
//}
//
//int SolutionTreeModel::columnCount(const QModelIndex &parent) const{
//    return 2; //Algorithm and value
//}
//
//
//QVariant SolutionTreeModel::data(const QModelIndex &index, int role) const
//{
//    if (!index.isValid()){
//        return QVariant();
//    }
//    if (index.row() >= _solutions.count()){
//        return QVariant();
//    }
//    if (role == Qt::DisplayRole){
//        CCP::Solution *sol = _solutions.at(index.row());
//        if (index.column() == 0){
//            return sol->algorithmName();
//        }else{
//            if (index.column() == 1){
//                return sol->getValue();
//            }else{
//                return QVariant();
//            }
//        }
//    }
//    return QVariant();
//}
//
//QVariant SolutionTreeModel::headerData(int section, Qt::Orientation orientation, int role) const{
//    if(role == Qt::DisplayRole ){
//        if (orientation == Qt::Horizontal){
//            switch(section){
//            case 0: return QString ("Algorithm");
//            case 1: return QString ("Value");
//            }
//        }
//    }
//    return QVariant();
//}
//
//
//
//void SolutionTreeModel::newSolution(Solution* sol){
//    if (sol == 0){
//        return;
//    }
//    beginInsertRows(QModelIndex(), rowCount()-1, rowCount()-1);
//    _solutions.append(sol);
//    endInsertRows();
//
//}
//
//void SolutionTreeModel::clear(){
//    beginRemoveRows(QModelIndex(),0, rowCount() - 1);
//    foreach(Solution * sol, _solutions){
//        delete sol;
//    }
//    _solutions.clear();
//    endRemoveRows();
//
//}
