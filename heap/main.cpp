#include <iostream>
#include "heap.h"

using namespace std;

int main()
{
    Heap h;
    h.initiallize(7);
    h.printHeap();
    h.buildHeap();
    h.printHeap();
    h.sortHeap();
}
