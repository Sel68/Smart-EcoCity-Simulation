#include <iostream>
using namespace std;

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

int main()
{

    return 0;
}