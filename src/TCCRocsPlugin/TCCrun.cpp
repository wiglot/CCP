/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) <year>  <name of author>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include "TCCrun.h"
//#include <ToolsPluginInterface.h>
#include <KLocalizedString>
#include <QString>
#include <QStringList>
#include <kgenericfactory.h>
#include <KAboutData>

#include "Instance.h"
#include <Solution.h>
#include "History.h"
#include "Cluster.h"
#include <rocs/graphDocument.h>
#include <rocs/graph.h>





static const KAboutData aboutdata ( "TCCrun", 0, ki18n ( "TCC Run" ) , "0.1" );

K_PLUGIN_FACTORY ( TCCRunToolsPluginFactory, registerPlugin<TCCRun>(); )
K_EXPORT_PLUGIN ( TCCRunToolsPluginFactory ( aboutdata ) )





TCCRun::TCCRun ( QObject* parent,  const QList<QVariant> & /* args*/ ) :
        ToolsPluginInterface ( TCCRunToolsPluginFactory::componentData(), parent ) {

}


TCCRun::~TCCRun() {

}


static CCP::Instance * rocs2tcc ( Graph *graph ) {
    int i;
    CCP::Instance * inst =  new CCP::Instance();
    CCP::Point ** points = new CCP::Point*[graph->nodes().count() ];
    for ( i = 0; i < graph->nodes().count(); ++i ) {
        Node * n1 = graph->nodes().at ( i );
        points[i] = new CCP::Point ( inst,
                                     n1->property ( "coordX" ).toDouble(),
                                     n1->property ( "coordY" ).toDouble(),
                                     n1->property ( "Demand" ).toDouble() );
        //kDebug() << "Point" << i << points[i]->position().x() << points[i]->position().y() << points[i]->demand();
    }
    inst->setPoints ( points, i );
    inst->setNumCenters ( graph->property ( "NumCenters" ).toInt() );
    inst->setCapacity ( graph->property ( "Capacity" ).toDouble() );
    new CCP::Distance ( inst );

    return inst;

}

static void tcc2rocs ( CCP::Solution * sol, Graph *g ) {
    NodeList nodes = g->nodes();
    g->addDynamicProperty ( "Value", sol->getValue() );
    g->addDynamicProperty ( "TimeTaken", sol->timeTaken() );
    g->addDynamicProperty ( "Iterations", qreal ( sol->iterations() ) );
    g->addDynamicProperty ( "AlgorithmName", sol->algorithmName() );
    QStringList colors;
    colors << "red" << "black" << "blue" << "cyan" << "green" << "yellow";
    foreach ( Edge *e, g->edges() )    {
        g->remove ( e );
    }

    for ( int j = 0; j < sol->instance()->numCenters(); ++j ) {
        CCP::Cluster * cluster = sol->cluster ( j );
        QString color = colors.at ( qrand() %colors.count() );
        Node* center = nodes.at ( cluster->getCenter()->index() );
        center->setWidth ( 0.4 );
        center->setColor ( color );

        for ( int i = 0; i < cluster->numPoints(); ++i ) {
            CCP::Point *p = cluster->getPoint ( i );
            Node * n = nodes.at ( p->index() );
      kDebug() << n->name() << p->index();
            n->setWidth ( 0.2 );
            n->setColor ( color );
            g->addEdge ( center, n );
        }
    }
}

static void convertHistory ( CCP::Solution * sol, Graph *g ) {
//     kDebug() << "Entry point";
    NodeList nodes = g->nodes();
    CCP::History * h = sol->history();

    for ( int i = 0; i <  nodes.size(); ++i ) {
        Node *n = nodes.at ( i );
        h->begin();
        CCP::HistoryStep step = h->moveSteps ( 0 ); //get first step
        QList <QVariant> assigns;
        while ( h->actualStep() < h->stepsCount()-1 ) {
            assigns.append ( step.assignedTo ( i ) );
            step = h->moveSteps ( 1 );
        }
        assigns.append ( step.assignedTo ( i ) );
//         kDebug() << "Finished history" << assigns;
        n->addDynamicProperty ( "History", ( assigns ) );
    }
}

QString TCCRun::run ( QObject* doc ) const {
    GraphDocument * graphDoc = qobject_cast<GraphDocument*> ( doc );
    if ( graphDoc ) {

        Graph * graph = graphDoc->activeGraph();
        CCP::Instance * inst = rocs2tcc ( graph );
        CCP::Solution * sol = new CCP::Solution ( inst );
        sol->constructSolution ( CCP::Density );
//             sol->run();
        if ( sol->isValid() ) {
            tcc2rocs ( sol,graph );
            convertHistory ( sol,graph );
        }
    }

    return QString ();
}


#include "TCCrun.moc"