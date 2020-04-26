//
// Created by Aleksy on 2020-04-22.
//

#ifndef GRAPHS_DIJKSTRA_H
#define GRAPHS_DIJKSTRA_H

#include "Queue.h"

void dijkstra(Graph &graph, bool printToFile = false) {

    std::ofstream file;
    if (printToFile) { file.open("dijkstra_result.txt"); }
    int noOfVertices = graph.getVerts().getSize();
    Queue queue(noOfVertices);

    for (int i = 0; i < noOfVertices ; i++) {
        queue.add(graph.getVert(i).getIndex(), INF);
    }

    queue.setDistance(graph.getStartingVert()->getIndex(),0);

    while(!queue.isEmpty()) {

        node currentV = queue.removeMin();
        List<Edge*>& neighbours = graph.getAdjacentTo(currentV.index);

        if(!neighbours.isEmpty()) {
            for (int i = 0; i < neighbours.getSize() ; i++) {

                Vertex* oppositeV = neighbours[i]->getOpposite(graph.getVert(currentV.index));

                if ( currentV.distance + neighbours[i]->getWeight() < queue.getDistance(oppositeV->getIndex()) ) {
                    queue.setDistance(oppositeV->getIndex(), currentV.distance + neighbours[i]->getWeight());
                    queue.setPrevious(oppositeV->getIndex(), currentV.index);
                }
            }

        }
//        std::cout << currentV.index << " distance: " << currentV.distance << " previous: " << currentV.previous << "\n";

        if (printToFile) {

            node n = currentV;
            List<int> path;
            path.push_back(n.index);
            while(n.previous != n.index) {
                path.push_back(n.previous);
                n = queue.getNode(n.previous);
            }

            file << "to: " << currentV.index << " cost: " << currentV.distance << " path: ";
            file << path << "\n";
        }
    }
}
#endif
