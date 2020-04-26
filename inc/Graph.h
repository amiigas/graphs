//
// Created by Aleksy on 2020-04-22.
//

#ifndef GRAPHS_GRAPH_H
#define GRAPHS_GRAPH_H

#include "List.h"
#include <iostream>

class Edge;

class Vertex;

class Graph {
public:
    virtual List<Vertex>& getVerts() = 0;
    virtual List<Edge>&   getEdges() = 0;
    virtual Vertex*       getStartingVert() = 0;
    virtual Vertex&       getVert(int i) = 0;
    virtual Edge&         getEdge(int i) = 0;
    virtual List<Edge*>&  getAdjacentTo(int i) = 0;
};

class Vertex {
private:

    int         index;
    int         element;
    List<Edge*> incidencyList;

public:

    explicit Vertex(int i, int elem)
            : index(i), element(elem)
    {}

    int          getIndex() const;
    int          getElement() const;
    List<Edge*>& getList();

    bool operator == (Vertex v) const;
    bool operator != (Vertex v) const;

    friend Edge;

    friend std::ostream& operator << (std::ostream& stream, const Vertex &vertex) {
        stream << vertex.element << " " ;
        return stream;
    }
};


class Edge {
private:

    int     weight;
    Vertex* startVert;
    Vertex* endVert;

public:

    explicit Edge(int weight)
            : weight(weight)
    {}

    explicit Edge(int weight, Vertex& start, Vertex& end)
            : weight(weight), startVert(&start), endVert(&end)
    {}

    int     getWeight() const;
    Vertex* getStartVert() const;
    Vertex* getEndVert() const;
    Vertex* getOpposite(Vertex& v) const;

    friend std::ostream& operator << (std::ostream& stream, const Edge &edge) {
        stream << edge.startVert->getElement() << " - "
               << edge.weight <<  " - "
               << edge.endVert->getElement() << std::endl;
        return stream;
    }

};

// ---------------- VERTEX ---------------- //

int Vertex::getElement() const {
    return element;
}

int Vertex::getIndex() const {
    return index;
}

List<Edge*>& Vertex::getList() {
    return incidencyList;
}

bool Vertex::operator == (Vertex v) const {
    return (element == v.getElement());
}

bool Vertex::operator != (Vertex v) const {
    return (element != v.getElement());
}

// ---------------- EDGE ---------------- //

int Edge::getWeight() const {
    return weight;
}

Vertex* Edge::getStartVert() const {
    return startVert;
}

Vertex* Edge::getEndVert() const {
    return endVert;
}

Vertex* Edge::getOpposite(Vertex& v) const {
    return (startVert->index == v.getIndex()) ? endVert : startVert;
}

#endif
