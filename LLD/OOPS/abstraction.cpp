#include <iostream>
#include <string>
using namespace std;

// Abtraction is a process of hiding the implementation details and showing only functionality to the user. In C++, abstraction can be achieved using abstract classes and interfaces. An abstract class is a class that cannot be instantiated and is designed to be inherited by other classes. It can contain pure virtual functions, which are functions that have no implementation in the base class and must be overridden in derived classes.
class Car
{
    //characteristics of Car
public:
    virtual void startEngine() = 0;
    virtual void stopEngine() = 0;
    virtual void shiftGear(int gear) = 0;
    virtual void accelerate() = 0;
    virtual void brake() = 0;
    virtual ~Car() = default; // Virtual destructor for proper cleanup of derived classes
};

class SportsCar : public Car

{
    //Characteristics of SportsCar
public:
    string model;
    string brand;
    bool isEngineOn;
    int currentSpeed;
    int currentGear;

    // Constructor to initialize the SportsCar object
    SportsCar(string m,string b){
        this->model = m;
        this->brand = b;
        isEngineOn = false;
        currentSpeed = 0;
        currentGear = 0;
    };
    //Behaviors of SportsCar
    void startEngine() {
        isEngineOn = true;
        cout << "Engine started for " << brand << " " << model << endl;
    }

    void shiftGear(int gear){
        if(isEngineOn){
            currentGear = gear;
            cout << "Gear shifted to " << currentGear << " for " << brand  << " " << model <<endl;
        }else{
            cout << "Cannot shift gear. Engine is off for " << brand  << " " << model <<endl;
        }
    }

    void accelerate(){
        if(!isEngineOn){
            cout << "Cannot accelerate. Engine is off for " << brand  << " " << model <<endl;
            return;
        }
        currentSpeed += 10;
        cout << "Accelerating. Current speed: " << currentSpeed << " km/h for " << brand  << " " << model <<endl;
    }
    void brake(){
        if(!isEngineOn){
            cout << "Cannot brake. Engine is off for " << brand  << " " << model <<endl;
            return;
        }
        if(currentSpeed > 0){
            currentSpeed -= 10;
            cout << "Braking. Current speed: " << currentSpeed << " km/h for " << brand  << " " << model <<endl;
        }
    }

      void stopEngine() {
        isEngineOn = false;
        currentSpeed = 0;
        currentGear = 0;
        cout << "Engine stopped for " << brand << " " << model <<endl;
    }

};

int main(){
    Car* myCar = new SportsCar("BMW M3", "BMW");
    Car* myCar2 = new SportsCar("Audi R8", "Audi");
    myCar2->startEngine();
    myCar2->shiftGear(1);
    myCar2->accelerate();
    myCar2->shiftGear(2);
    myCar2->accelerate();
    myCar2->shiftGear(1);
    myCar2->brake();
    myCar2->shiftGear(0);
    myCar2->stopEngine();

    
    myCar->startEngine();
    myCar->shiftGear(1);
    myCar->accelerate();
    myCar->shiftGear(2);
    myCar->accelerate();
    myCar->shiftGear(1);
    myCar->brake();
    myCar->shiftGear(0);
    myCar->stopEngine();
    delete myCar; // Clean up the dynamically allocated memory
    delete myCar2; // Clean up the dynamically allocated memory
    return 0;
}