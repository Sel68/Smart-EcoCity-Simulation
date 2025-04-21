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


};

Class Utility{
	protected:
	int capacity;
	int current_usage;
	public:
		Utility(int cap,int cusage){
			capacity=cap;
			current_usage=cusage;
		}
		
	
	
	
class Water:protected Utility{
	public:
		Water(int cap,int cusage){
			capacity=cap;
			current_usage=cusage;
		}
		
	
};

class Eletricity:protected Utility{
	public:
		Eletricity(int cap,int cusage){
			capacity=cap;
			current_usage=cusage;
		}
};

class Gas:protected Utility{
	public:
		Gas(int cap,int cusage){
			capacity=cap;
			current_usage=cusage;
		}
};
	
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

int main()
{

    return 0;
}
