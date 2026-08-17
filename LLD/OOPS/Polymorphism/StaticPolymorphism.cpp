#include <iostream>
using namespace std;

class ManualCar {
protected:
    string model;
    string brand;
    int currentSpeed;
    int currentGear;
    bool isEngineOn;

public:
    ManualCar(string m, string b) {
        this->model = m;
        this->brand = b;
        currentSpeed = 0;
        currentGear = 0;
        isEngineOn = false;
    }

    void startEngine() {
        isEngineOn = true;
        cout << "Engine started" << endl;
    }

    void shiftGear(int gear) {
        if (!isEngineOn) {
            cout << "Start the engine first" << endl;
            return;
        }

        currentGear = gear;
        cout << "Gear shifted to " << currentGear << endl;
    }

    void accelerate() {
        if (!isEngineOn) {
            cout << "Start the engine first" << endl;
            return;
        }

        currentSpeed += 10;
        cout << "Accelerating. Current speed: "
             << currentSpeed << " km/h" << endl;
    }

    // Static polymorphism through function overloading
    void accelerate(int increment) {
        if (!isEngineOn) {
            cout << "Start the engine first" << endl;
            return;
        }

        currentSpeed += increment;
        cout << "Accelerating. Current speed: "
             << currentSpeed << " km/h" << endl;
    }

    void brake() {
        if (!isEngineOn) {
            cout << "Start the engine first" << endl;
            return;
        }

        if (currentSpeed > 0) {
            currentSpeed -= 5;
            cout << "Braking. Current speed: "
                 << currentSpeed << " km/h" << endl;
        } else {
            cout << "Car is already stopped." << endl;
        }
    }

    void stopEngine() {
        isEngineOn = false;
        currentSpeed = 0;
        cout << "Engine stopped" << endl;
    }

    ~ManualCar() {
        cout << "Manual Car destroyed" << endl;
    }
};

int main() {
    // Stack object: automatically destroyed when it goes out of scope
    ManualCar myCar("Model S", "Tesla");

    myCar.startEngine();
    myCar.shiftGear(1);

    myCar.accelerate();    // Calls accelerate()
    myCar.accelerate(20);  // Calls overloaded accelerate(int)

    myCar.brake();
    myCar.stopEngine();

    return 0;
}