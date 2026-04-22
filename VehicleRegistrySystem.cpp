#include <iostream>
#include <string>
#include <cstring>
#include <iomanip>
#include <limits>

using namespace std;

// Base Class: Vehicle
class Vehicle {
protected:
    string vehicleID;
    string manufacturer;
    string model;
    int year;
    
public:
    static int totalVehicles;
    
    // Constructors
    Vehicle() : vehicleID(""), manufacturer(""), model(""), year(0) {
        totalVehicles++;
    }
    
    Vehicle(string id, string manu, string mod, int y) 
        : vehicleID(id), manufacturer(manu), model(mod), year(y) {
        totalVehicles++;
    }
    
    // Copy Constructor
    Vehicle(const Vehicle &v) {
        vehicleID = v.vehicleID;
        manufacturer = v.manufacturer;
        model = v.model;
        year = v.year;
        totalVehicles++;
    }
    
    // Destructor
    virtual ~Vehicle() {
        totalVehicles--;
    }
    
    // Getters
    string getVehicleID() const { return vehicleID; }
    string getManufacturer() const { return manufacturer; }
    string getModel() const { return model; }
    int getYear() const { return year; }
    
    // Setters
    void setVehicleID(string id) { vehicleID = id; }
    void setManufacturer(string manu) { manufacturer = manu; }
    void setModel(string mod) { model = mod; }
    void setYear(int y) { year = y; }
    
    // Virtual function for display
    virtual void display() const {
        cout << "Vehicle ID: " << vehicleID << endl;
        cout << "Manufacturer: " << manufacturer << endl;
        cout << "Model: " << model << endl;
        cout << "Year: " << year << endl;
    }
    
    static int getTotalVehicles() {
        return totalVehicles;
    }
};

int Vehicle::totalVehicles = 0;

// Single Inheritance: Car inherits from Vehicle
class Car : public Vehicle {
protected:
    string fuelType;
    
public:
    Car() : Vehicle(), fuelType("") {}
    
    Car(string id, string manu, string mod, int y, string fuel)
        : Vehicle(id, manu, mod, y), fuelType(fuel) {}
    
    string getFuelType() const { return fuelType; }
    void setFuelType(string fuel) { fuelType = fuel; }
    
    void display() const override {
        Vehicle::display();
        cout << "Fuel Type: " << fuelType << endl;
    }
};

// Multilevel Inheritance: ElectricCar inherits from Car
class ElectricCar : public Car {
protected:
    double batteryCapacity;
    
public:
    ElectricCar() : Car(), batteryCapacity(0) {}
    
    ElectricCar(string id, string manu, string mod, int y, string fuel, double capacity)
        : Car(id, manu, mod, y, fuel), batteryCapacity(capacity) {}
    
    double getBatteryCapacity() const { return batteryCapacity; }
    void setBatteryCapacity(double capacity) { batteryCapacity = capacity; }
    
    void display() const override {
        Car::display();
        cout << "Battery Capacity: " << batteryCapacity << " kWh" << endl;
    }
};

// Base class for Multiple Inheritance
class Aircraft {
protected:
    double flightRange;
    
public:
    Aircraft() : flightRange(0) {}
    Aircraft(double range) : flightRange(range) {}
    
    double getFlightRange() const { return flightRange; }
    void setFlightRange(double range) { flightRange = range; }
    
    void displayAircraft() const {
        cout << "Flight Range: " << flightRange << " km" << endl;
    }
};

// Multiple Inheritance: FlyingCar inherits from Car and Aircraft
class FlyingCar : public Car, public Aircraft {
private:
    double wingSpan;
    
public:
    FlyingCar() : Car(), Aircraft(), wingSpan(0) {}
    
    FlyingCar(string id, string manu, string mod, int y, string fuel, double range, double wings)
        : Car(id, manu, mod, y, fuel), Aircraft(range), wingSpan(wings) {}
    
    double getWingSpan() const { return wingSpan; }
    void setWingSpan(double wings) { wingSpan = wings; }
    
    void display() const {
        Car::display();
        cout << "Flight Range: " << flightRange << " km" << endl;
        cout << "Wing Span: " << wingSpan << " m" << endl;
    }
};

// Multilevel Inheritance: SportsCar inherits from ElectricCar
class SportsCar : public ElectricCar {
private:
    double topSpeed;
    
public:
    SportsCar() : ElectricCar(), topSpeed(0) {}
    
