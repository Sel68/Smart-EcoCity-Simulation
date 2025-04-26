#include <iostream>
using namespace std;

//Building (Base class for all structures)
class Building {
    protected:
        double landCover, cost; string buildingType;
        
    public:
        Building(string type = "Generic", double land = 0, double c = 1000) : buildingType(type), landCover(land), cost(c) {}
        virtual ~Building() {}
    
        double getLandCover() const { return landCover; }
        string getBuildingType() const { return buildingType; }
        double getCost() const { return cost; }
    
        virtual void operate() { cout << "Operating a generic building." << endl; }
        virtual void displayDetails() const {
            cout << "Type: " << buildingType << ", Land Cover: " << landCover << " sq units, Cost: " << displayCurrency(cost);
        }
    };

int main()
{

    return 0;
}
