//
// Created by Aleksy on 2020-04-16.
// Adjacency Matrix Graph
//

#ifndef GRAPHS_AMGRAPH_H
#define GRAPHS_AMGRAPH_H

#include "List.h"
#include "Graph.h"
#include <iostream>
#include <string>
#include <random>
#include <chrono>
#include <fstream>

#define MIN_WEIGHT 1
#define MAX_WEIGHT 100


class AMGraph : public Graph {
private:

    List<Vertex> verts;
    List<Edge>   edges;
    Vertex*      startingVertex;
    Edge***      matrix;

public:


     AMGraph();
     AMGraph(int noOfVerts, double density);
    ~AMGraph();
    void loadFromFile(std::string filename);

    Vertex*       getStartingVert() override;
    List<Vertex>& getVerts() override;
    List<Edge>&   getEdges() override;
    Vertex&       getVert(int i) override;
    Edge&         getEdge(int i) override;
    List<Edge*>&  getAdjacentTo(int i) override;

    void createMatrix(int noOfVerts);
    void addVertex(int element);
    void addEdge(int weight, Vertex& start, Vertex& end);
    bool areConnected(Vertex& v1, Vertex& v2);

    friend std::ostream& operator << (std::ostream& stream, const AMGraph &graph) {

        stream
                << "verts count: " << graph.verts.getSize() << std::endl
                << "edges count: " << graph.edges.getSize() << std::endl;

        for (int i = 0; i < graph.edges.getSize() ; i++) {
            stream
                    << graph.edges[i].getStartVert()->getElement() << " - "
                    << graph.edges[i].getWeight() <<  " - "
                    << graph.edges[i].getEndVert()->getElement() << std::endl;
        }
        return stream;
    }
};

// ---------------- GRAPH ---------------- //

AMGraph::AMGraph() {}

AMGraph::~AMGraph() {
    for (int i = 0; i < verts.getSize() ; ++i) {
        delete[] matrix[i];
    }
    delete [] matrix;
}

AMGraph::AMGraph(int noOfVerts, double density) {

    // create adjacency matrix
    createMatrix(noOfVerts);

    // prepare random generator
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::uniform_int_distribution<int> random_weight(MIN_WEIGHT, MAX_WEIGHT);

    if (typeid(int) != typeid(int)) {
        std::cerr << "IncGraph Constructor: random element of this type is not supported" << std::endl;
    } else if (density == 1.0) {

        // create all vertices
        for (int i = 0; i < noOfVerts; i++) {
            addVertex(i);
        }

        // create all possible edges
        for (int i = 0; i < noOfVerts-1 ; i++) {
            for (int j = 0; j < noOfVerts-1-i ; j++) {
                addEdge(random_weight(generator), verts[i], verts[i+j+1]);
            }
        }
        startingVertex = &verts[0];

    } else if (noOfVerts >= 500) {

        //// is reasonably fast, but does not create exact number of edges

        // create first vertex
        addVertex(0);
        int count = 1;

        // create vertex and link it to another density*i random ones
        // this way graph will be connected
        for (int i = 1; i < noOfVerts ; i++) {

            addVertex(i);

            // calculate number of vertices
            // with which new vertex will be connected
            int fraction = ceil(density*i);

            for (int j = 0; j < fraction ; j++) {
                std::uniform_int_distribution<int> random_vert(0, i - 1);
                addEdge(random_weight(generator), verts[i], verts[random_vert(generator)]);
                count++;
            }
        }
        startingVertex = &verts[0];

    } else {

        // calculate total number of vertices
        int noOfEdges = floor(density * noOfVerts * (noOfVerts - 1) / 2);

        // create first vertex
        addVertex(0);

        // create vertex and link it to another random one
        // this way graph will be connected
        for (int i = 1; i < noOfVerts; i++) {
            addVertex(i);
            std::uniform_int_distribution<int> random_vert(0, i - 1);
            addEdge(random_weight(generator), verts[i], verts[random_vert(generator)]);
        }

        // create rest of the edges by random connections
        std::uniform_int_distribution<int> random_vert(0, noOfVerts - 1);
        for (int i = 0; i < noOfEdges - (noOfVerts - 1); i++) {
            int start = random_vert(generator);
            int end = random_vert(generator);
            int c = 0;

            while (start == end || areConnected(verts[start],verts[end]) ) {
                end = random_vert(generator);
                c++;
                if (c > noOfVerts) {
                    start = random_vert(generator);
                }
            }
            addEdge(random_weight(generator), verts[start], verts[end]);
        }
        startingVertex = &verts[0];
    }
}

void AMGraph::loadFromFile(std::string filename) {

    std::ifstream file(filename);

    if (file) {

        int noOfEdges, noOfVertices, startingVert;
        file >> noOfEdges >> noOfVertices >> startingVert;

        // create adjacency matrix
        createMatrix(noOfVertices);

        for (int i = 0; i < noOfVertices; i++) {
            addVertex(i);
        }

        for (int i = 0 ; i < noOfEdges ; i++) {
            int start, end, weight;
            file >> start >> end >> weight;

            addEdge(weight, verts[start], verts[end]);
        }

        startingVertex = &verts[startingVert];
    } else {
        std::cerr << "loadFromFile: couldn't open file" << std::endl;
    }
}

List<Vertex>& AMGraph::getVerts() {
    return verts;
}

List<Edge>& AMGraph::getEdges() {
    return edges;
}

Vertex* AMGraph::getStartingVert() {
    return startingVertex;
}

Vertex& AMGraph::getVert(int i) {
    return verts[i];
}

Edge& AMGraph::getEdge(int i) {
    return edges[i];
}

List<Edge*>& AMGraph::getAdjacentTo(int i) {

    for (int j = 0; j < verts.getSize() ; j++) {
        if (matrix[i][j] != nullptr) {
            verts[i].getList().push_front(matrix[i][j]);
        }
    }
    return verts[i].getList();
}

void AMGraph::createMatrix(int noOfVerts) {
    matrix = new Edge**[noOfVerts];
    for (int i = 0 ; i < noOfVerts ; ++i) {
        matrix[i] = new Edge*[noOfVerts];
        for (int j = 0; j < noOfVerts; ++j) {
            matrix[i][j] = nullptr;
        }
    }
}

void AMGraph::addVertex(int element) {
    verts.push_front(Vertex(verts.getSize(), element));
}

void AMGraph::addEdge(int weight, Vertex& start, Vertex& end) {
    Edge e(weight,start,end);
    auto* p = edges.push_front(e);
    matrix[start.getIndex()][end.getIndex()] = p;
    matrix[end.getIndex()][start.getIndex()] = p;
}

bool AMGraph::areConnected(Vertex& v1, Vertex& v2) {
    return (matrix[v1.getIndex()][v2.getIndex()] != nullptr);
}


#endif