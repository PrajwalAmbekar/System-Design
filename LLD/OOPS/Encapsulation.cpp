#include <iostream>
#include <string>
using namespace std;

class SportsCar
{
    // Characters if sportsCar

private:
    string model;
    string brand;
    bool isEngineOn;
    int currentSpeed;
    int currentGear;
    string tyreType;

public:
    // Constructor to initialize SportsCar Object
    SportsCar(string m, string b)
    {
        this->model = m;
        this->brand = b;
        this->tyreType = "Standard";
        isEngineOn = false;
        currentSpeed = 0;
        currentGear = 0;
    };

    // getter and setter methods for encapsulation
    string getModel()
    {
        return model;
    }

    string getBrand()
    {
        return brand;
    }
    string getTyreType()
    {
        return tyreType;
    }
    void setTyreType(string t)
    {
        this->tyreType = t;
    
    }

    // Behaviors of SportsCar
    void startEngine()
    {
        isEngineOn = true;
        cout << "Engine started for " << brand << " " << model << endl;
    }

    void shiftGear(int gear)
    {
        if (!isEngineOn)
        {
            cout << "Cannot shift gear .Engine is off for " << brand << " " << model << endl;
            return;
        }
        currentGear = gear;
        cout << "Gear is shifted to " << currentGear << " for " << brand << " " << model << endl;
    }

    void accelerate()
    {
        if (!isEngineOn)
        {
            cout << "cannot accelerate. Engine is off for " << brand << " " << model << endl;
            return;
        }
        currentSpeed += 10;
        cout << "Accelerating to " << currentSpeed << " km/h for " << brand << " " << model << endl;
    }

    void brake()
    {
        if (!isEngineOn)
        {
            cout << "Cannot brake. Engine is off for " << brand << " " << model << endl;
            return;
        }
        else if (currentSpeed <= 0)
        {
            cout << "Car is already stopped for " << brand << " " << model << endl;
            return;
        }
        currentSpeed -= 10;
        if (currentSpeed < 0)
        {
            currentSpeed = 0;
        }
        cout << "Braking for " << brand << " " << model << endl;
    };

    void stopEngine()
    {
        isEngineOn = false;
        currentSpeed = 0;
        currentGear = 0;
        cout << "Engine stopped for " << brand << " " << model << endl;
    }
    ~SportsCar()
    {
        cout << "SportsCar object destroyed for " << brand << " " << model << endl;
    } // Destructor to clean up resources when the SportsCar object is destroyed
};

int main()
{
    SportsCar *car1 = new SportsCar("BMW M3", "BMW");
    car1->startEngine();
    car1->shiftGear(1);
    car1->accelerate();
    car1->brake();
    car1->stopEngine();
    // Accessing private members using getter and setter methods
    cout << "Car Model: " << car1->getModel() << endl;
    cout << "Car Brand: " << car1->getBrand() << endl;
    cout << "Car Tyre Type: " << car1->getTyreType() << endl;
    cout << "Changing Tyre Type to MRF" << endl;
    car1->setTyreType("MRF");
    cout << "Car Tyre Type after change: " << car1->getTyreType() << endl;
    delete car1;
    return 0;
}