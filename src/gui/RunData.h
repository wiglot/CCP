#ifndef RUNDATA_H
#define RUNDATA_H

#include <QWidget>
namespace CCP{
    class Solution;
}

namespace Ui {
    class RunData;
}

class RunData : public QWidget {
    Q_OBJECT
public:
    explicit RunData(QWidget *parent = 0);
    ~RunData();

public slots:
    void setData(CCP::Solution * sol);

protected:
    void changeEvent(QEvent *e);

private:
    Ui::RunData *ui;
};

#endif // RUNDATA_H
