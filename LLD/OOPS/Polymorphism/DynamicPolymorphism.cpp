#include <iostream>
using namespace std;

class Car{
    protected:
        string model;
        string brand;
        bool isEngineOn;
        int currentSpeed;
    public:
    Car(string m,string b){
        model = m;
        brand = b;
        isEngineOn  = false;
        currentSpeed = 0;
    }

    void startEngine(){
        isEngineOn = true;
        cout << "Engine started" << endl;
    }

    void stopEngine(){
        isEngineOn = false;
        currentSpeed = 0;
        cout << "Engine stopped" << endl;
    }

    virtual void accelerate() = 0; // pure virtual function 
    virtual void brake() = 0; // pure virtual function

    ~Car(){
        cout << "Car destroyed" << endl;
    }
};


class ManualCar : public Car{
    private:
       int currentGear;
    public:
    ManualCar(string m,string b) : Car(m,b){
        currentGear = 0;
    }

    void shiftGear(int gear){
       currentGear = gear;
       cout << "Gear shifted to " << currentGear << endl;
    }

    void accelerate() override{
        if(!isEngineOn){
            cout << "Start the engine first" << endl;
            return;

        }
        currentSpeed += 10;
        cout << "Accelerating. Current speed: " << currentSpeed << " km/h" << endl;

    }

    void brake() override{
        if(currentSpeed > 0){
            currentSpeed -= 5;
            cout << "Braking. Current speed: " << currentSpeed << " km/h" << endl;
        } else {
            cout << "Car is already stopped." << endl;
        }
    }
    ~ManualCar(){
        cout << "Manual Car destroyed" << endl;
    }
};


class ElectricCar : public Car{
    private:
        int batteryLevel;
    public:
        ElectricCar(string m,string b) : Car(m,b){
            batteryLevel = 100;
        }
    
        void accelerate() override{
            if(!isEngineOn){
                cout << "Start the engine first" << endl;
                return;
            }
            if(batteryLevel <= 0){
                cout << "Battery is empty. Cannot accelerate." << endl;
                return;
            }
            currentSpeed += 15;
            batteryLevel -= 5;
            cout << "Accelerating. Current speed: " << currentSpeed << " km/h, Battery level: " << batteryLevel << "%" << endl;
        }

        void brake() override{
            if(currentSpeed > 0){
                currentSpeed -= 5;
                cout << "Braking. Current speed: " << currentSpeed << " km/h" << endl;
            } else {
                cout << "Car is already stopped." << endl;
            }
        }
        ~ElectricCar(){
            cout << "Electric Car destroyed" << endl;
        }
};


int main() {
    // Car* car1 = new ManualCar("Tesla 1", "Tesla");
    // ManualCar* manualCar = dynamic_cast<ManualCar*>(car1); 
    // these lines are used in casting like mainly using Car* pointer to point to derived class object and then casting it to derived class pointer type. Because we are using dynamic polymorphism here, we can use base class pointer to point to derived class object and then call the derived class methods using base class pointer. But if we want to access the derived class specific methods, we need to cast the base class pointer to derived class pointer type. for example, in this case, we can use dynamic_cast to cast the base class pointer car1 to derived class pointer manualCar and then call the shiftGear method of ManualCar class. But if we don't cast it, we can't access the shiftGear method because it's not present in the base class Car.
    ManualCar* myManualCar = new ManualCar("Model S", "Tesla");
    myManualCar->startEngine();
    myManualCar->shiftGear(1); 
    myManualCar->accelerate();
    myManualCar->brake();
    myManualCar->stopEngine();
    delete myManualCar;
    cout << "---------------------------------------------------" << endl;
    ElectricCar* myElectricCar = new ElectricCar("Model 3", "Tesla");
    myElectricCar->startEngine();
    myElectricCar->accelerate();
    myElectricCar->brake();
    myElectricCar->stopEngine();
    delete myElectricCar;

    return 0;
}