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


class Transport{
    protected:
        double maintenanceCost;
        double travelCost;
        double maintenanceState;
        int level;
    public:
        Transport(double mcost, double tcost, double mstate, int lvl){
            maintenanceCost = mcost;
            travelCost = tcost;
            maintenanceState = mstate;
            level = lvl;
        }
};

class Road : protected Transport{
    public:
        Road(double mcost, double tcost, double mstate, int lvl){
            maintenanceCost = mcost;
            travelCost = tcost;
            maintenanceState = mstate;
            level = lvl;
        }
};

class Railways: protected Transport{
    public:
        Railways(double mcost, double tcost, double mstate, int lvl){
            maintenanceCost = mcost;
            travelCost = tcost;
            maintenanceState = mstate;
            level = lvl;
        }
};

class Airport: protected Transport{
    public:
        Airport(double mcost, double tcost, double mstate, int lvl){
            maintenanceCost = mcost;
            travelCost = tcost;
            maintenanceState = mstate;
            level = lvl;
        }
};
class building{
	protected:
		double maintenanceCost;
		double land;
	public:
		friend void buyBuilding(building &b);
};
class Mall: public building{
    private:
        double maintenanceCost;
        double land;
	
};
class PowerPlants: public building{
    private:
        double maintenanceCost;
        double land;

};
class Factory: public building{
    private:
        double maintenanceCost;
        double land;


};

int main()
{

    return 0;
}