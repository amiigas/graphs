//
// Created by Aleksy on 2020-04-23.
//

#ifndef GRAPHS_QUEUE_H
#define GRAPHS_QUEUE_H

#include <limits>
#define INF std::numeric_limits<int>::max()

struct node {
    int index;
    int distance;
    int previous;
};

class Queue {
public:

    node* data;
    int   last;
    int   size;

    Queue(int size);
    ~Queue();
    void add(int index, int distance);
    node removeMin();
    node getNode(int index);
    void setDistance(int index, int key);
    int  getDistance(int index);
    void setPrevious(int index, int previous);
    int  getPrevious(int index);
    bool isEmpty();
    void upheap(int nodeIndex);
    void downheap(int index);
    void swap(int i, int j);
    void display();
};

Queue::Queue(int size) {
    data = new node[size];
    last = 0;
    this->size = size;
}

Queue::~Queue() {
    delete data;
}

void Queue::add(int index, int distance) {
    data[last].index = index;
    data[last].distance = distance;
    data[last].previous = index;
    upheap(last);
    last++;
}

node Queue::removeMin() {
    node temp = data[0];
    swap(last-1,0);
//    data[last-1].distance = 0;
    last--;
    downheap(0);
    return temp;
}

node Queue::getNode(int index) {
    for (int i = 0; i < size ; i++) {
        if(data[i].index == index) {
            return data[i];
        }
    }
}

void Queue::setDistance(int index, int key) {
    for (int i = 0; i <  size; i++) {
        if(data[i].index == index) {
            if (i==0) {
                data[i].distance = key;
                downheap(i);
                return;
            } else {
                data[i].distance = key;
                upheap(i);
                return;
            }
        }
    }
}

int Queue::getDistance(int index) {
    for (int i = 0; i < size; i++) {
        if(data[i].index == index) {
            return data[i].distance;
        }
    }
}

void Queue::setPrevious(int index, int previous) {
    for (int i = 0; i < size; i++) {
        if(data[i].index == index) {
            data[i].previous = previous;
            return;
        }
    }
}

int Queue::getPrevious(int index) {
    for (int i = 0; i < size; i++) {
        if(data[i].index == index) {
            return data[i].previous;
        }
    }
}

bool Queue::isEmpty() {
    return (last <= 0);
}

void Queue::upheap(int nodeIndex) {

    int i = nodeIndex;
    while(data[(i-1)/2].distance > data[i].distance && i > 0) {
        swap((i-1)/2,i);
        i = (i-1)/2;
    }
}

void Queue::downheap(int nodeIndex) {

    int leftChild = 2*nodeIndex+1;
    int rightChild = 2*nodeIndex+2;
    int lastParent = (last-1-1)/2;
    int smallerChild = leftChild;                                        // większe to lewe, chyba że jest prawe

    if (last % 2) {                                         // sprawdzamy czy są oboje dzieci i wybieramy większe
        smallerChild = (data[leftChild].distance <= data[rightChild].distance) ? leftChild : rightChild;
    }

    if (data[nodeIndex].distance > data[smallerChild].distance && last != 1) {   // sprawdzamy czy trzeba zamienić z dzieckiem
        swap(nodeIndex, smallerChild);
    }

    if (smallerChild <= lastParent) {                                    // jeśli większe dziecko też jest rodzicem
        downheap(smallerChild);// to powtórz procedurę
    }
}

void Queue::swap(int i, int j) {
    node temp = data[j];
    data[j] = data[i];
    data[i] = temp;
}

void Queue::display() {

    for (int i = 0; i < size; ++i) {
        std::cout << data[i].index << " distance: " << data[i].distance << " previous: " << data[i].previous << "\n";
    }

}
#endif
