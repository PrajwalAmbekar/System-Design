#include <iostream>
#include <string>
using namespace std;

class Car
{
protected:
    string model;
    string brand;
    bool isEngineOn;
    int currentSpeed;

public:
    Car(string m, string b)
    {
        this->model = m;
        this->brand = b;
        isEngineOn = false;
        currentSpeed = 0;
    };

    void startEngine()
    {
        isEngineOn = true;
        cout << "Engine started for " << brand << " " << model << endl;
    };

    virtual void accelerate()
    {
        if (!isEngineOn)
        {
            cout << "Cannot accelerate. Engine is off for "
                 << brand << " " << model << endl;
            return;
        }

        currentSpeed += 10;

        cout << "Accelerating to " << currentSpeed
             << " km/h for " << brand << " " << model << endl;
    }

    void brake()
    {
        if (!isEngineOn)
        {
            cout << "Cannot brake. Engine is off for "
                 << brand << " " << model << endl;
            return;
        }

        if (currentSpeed <= 0)
        {
            cout << "Car is already stopped for "
                 << brand << " " << model << endl;
            return;
        }

        currentSpeed -= 10;

        cout << "Braking. Current speed: "
             << currentSpeed << " km/h for "
             << brand << " " << model << endl;
    }

    void stopEngine()
    {
        isEngineOn = false;
        currentSpeed = 0;
        cout << "Engine stopped for " << brand << " " << model << endl;
    };
    ~Car()
    {
        cout << "Car object destroyed for " << brand << " " << model << endl;
    }// Car* ManualCar = new ManualCar("Model S", "Tesla"); this is how we can create a new object of the derived class ManualCar using a pointer of the base class Car. This is an example of polymorphism in C++. The base class pointer can point to objects of derived classes, allowing us to call overridden methods in the derived class through the base class pointer.
};

// Derived class ManualCar inheriting from Car

class ManualCar : public Car
{
private:
    int currentGear;

public:
    ManualCar(string m, string b) : Car(m, b)
    {
        currentGear = 0;
    }

    void shiftGear(int gear)
    {
        if (!isEngineOn)
        {
            cout << "Cannot shift gear. Engine is off for " << brand << " " << model << endl;
            return;
        }
        currentGear = gear;
        cout << "Gear is shifted to " << currentGear << " for " << brand << " " << model << endl;
    }

    ~ManualCar()
    {
        cout << "ManualCar object destroyed for " << brand << " " << model << endl;
    }
};

class ElectricCar : public Car
{
private:
    int batteryPercentage;

public:
    ElectricCar(string m, string b) : Car(m, b)
    {
        batteryPercentage = 0;
    }
    void accelerate() override
    {
        if (!isEngineOn)
        {
            cout << "Cannot accelerate. Car is off for "
                 << brand << " " << model << endl;
            return;
        }

        if (batteryPercentage <= 0)
        {
            cout << "Cannot accelerate. Battery is empty for "
                 << brand << " " << model << endl;
            return;
        }

        currentSpeed += 10;
        batteryPercentage -= 10;

        if (batteryPercentage < 0)
        {
            batteryPercentage = 0;
        }

        cout << "Electric car accelerating to "
             << currentSpeed << " km/h. Battery: "
             << batteryPercentage << "%" << endl;
    }
    void chargeBattery(int percentage)
    {
        if (percentage <= 0)
        {
            cout << "Invalid charging percentage." << endl;
            return;
        }

        batteryPercentage += percentage;

        if (batteryPercentage > 100)
        {
            batteryPercentage = 100;
        }

        cout << "Battery charged to "
             << batteryPercentage << "% for "
             << brand << " " << model << endl;
    }
    void displayBatteryStatus()
    {
        cout << "Battery status: " << batteryPercentage << "% for " << brand << " " << model << endl;
    }

    void dischargeBattery()
    {
        if (batteryPercentage <= 0)
        {
            cout << "Battery is empty so no running condition for " << brand << " " << model << endl;
            return;
        }
        batteryPercentage -= 10;
        if (batteryPercentage < 0)
        {
            batteryPercentage = 0;
        }
        cout << "Battery discharged to " << batteryPercentage << "% for " << brand << " " << model << endl;
    }

    ~ElectricCar()
    {
        cout << "ElectricCar object destroyed for " << brand << " " << model << endl;
    }
};

int main()
{
    ManualCar *manualCar = new ManualCar("Model S", "Tesla");
    manualCar->startEngine();
    manualCar->shiftGear(1);
    manualCar->accelerate();
    manualCar->brake();
    manualCar->stopEngine();
    delete manualCar;

    ElectricCar *electricCar = new ElectricCar("Model 3", "Tesla");
    electricCar->startEngine();
    electricCar->chargeBattery(50);
    electricCar->displayBatteryStatus();
    electricCar->accelerate();
    electricCar->brake();
    electricCar->dischargeBattery();
    electricCar->displayBatteryStatus();
    electricCar->stopEngine();
    delete electricCar;
}