#include <iostream>
#include <cstring>
#include <iomanip>
using namespace std;

// Train Class
class Train {
private:
    int trainNumber;
    char trainName[50];
    char source[50];
    char destination[50];
    char trainTime[10];
    static int trainCount;

public:
    // Default Constructor
    Train() {
        trainNumber = 0;
        strcpy(trainName, "");
        strcpy(source, "");
        strcpy(destination, "");
        strcpy(trainTime, "");
        trainCount++;
    }

    // Parameterized Constructor
    Train(int num, const char* name, const char* src, const char* dest, const char* time) {
        trainNumber = num;
        strcpy(trainName, name);
        strcpy(source, src);
        strcpy(destination, dest);
        strcpy(trainTime, time);
        trainCount++;
    }

    // Destructor
    ~Train() {
        trainCount--;
    }

    // Getters
    int getTrainNumber() const {
        return trainNumber;
    }

    const char* getTrainName() const {
        return trainName;
    }

    const char* getSource() const {
        return source;
    }

    const char* getDestination() const {
        return destination;
    }

    const char* getTrainTime() const {
        return trainTime;
    }

    // Setters
    void setTrainNumber(int num) {
        trainNumber = num;
    }

    void setTrainName(const char* name) {
        strcpy(trainName, name);
    }

    void setSource(const char* src) {
        strcpy(source, src);
    }

    void setDestination(const char* dest) {
        strcpy(destination, dest);
    }

    void setTrainTime(const char* time) {
        strcpy(trainTime, time);
    }

    // Input train details
    void inputTrainDetails() {
        cout << "Enter Train Number: ";
        cin >> trainNumber;
        cin.ignore();
        
        cout << "Enter Train Name: ";
        cin.getline(trainName, 50);
        
        cout << "Enter Source: ";
        cin.getline(source, 50);
        
        cout << "Enter Destination: ";
        cin.getline(destination, 50);
        
        cout << "Enter Train Time: ";
        cin.getline(trainTime, 10);
    }

    // Display train details
    void displayTrainDetails() const {
        cout << "Train Number: " << trainNumber << endl;
        cout << "Train Name: " << trainName << endl;
        cout << "Source: " << source << endl;
        cout << "Destination: " << destination << endl;
        cout << "Train Time: " << trainTime << endl;
        cout << "------------------------" << endl;
    }

    // Static method to get train count
    static int getTrainCount() {
        return trainCount;
    }
};

// Initialize static member
int Train::trainCount = 0;

// RailwaySystem Class
class RailwaySystem {
private:
    Train trains[100];
    int totalTrains;

public:
    // Constructor
    RailwaySystem() {
        totalTrains = 0;
    }

    // Add initial trains
    void addInitialTrains() {
        // Train 1
        trains[totalTrains++] = Train(101, "Okha Express", "Surat", "Mumbai", "10 AM");
        
        // Train 2
        trains[totalTrains++] = Train(102, "Rajdhani Express", "Delhi", "Mumbai", "8 PM");
        
        // Train 3
        trains[totalTrains++] = Train(103, "Shatabdi Express", "Chennai", "Bangalore", "6 AM");
    }

    // Add new train record
    void addTrain() {
        if (totalTrains >= 100) {
            cout << "Cannot add more trains. Maximum limit reached!" << endl;
            return;
        }
        
        cout << "\n--- Add New Train Record ---" << endl;
        trains[totalTrains].inputTrainDetails();
        totalTrains++;
        cout << "Train added successfully!" << endl;
        cout << "Total trains in system: " << Train::getTrainCount() << endl;
    }

    // Display all train records
    void displayAllTrains() {
        if (totalTrains == 0) {
            cout << "No train records available!" << endl;
            return;
        }
        
        cout << "\n--- All Train Records ---" << endl;
        for (int i = 0; i < totalTrains; i++) {
            cout << "\nTrain " << (i + 1) << " details:" << endl;
            trains[i].displayTrainDetails();
        }
        cout << "Total trains in system: " << Train::getTrainCount() << endl;
    }

    // Search train by number
    void searchTrainByNumber(int number) {
        bool found = false;
        
        for (int i = 0; i < totalTrains; i++) {
            if (trains[i].getTrainNumber() == number) {
                cout << "\n--- Train Found ---" << endl;
                trains[i].displayTrainDetails();
                found = true;
                break;
            }
        }
        
        if (!found) {
            cout << "\nTrain with number " << number << " not found!" << endl;
        }
    }
};

// Main function with menu-driven approach
int main() {
    RailwaySystem system;
    int choice, trainNumber;
    
    // Add initial three train records
    system.addInitialTrains();
    
    do {
        cout << "\n--- Railway Reservation System Menu ---" << endl;
        cout << "1. Add New Train Record" << endl;
        cout << "2. Display All Train Records" << endl;
        cout << "3. Search Train by Number" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                system.addTrain();
                break;
                
            case 2:
                system.displayAllTrains();
                break;
                
            case 3:
                cout << "Enter Train Number to search: ";
                cin >> trainNumber;
                system.searchTrainByNumber(trainNumber);
                break;
                
            case 4:
                cout << "Exiting the system. Goodbye!" << endl;
                break;
                
            default:
                cout << "Invalid choice! Please enter a number between 1 and 4." << endl;
        }
    } while (choice != 4);
    
    return 0;
}