#include <iostream>
#include <memory>
#include <string>

using namespace std;

class IEngine
{ 
    public:
        virtual void start() const = 0;
        virtual ~IEngine() = default;  
};

class IVehicle
{
public:
    explicit IVehicle(IEngine& engine) : m_engine(engine) {};
    virtual ~IVehicle() = default;

    virtual void drive() {
        m_engine.start();
        driveVehicle(); 
    };
 
protected:
    virtual void driveVehicle() const = 0;


private:
    /* data */
    IEngine& m_engine;
};


class GasEngine: public IEngine
{
public:
    void start() const override
    {
        cout << "Starting gas engine." << endl;
    }
};

class ElectricEngine: public IEngine
{
public:
    void start() const override
    {
        cout << "Starting electric engine." << endl;
    }
};

class HybridEngine: public IEngine
{
public:
    void start() const override
    {
        cout << "Starting hybrid engine." << endl;
    }
};


class Car: public IVehicle
{
public:
    Car(IEngine& engine) : IVehicle(engine)  {};

    void driveVehicle() const override
    {
        cout << "Driving a car." << endl;
    }
};

class Truck: public IVehicle
{
public:
    Truck(IEngine& engine) : IVehicle(engine)  {};

    void driveVehicle() const override
    {
        cout << "Driving a truck." << endl;
    }
};

class Bike: public IVehicle
{
public:
    Bike(IEngine& engine) : IVehicle(engine)  {};

    void driveVehicle() const override
    {
        cout << "Driving a Bike." << endl;
    }
};

void test_engines()
{
    // Create an array of pointers to all engine objects.
    const std::unique_ptr<IEngine> engines[]
    {
        make_unique<GasEngine>(),
        make_unique<ElectricEngine>(),
        make_unique<HybridEngine>(),
    };

    // Iterate through the array and invoke the uploadContents and getFreeSpace
    // methods on each object
    for (const auto& engine : engines)
    {        
        engine->start();
        cout << endl;
    }
}

int main()
{
    // test_engines();

    // Create engine objects
    auto gasEngine = GasEngine();
    auto electricEngine = ElectricEngine();
    auto hybridEngine = HybridEngine();

    // Create an array of pointers to Vehicle objects.
    const std::unique_ptr<IVehicle> vehicles[]
    {
        make_unique<Car>(electricEngine),
        make_unique<Truck>(gasEngine),
        make_unique<Bike>(hybridEngine),
    };


    // Iterate through the array and invoke the start and driving

    for (const auto& vehicle : vehicles)
    {        
        vehicle->drive();
        cout << endl;
 
    }

    return 0;
}