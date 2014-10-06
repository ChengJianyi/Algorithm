#include <iostream>
#include <vector>

using namespace std;

//template <typename T>
class Heap{
private:
    vector<int> vHeap;
public:
    Heap();
    ~Heap();
    void initiallize(int count);
    void adjustDown(int i, int n);
    void buildHeap();
    void sortHeap();
    void printHeap();
};
