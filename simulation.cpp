#include<iostream>
using namespace std;
#include<iomanip>



// Function to display currency (converts double to string)
string displayCurrency(double amount) {
    stringstream ss;
    ss << fixed << setprecision(2) << amount;
    return "$" + ss.str();
}



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









int main(){

    return 0;
}