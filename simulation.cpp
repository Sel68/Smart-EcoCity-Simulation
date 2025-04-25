#include<iostream>
using namespace std;
#include<iomanip>

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
};


int main(){

    return 0;
}