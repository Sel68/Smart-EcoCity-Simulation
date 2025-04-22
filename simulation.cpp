#include <iostream>
using namespace std;

class Building {
protected:
    double landCover;
public:
    Building(double landCover = 0) : landCover(landCover) {}
};

class skyLineResidence : protected Building {
    int noOfApartments;
public:
    skyLineResidence(int noOfApartments = 0) : Building(), noOfApartments(noOfApartments) {}
};

class house : protected Building {
    int noOfRooms;
public:
    house(int noOfRooms = 0) : Building(), noOfRooms(noOfRooms) {}
};


int main()
{

    return 0;
}
