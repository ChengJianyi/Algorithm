#include "heap.h"
#include <time.h>
#include <stdlib.h>

Heap::Heap(){}
Heap::~Heap(){}

void Heap::initiallize(int count)
{
    srand((unsigned int)time(0));
    vHeap.push_back(999);
    for (int i = 0; i < count; ++i)
        vHeap.push_back(rand()%30);
}

void Heap::adjustDown(int i, int n)
{    
    int k = i;
    int j = 2*k;
    int key = vHeap[i];
    while(j < n+1)
    {
        if (vHeap[j+1] < vHeap[j]) ++j;
        if (vHeap[j] < key)
        {
            vHeap[k] = vHeap[j];
            k = j;
            j = j*2;
        }
        else break;
    }
    vHeap[k] = key;
}

void Heap::buildHeap()
{
    int n = vHeap.size()-1;
    for (int i = n/2; i > 0; --i )
    {
        adjustDown(i, n);
    }
}

void Heap::sortHeap()
{
    int tail = vHeap.size() - 1;
    int head = 1;
    cout<<vHeap[head]<<" ";
    while(tail > 1)
    {
        vHeap[head] = vHeap[tail];
        --tail;
        adjustDown(head, tail);
        cout<<vHeap[head]<<" ";
    }
    cout<<endl;
}

void Heap::printHeap()
{
    for (int i = 1; i < vHeap.size(); ++i)
        cout<<vHeap[i]<<" ";
    cout<<endl;
}
