#include<iostream>
using namespace std;

struct box {
    bool up,down,left,right;
    box() {
        up = down = left = right = false;
    }
};

struct maze {
    box block[15][15];
    block[0][0].up = false;
};

int main() {

}