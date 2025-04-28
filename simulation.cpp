#include <iostream>
using namespace std;
#include <iomanip>
#include <string>
#include <vector>



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


    Transport(double mcost = 100, double tcost = 10, double mstate = 100.0, int lvl = 1, double buildCost = 2000)
        : maintenanceCost(mcost), travelCost(tcost), maintenanceState(mstate), level(lvl), cost(buildCost) {}
    
    virtual ~Transport() {}
    
    double getMaintenanceState () const {return maintenanceState;}
    double getCost() const { return cost; }
    int getLevel() const {return level;}
    double getMaintCost() const { return maintenanceCost; }

    virtual void useTransport() {
        maintenanceState -= 0.5 * (1 + (100.0 - maintenanceState)/100.0); //degradation accelerate when in poor condition
        if (maintenanceState < 0) maintenanceState = 0;
        cout << "Using generic transport. Maintenance: " << fixed << setprecision(1) << maintenanceState << "%" << endl;
    }

    virtual bool performMaintenance(double budget) {
        if (maintenanceState >= 100.0) {
            cout << "Maintenance not needed (already at 100%)." << endl;
            return false;
        }
        if (budget >= maintenanceCost) {
            maintenanceState += 25.0;
            if (maintenanceState > 100.0) maintenanceState = 100.0;
            cout << "Performed maintenance. New state: " << fixed << setprecision(1) << maintenanceState << "%" << endl;
            return true;
        } else {
            cout << "Insufficient budget for maintenance (Required: " << displayCurrency(maintenanceCost) << ", Available: " << displayCurrency(budget) << ")" << endl;
            return false;
        }
    }
    virtual void displayDetails() const {
         cout << "Level: " << level << ", Maint. Cost: " << displayCurrency(maintenanceCost) << ", Travel Cost: " << displayCurrency(travelCost)
              << ", Maint. State: " << fixed << setprecision(1) << maintenanceState << "%, Build Cost: " << displayCurrency(cost);
    }
};

class Road : public Transport {
public:
    
    
    Road(int lvl = 1) : Transport(75 * lvl, 5.0 / lvl, 100.0, lvl, 4000 * lvl) {}

    //override base class functions (good practice)
    void useTransport() override {
        maintenanceState -= 0.3 * (1 + (100.0 - maintenanceState)/100.0);
        if (maintenanceState < 0) maintenanceState = 0;
        cout << "Used road network. Maintenance: " << fixed << setprecision(1) << maintenanceState << "%" << endl;
    }
    void displayDetails() const override {
        cout << "Type: Road Network, ";
        Transport::displayDetails(); cout << endl;}


};

class Railways : public Transport {
public:


    Railways(int lvl = 1) : Transport(250 * lvl, 2.0 / lvl, 100.0, lvl, 40000 * lvl) {} 

    //override base class functions (good practice)
    void useTransport() override {
        maintenanceState -= 0.15 * (1 + (100.0 - maintenanceState)/100.0);
        if (maintenanceState < 0) maintenanceState = 0;
        cout << "Used railway network. Maintenance: " << fixed << setprecision(1) << maintenanceState << "%" << endl;
    }
     void displayDetails() const override {
        cout << "Type: Railway Network, ";
        Transport::displayDetails(); cout << endl;}

        
};


class Airport : public Transport {
public:
    
    
    Airport(int lvl = 1) : Transport(1200 * lvl, 45.0 / lvl, 100.0, lvl, 150000 * lvl) {}
    
    //override base class functions (good practice)
    void useTransport() override {
        maintenanceState -= 0.6 * (1 + (100.0 - maintenanceState)/100.0); 
        if (maintenanceState < 0) maintenanceState = 0;
        cout << "Used airport. Maintenance: " << fixed << setprecision(1) << maintenanceState << "%" << endl;
    }
    void displayDetails() const override {
        cout << "Type: Airport, ";
        Transport::displayDetails(); cout << endl;}

};


//Vehicles --> ICE, EV
class Vehicle {
protected:
    string type; double cost, environmentalImpact;

public:

    Vehicle(string t, double c, double impact) : type(t), cost(c), environmentalImpact(impact) {}
    virtual ~Vehicle() {}
    

    string getType() const { return type; }
    double getCost() const { return cost; }
    double getEnvironmentalImpact() const { return environmentalImpact; }

    virtual void move() = 0;
    virtual void displayDetails() const {
        cout << "Type: " << type << ", Cost: " << displayCurrency(cost) << ", Env. Impact Score Mod: " << environmentalImpact;
    }
};

class EV : public Vehicle {
public:
    
    EV() : Vehicle("Electric Vehicle (EV)", 35000, 2.5) {}
    void move() override { cout << "An EV drives quietly, using electricity." << endl; }
     void displayDetails() const override {
        Vehicle::displayDetails();
        cout << " (Improves EcoScore)" << endl;
    }
};

class ICE : public Vehicle {
public:
    
