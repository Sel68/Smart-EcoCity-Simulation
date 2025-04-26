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

// Derived class of Building
class Residential : public Building {
    protected:
        int populationCapacity;
        Water waterSupply; Electricity electricitySupply; Gas gasSupply;
        
    public:
        Residential(string type, double land, double c, int popCap, double waterCap = 100, double elecCap = 200, double gasCap = 50)
            : Building(type, land, c), populationCapacity(popCap), waterSupply(waterCap), electricitySupply(elecCap), gasSupply(gasCap) {}
    
        int getPopulationCapacity() const { return populationCapacity; }
    
        void simulateDailyConsumption() {
            waterSupply.setUsage(waterSupply.getCurrentUsage() + populationCapacity * 0.12);
            electricitySupply.setUsage(electricitySupply.getCurrentUsage() + populationCapacity * 0.55);
            gasSupply.setUsage(gasSupply.getCurrentUsage() + populationCapacity * 0.06);
        }
        void displayDetails() const override {
            Building::displayDetails();
            cout << ", Population Capacity: " << populationCapacity << endl;
            cout << "  Utilities: Water (Usage/Cap: " << waterSupply.getCurrentUsage() << "/" << waterSupply.getCapacity()
                 << "), Electricity (Usage/Cap: " << electricitySupply.getCurrentUsage() << "/" << electricitySupply.getCapacity()
                 << "), Gas (Usage/Cap: " << gasSupply.getCurrentUsage() << "/" << gasSupply.getCapacity() << ")";
        }
    };

int main()
{

    return 0;
}
