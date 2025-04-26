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
    class Mall : public Building {
        int noOfOutlets;
    public:
    
        Mall(int outlets = 20, double land = 500, double cost = 350000)
            : Building("Mall", land, cost), noOfOutlets(outlets) {}
    
        void operate() override {
            cout << "The mall with " << noOfOutlets << " outlets is open for business." << endl;
        }
        void displayDetails() const override {
            Building::displayDetails();
            cout << ", Outlets: " << noOfOutlets << endl;
        }
    
    };
    class PowerPlant : public Building {
        double energyGencapacity;
        double pollutionGenerated;
        string energyType;
    public:
    
        PowerPlant(string eType = "Coal", double capacity = 10000, double land = 400, double cost = 80000)
            : Building("Power Plant", land, cost), energyGencapacity(capacity), energyType(eType) {
            if (energyType == "Coal") { pollutionGenerated = 60; cost = 80000; } 
            else if (energyType == "Gas") { pollutionGenerated = 25; cost = 100000; } 
            else if (energyType == "Solar") { pollutionGenerated = 0.5; cost = 200000; capacity = 8000; } 
            else if (energyType == "Wind") { pollutionGenerated = 0.8; cost = 250000; capacity = 7500; } 
            else if (energyType == "Nuclear") { pollutionGenerated = 3; cost = 400000; capacity = 20000; }
            else { pollutionGenerated = 10; cost = 700000; } // default
            this->cost = cost;
        }
    };
class Transport {
protected:
    double maintenanceCost;
    double travelCost;
    double maintenanceState;
    int level;
public:
    Transport(double mcost, double tcost, double mstate, int lvl) {
        maintenanceCost = mcost;
        travelCost = tcost;
        maintenanceState = mstate;
        level = lvl;
    }
};

class Road : protected Transport {
public:
    Road(double mcost, double tcost, double mstate, int lvl) {
        maintenanceCost = mcost;
        travelCost = tcost;
        maintenanceState = mstate;
        level = lvl;
    }
};

class Railways : protected Transport {
public:
    Railways(double mcost, double tcost, double mstate, int lvl) {
        maintenanceCost = mcost;
        travelCost = tcost;
        maintenanceState = mstate;
        level = lvl;
    }
};

class Airport : protected Transport {
public:
    Airport(double mcost, double tcost, double mstate, int lvl) {
        maintenanceCost = mcost;
        travelCost = tcost;
        maintenanceState = mstate;
        level = lvl;
    }
};

class Factory : public Building {
  int level;
};

int main() {
    return 0;
}
