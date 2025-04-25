#include<iostream>
using namespace std;
#include<iomanip>



// Function to display currency
string displayCurrency(double amount) {
    stringstream ss;
    ss << fixed << setprecision(2) << amount;
    return "$" + ss.str();
}



class Transport {
protected:
    double maintenanceCost, travelCost, cost;
    int level;
    double maintenanceState;
    
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


int main(){

    return 0;
}