    SportsCar(string id, string manu, string mod, int y, string fuel, double capacity, double speed)
        : ElectricCar(id, manu, mod, y, fuel, capacity), topSpeed(speed) {}
    
    double getTopSpeed() const { return topSpeed; }
    void setTopSpeed(double speed) { topSpeed = speed; }
    
    void display() const override {
        ElectricCar::display();
        cout << "Top Speed: " << topSpeed << " km/h" << endl;
    }
};

// Hierarchical Inheritance: Sedan inherits from Car
class Sedan : public Car {
private:
    double trunkCapacity;
    
public:
    Sedan() : Car(), trunkCapacity(0) {}
    
    Sedan(string id, string manu, string mod, int y, string fuel, double trunk)
        : Car(id, manu, mod, y, fuel), trunkCapacity(trunk) {}
    
    double getTrunkCapacity() const { return trunkCapacity; }
    void setTrunkCapacity(double trunk) { trunkCapacity = trunk; }
    
    void display() const override {
        Car::display();
        cout << "Trunk Capacity: " << trunkCapacity << " L" << endl;
    }
};

// Hierarchical Inheritance: SUV inherits from Car
class SUV : public Car {
private:
    bool fourWheelDrive;
    
public:
    SUV() : Car(), fourWheelDrive(false) {}
    
    SUV(string id, string manu, string mod, int y, string fuel, bool awd)
        : Car(id, manu, mod, y, fuel), fourWheelDrive(awd) {}
    
    bool getFourWheelDrive() const { return fourWheelDrive; }
    void setFourWheelDrive(bool awd) { fourWheelDrive = awd; }
    
    void display() const override {
        Car::display();
        cout << "Four Wheel Drive: " << (fourWheelDrive ? "Yes" : "No") << endl;
    }
};

// VehicleRegistry Class - Manages array of Vehicle pointers
class VehicleRegistry {
private:
    Vehicle** vehicles;
    int capacity;
    int count;
    
public:
    VehicleRegistry(int cap = 100) : capacity(cap), count(0) {
        vehicles = new Vehicle*[capacity];
        for(int i = 0; i < capacity; i++) {
            vehicles[i] = nullptr;
        }
    }
    
    ~VehicleRegistry() {
        for(int i = 0; i < count; i++) {
            delete vehicles[i];
        }
        delete[] vehicles;
    }
    
    // Add vehicle
    bool addVehicle(Vehicle* v) {
        if(count < capacity) {
            vehicles[count++] = v;
            return true;
        }
        return false;
    }
    
    // Display all vehicles
    void displayAll() const {
        if(count == 0) {
            cout << "\nNo vehicles in registry.\n";
            return;
        }
        
        cout << "\n" << string(60, '=') << endl;
        cout << "VEHICLE REGISTRY (" << count << " vehicles)" << endl;
        cout << string(60, '=') << endl;
        
        for(int i = 0; i < count; i++) {
            cout << "\n--- Vehicle " << (i+1) << " ---" << endl;
            vehicles[i]->display();
            cout << endl;
        }
        cout << "Total vehicles in system: " << Vehicle::getTotalVehicles() << endl;
    }
    
    // Search by ID
    Vehicle* searchByID(string id) const {
        for(int i = 0; i < count; i++) {
            if(vehicles[i]->getVehicleID() == id) {
                return vehicles[i];
            }
        }
        return nullptr;
    }
};

