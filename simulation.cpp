#include <iostream>
using namespace std;
#include <iomanip>
#include <string>
using namespace std;

// Function to display currency (converts double to string)
string displayCurrency(double amount) {
    stringstream ss;
    ss << fixed << setprecision(2) << amount;
    return "$" + ss.str();
}

// Utilities (include Water, Gas, Electricity)
class Utilities {
protected:
    double capacity, currentUsage;

public:
    Utilities(double cap = 0) : capacity(cap), currentUsage(0) {}
    virtual ~Utilities() {}

    double getCapacity() const { return capacity; }
    double getCurrentUsage() const { return currentUsage; }

    virtual bool setUsage(double usage) {

        try{
            if (usage > capacity)
                throw runtime_error("Usage exceeds capacity");
            if (usage < 0)
                throw runtime_error("Usage cannot be negative");
            
            currentUsage = usage; return true;
        }catch(const runtime_error& e){
            cerr << "Error: " << e.what() << endl;
            return false;
        }
    }
    
    virtual string getType() const = 0;
};

class Water : public Utilities {
public:
    Water(double cap = 1000) : Utilities(cap) {}
    string getType() const override { return "Water"; }
};
    
class Electricity : public Utilities {
public:
    Electricity(double cap = 5000) : Utilities(cap) {}
    string getType() const override { return "Electricity"; }
};
    
class Gas : public Utilities {
public:
    Gas(double cap = 500) : Utilities(cap) {}
    string getType() const override { return "Gas"; }
};



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

// Residential Objects
class House : public Residential {
    int noOfRooms;
public:

    House(int rooms = 4, double land = 50, double cost = 45000)
        : Residential("House", land, cost, rooms * 2, rooms * 20, rooms * 50, rooms * 10), noOfRooms(rooms) {}
    //all house parameters are function of # of rooms

    void operate() override {
        cout << "A cozy " << noOfRooms << "-room house is lived in." << endl;
        simulateDailyConsumption();
    }
    void displayDetails() const override {
        Residential::displayDetails();
        cout << ", Rooms: " << noOfRooms << endl;
    }
};
    
class SkylineResidence : public Residential {
    int noOfApartments;
public:

    SkylineResidence(int apartments = 50, double land = 200, double cost = 750000)
        : Residential("Skyline Residence", land, cost, apartments * 3, apartments * 30, apartments * 80, apartments * 15), noOfApartments(apartments) {}
    //all house parameters are function of # of apartments
    
    void operate() override {
        cout << "A skyline residence with " << noOfApartments << " apartments provides housing." << endl;
        simulateDailyConsumption();
    }
        void displayDetails() const override {
        Residential::displayDetails();
        cout << ", Apartments: " << noOfApartments << endl;
    }
};



// Commercial Objects
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
        double getEnergyCapacity() const { return energyGencapacity; }
        double getPollutionGenerated() const { return pollutionGenerated; }
        string getEnergyType() const { return energyType; }
        bool isRenewable() const { return (energyType == "Solar" || energyType == "Wind"); }
        void operate() override {
            cout << "The " << energyType << " power plant is generating " << energyGencapacity << " units of energy." << endl;
        }
        void displayDetails() const override {
            Building::displayDetails();
            cout << ", Energy Type: " << energyType << ", Capacity: " << energyGencapacity << ", Pollution/Cycle: " << pollutionGenerated << endl;
        }
};




class Transport {
protected:
    double maintenanceCost, travelCost, cost, maintenanceState;;
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