    ICE() : Vehicle("ICE Vehicle", 22000, -3.0) {} 
    void move() override { cout << "An ICE vehicle drives, using gasoline and emitting fumes." << endl; }
    void displayDetails() const override {
        Vehicle::displayDetails();
        cout << " (Decreases EcoScore)" << endl;
    }

};

class Environment {
    double pollutionLevel, ecoScore, greenSpaceFactor;
    int population;
    double transportNetworkScore, totalPowerCapacity, totalRenewablePowerCapacity, totalPowerDemand;
     

public:
    Environment() : pollutionLevel(15.0), ecoScore(20), population(0), transportNetworkScore(0),
                    totalPowerCapacity(0), totalRenewablePowerCapacity(0), totalPowerDemand(0), greenSpaceFactor(1.0) {} // Initial pollution slightly higher

    void updatePopulation(const vector<Building*>& buildings) {
        population = 0;
        for (const auto* building : buildings) {
            if (const Residential* res = dynamic_cast<const Residential*>(building)) {
                population += res->getPopulationCapacity();
            }
            
        }
        //Power Demand as a function of population
        totalPowerDemand = population * 1.1; 
    }

    void updatePowerGrid(const vector<Building*>& buildings) {
        
        totalPowerCapacity = 0; totalRenewablePowerCapacity = 0;
        
        pollutionLevel = 5.0; // Base pollution level reset each cycle, then added to
        for (const auto* building : buildings) {
            //dynamic_cast checks for type and returns nullptr if not
            if (const PowerPlant* pp = dynamic_cast<const PowerPlant*>(building)) {
                totalPowerCapacity += pp->getEnergyCapacity();
                pollutionLevel += pp->getPollutionGenerated(); // Considers pollution from power plants
                if (pp->isRenewable()) {
                    totalRenewablePowerCapacity += pp->getEnergyCapacity();
                }
            }
           
        }
    }
    void modifyPollution(double change) {
        pollutionLevel += change;
        if (pollutionLevel < 0) pollutionLevel = 0;
    }

    void improveGreenSpace(double amount) {
        greenSpaceFactor += amount;
        if (greenSpaceFactor < 0.1) greenSpaceFactor = 0.1;
        recalculateEcoScore();
    }

    void recalculateEcoScore(const vector<Vehicle*>& playerVehicles = {}) { 

        double pollutionImpact = pollutionLevel * 1.5; 
        double baseScore = 70.0 - pollutionImpact;

        // Bonus for renewable energy percentage
        double renewablePercent = calculateRenewableEnergyPercentage();
        double renewableBonus = (renewablePercent / 10.0); //+10 points if 100% renewable

        // Penalty(ICE) or Bonus (EV) from vehicles
        double vehicleImpact = 0;
        for(const auto* v : playerVehicles) {
            vehicleImpact += v->getEnvironmentalImpact();
        }

        // Bonus from green spaces
        double greenSpaceBonus = (greenSpaceFactor - 1.0) * 15.0; 

         // Bonus for good transport network
         double transportBonus = transportNetworkScore / 50.0; 

        ecoScore = baseScore + renewableBonus + vehicleImpact + greenSpaceBonus + transportBonus;

        // ecoScore = max(0.0, min(100.0, ecoScore));
    }
    void updateTransportScore(const vector<Transport*>& transport) {
        transportNetworkScore = 0;
        for(const auto* t : transport) {
            double maintenanceFactor = t->getLevel() * (t->getMaintenanceState() / 100.0); 
            if (dynamic_cast<const Road*>(t)) transportNetworkScore += 5 * maintenanceFactor;
            else if (dynamic_cast<const Railways*>(t)) transportNetworkScore += 20 * maintenanceFactor;
            else if (dynamic_cast<const Airport*>(t)) transportNetworkScore += 40 * maintenanceFactor; 
        }
     }

    double calculateRenewableEnergyPercentage() const {
        if (totalPowerCapacity <= 0) return 0.0;
        return (totalRenewablePowerCapacity / totalPowerCapacity) * 100.0;
    }

    friend ostream& operator<<(ostream& os, const Environment& env) {
        os << "--- City Environment ---" << endl;
        os << "Population: " << env.population << endl;
        os << "Pollution Level: " << fixed << setprecision(1) << env.pollutionLevel << " (Lower is better)" << endl;
        os << "EcoScore: " << fixed << setprecision(1) << env.ecoScore << " / 100" << endl;
        os << "Green Space Factor: " << fixed << setprecision(2) << env.greenSpaceFactor << endl;
        os << "Transport Network Score: " << fixed << setprecision(1) << env.transportNetworkScore << endl;
        os << "Power Demand: " << fixed << setprecision(1) << env.totalPowerDemand
        << " | Capacity: " << env.totalPowerCapacity << endl;
        os << "Renewable Energy: " << fixed << setprecision(1) << env.calculateRenewableEnergyPercentage() << "%" << endl;
        os << "------------------------\n" << endl;
        return os;}


    double getEcoScore() const { return ecoScore; }
    double getPollutionLevel() const { return pollutionLevel; }

};



int main() {
    
  
  return 0;
}