// Main function with menu-driven interface
int main() {
    VehicleRegistry registry;
    int choice;
    string id, manu, model, fuel;
    int year;
    
    cout << "\n========================================\n";
    cout << "   VEHICLE REGISTRY SYSTEM\n";
    cout << "========================================\n";
    
    do {
        cout << "\n--- MENU ---\n";
        cout << "1. Add Car\n";
        cout << "2. Add Electric Car\n";
        cout << "3. Add Sports Car\n";
        cout << "4. Add Sedan\n";
        cout << "5. Add SUV\n";
        cout << "6. Add Flying Car\n";
        cout << "7. View All Vehicles\n";
        cout << "8. Search Vehicle by ID\n";
        cout << "9. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        switch(choice) {
            case 1: {
                cout << "\n--- Add Car ---\n";
                cout << "Enter Vehicle ID: ";
                getline(cin, id);
                cout << "Enter Manufacturer: ";
                getline(cin, manu);
                cout << "Enter Model: ";
                getline(cin, model);
                cout << "Enter Year: ";
                cin >> year;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Enter Fuel Type: ";
                getline(cin, fuel);
                
                registry.addVehicle(new Car(id, manu, model, year, fuel));
                cout << "\nCar added successfully!\n";
                break;
            }
            case 2: {
                double capacity;
                cout << "\n--- Add Electric Car ---\n";
                cout << "Enter Vehicle ID: ";
                getline(cin, id);
                cout << "Enter Manufacturer: ";
                getline(cin, manu);
                cout << "Enter Model: ";
                getline(cin, model);
                cout << "Enter Year: ";
                cin >> year;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Enter Fuel Type: ";
                getline(cin, fuel);
                cout << "Enter Battery Capacity (kWh): ";
                cin >> capacity;
                
                registry.addVehicle(new ElectricCar(id, manu, model, year, fuel, capacity));
                cout << "\nElectric Car added successfully!\n";
                break;
            }
            case 3: {
                double capacity, speed;
                cout << "\n--- Add Sports Car ---\n";
                cout << "Enter Vehicle ID: ";
                getline(cin, id);
                cout << "Enter Manufacturer: ";
                getline(cin, manu);
                cout << "Enter Model: ";
                getline(cin, model);
                cout << "Enter Year: ";
                cin >> year;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Enter Fuel Type: ";
                getline(cin, fuel);
                cout << "Enter Battery Capacity (kWh): ";
                cin >> capacity;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Enter Top Speed (km/h): ";
                cin >> speed;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                registry.addVehicle(new SportsCar(id, manu, model, year, fuel, capacity, speed));
                cout << "\nSports Car added successfully!\n";
                break;
            }
            case 4: {
                double trunk;
                cout << "\n--- Add Sedan ---\n";
                cout << "Enter Vehicle ID: ";
                getline(cin, id);
                cout << "Enter Manufacturer: ";
                getline(cin, manu);
                cout << "Enter Model: ";
                getline(cin, model);
                cout << "Enter Year: ";
                cin >> year;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Enter Fuel Type: ";
                getline(cin, fuel);
                cout << "Enter Trunk Capacity (L): ";
                cin >> trunk;
                
                registry.addVehicle(new Sedan(id, manu, model, year, fuel, trunk));
                cout << "\nSedan added successfully!\n";
                break;
            }
            case 5: {
                int awd;
                cout << "\n--- Add SUV ---\n";
                cout << "Enter Vehicle ID: ";
                getline(cin, id);
                cout << "Enter Manufacturer: ";
                getline(cin, manu);
                cout << "Enter Model: ";
                getline(cin, model);
                cout << "Enter Year: ";
                cin >> year;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Enter Fuel Type: ";
                getline(cin, fuel);
                cout << "Four Wheel Drive (1 for Yes, 0 for No): ";
                cin >> awd;
                
                registry.addVehicle(new SUV(id, manu, model, year, fuel, awd == 1));
                cout << "\nSUV added successfully!\n";
                break;
            }
            case 6: {
                double range, wings;
                cout << "\n--- Add Flying Car ---\n";
                cout << "Enter Vehicle ID: ";
                getline(cin, id);
                cout << "Enter Manufacturer: ";
                getline(cin, manu);
                cout << "Enter Model: ";
                getline(cin, model);
                cout << "Enter Year: ";
                cin >> year;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Enter Fuel Type: ";
                getline(cin, fuel);
                cout << "Enter Flight Range (km): ";
                cin >> range;
                cout << "Enter Wing Span (m): ";
                cin >> wings;
                
                registry.addVehicle(new FlyingCar(id, manu, model, year, fuel, range, wings));
                cout << "\nFlying Car added successfully!\n";
                break;
            }
            case 7:
                registry.displayAll();
                break;
            case 8: {
                cout << "\nEnter Vehicle ID to search: ";
                getline(cin, id);
                Vehicle* v = registry.searchByID(id);
                if(v) {
                    cout << "\nVehicle Found:\n";
                    cout << string(40, '-') << endl;
                    v->display();
                } else {
                    cout << "\nVehicle with ID '" << id << "' not found.\n";
                }
                break;
            }
            case 9:
                cout << "\nExiting system. Goodbye!\n";
                break;
            default:
                cout << "\nInvalid choice! Please try again.\n";
        }
    } while(choice != 9);
    
    return 0;
}