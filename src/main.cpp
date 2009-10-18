#include <QCoreApplication>
#include "Instance.h"

using namespace CCP;

int main(int argc, char** argv)
{
    QCoreApplication app(argc, argv);
    Instance foo;
    return app.exec();
}
