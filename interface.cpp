#include <iostream>
#include <vector>
#include <string>
using namespace std;

// інтерфейси
class Ideleter{
public:
    void virtual delete_item() = 0;
};
class Iadder{
public:
    void virtual add_item() = 0;
};
