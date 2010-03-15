#include "SolutionPool.h"
#include <Solution.h>

using namespace CCP;


int SolutionPool::rowCount(const QModelIndex &/*parent*/) const
{
    return _solutions.count();
}

int SolutionPool::columnCount(const QModelIndex &parent) const{
    return 2; //Algorithm and value
}


QVariant SolutionPool::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()){
        return QVariant();
    }
    if (index.row() >= _solutions.count()){
        return QVariant();
    }
    if (role == Qt::DisplayRole){
        CCP::Solution *sol = _solutions.at(index.row());
        if (index.column() == 0){
            return sol->algorithmName();
        }else{
            if (index.column() == 1){
                return sol->getValue();
            }else{
                return QVariant();
            }
        }
    }
    return QVariant();
}

QVariant SolutionPool::headerData(int section, Qt::Orientation orientation, int role) const{
    if(role == Qt::DisplayRole ){
        if (orientation == Qt::Horizontal){
            switch(section){
            case 0: return QString ("Algorithm");
            case 1: return QString ("Value");
            }
        }
    }
    return QVariant();
}



void SolutionPool::newSolution(Solution* sol){
    if (sol == 0){
        return;
    }
    beginInsertRows(QModelIndex(), rowCount()-1, rowCount()-1);
    _solutions.append(sol);
    endInsertRows();
    
}

void SolutionPool::clear(){
    beginRemoveRows(QModelIndex(),0, rowCount() - 1);
    foreach(Solution * sol, _solutions){
        delete sol;
    }
    _solutions.clear();
    endRemoveRows();

}
