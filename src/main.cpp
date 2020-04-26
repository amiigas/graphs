//
// Created by Aleksy on 2020-04-08.
//

#include <iostream>
#include <chrono>
#include "ILGraph.h"
#include "AMGraph.h"
#include "Dijkstra.h"

#define BG "\033[1;32m"
#define Y  "\033[33m"
#define RESET   "\033[0m"

using namespace std;

// --------------- TESTING --------------- //

string loadingBar(int i, int amonut) {
    int progress = static_cast<double>(i)/amonut*10;
    switch(progress){
        case 0: return "[          ] ";
        case 1: return "[=         ] ";
        case 2: return "[==        ] ";
        case 3: return "[===       ] ";
        case 4: return "[====      ] ";
        case 5: return "[=====     ] ";
        case 6: return "[======    ] ";
        case 7: return "[=======   ] ";
        case 8: return "[========  ] ";
        case 9: return "[========= ] ";
        default:return "[          ] ";
    }

}

void test(string type, int amount, int vertices, double density) {

    if (type == "IL") {
        chrono::duration<double, std::milli> elapsedTime(0);
        for (int i = 0; i < amount; i++) {
            cout << "\r";
            cout << loadingBar(i, amount) << i << "%";
            cout << std::flush;
            ILGraph graph(vertices, density);
            auto start = chrono::high_resolution_clock::now();
            dijkstra(graph);
            auto stop = chrono::high_resolution_clock::now();
            chrono::duration<double, std::milli> oneRun = stop - start;
            elapsedTime += oneRun;
        }

        cout << "\r";
        cout << Y << amount << RESET << " IL graphs "
             << Y << vertices << RESET << " vertices "
             << Y << density << RESET << " density "
             << "dijkstra time: " << BG << elapsedTime.count() << RESET << "ms";
        cout << std::flush;
        cout << "\n";
    } else if (type == "AM") {
        chrono::duration<double, std::milli> elapsedTime(0);
        for (int i = 0; i < amount; i++) {
            cout << "\r";
            cout << loadingBar(i, amount) << i << "%";
            cout << std::flush;
            AMGraph graph(vertices, density);
            auto start = chrono::high_resolution_clock::now();
            dijkstra(graph);
            auto stop = chrono::high_resolution_clock::now();
            chrono::duration<double, std::milli> oneRun = stop - start;
            elapsedTime += oneRun;
        }

        cout << "\r";
        cout << Y << amount << RESET << " AM graphs "
             << Y << vertices << RESET << " vertices "
             << Y << density << RESET << " density "
             << "dijkstra time: " << BG << elapsedTime.count() << RESET << "ms";
        cout << std::flush;
        cout << "\n";
    }
}

// --------------- MAIN --------------- //

int main() {

    ILGraph graph;
    graph.loadFromFile("test_graph.txt");
    cout << Y << "writing to: dijkstra_result.txt" << RESET << "\n";
    dijkstra(graph,true);

    //// Incidence List Graph

    test("IL",100,10,0.25);
    test("IL",100,10,0.5);
    test("IL",100,10,0.75);
    test("IL",100,10,1.0);

    test("IL",100,50,0.25);
    test("IL",100,50,0.5);
    test("IL",100,50,0.75);
    test("IL",100,50,1.0);

    test("IL",100,100,0.25);
    test("IL",100,100,0.5);
    test("IL",100,100,0.75);
    test("IL",100,100,1.0);
//
//    test("IL",100,500,0.25);
//    test("IL",100,500,0.5);
//    test("IL",100,500,0.75);
//    test("IL",100,500,1.0);
//
//    test("IL",100,1000,0.25);
//    test("IL",100,1000,0.5);
//    test("IL",100,1000,0.75);
//    test("IL",100,1000,1.0);
//
//    //// Adjacency Matrix Graph
//
//    test("AM",100,10,0.25);
//    test("AM",100,10,0.5);
//    test("AM",100,10,0.75);
//    test("AM",100,10,1.0);
//
//    test("AM",100,50,0.25);
//    test("AM",100,50,0.5);
//    test("AM",100,50,0.75);
//    test("AM",100,50,1.0);
//
//    test("AM",100,100,0.25);
//    test("AM",100,100,0.5);
//    test("AM",100,100,0.75);
//    test("AM",100,100,1.0);
//
//    test("AM",100,500,0.25);
//    test("AM",100,500,0.5);
//    test("AM",100,500,0.75);
//    test("AM",100,500,1.0);
//
//    test("AM",100,1000,0.25);
//    test("AM",100,1000,0.5);
//    test("AM",100,1000,0.75);
//    test("AM",100,1000,1.0);





    return 0;
}