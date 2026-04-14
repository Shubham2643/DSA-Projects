#include <iostream>
#include <iomanip>
#include <string>

class TimeConverter {
private:
    int hours;
    int minutes;
    int seconds;
    long totalSeconds;

public:
    // Constructor
    TimeConverter() : hours(0), minutes(0), seconds(0), totalSeconds(0) {}

    // Convert seconds to HH:MM:SS format
    void convertSecondsToHMS(long sec) {
        totalSeconds = sec;
        hours = sec / 3600;
        sec %= 3600;
        minutes = sec / 60;
        seconds = sec % 60;
    }

    // Convert HH:MM:SS to seconds
    void convertHMSToSeconds(int h, int m, int s) {
        hours = h;
        minutes = m;
        seconds = s;
        totalSeconds = (h * 3600) + (m * 60) + s;
    }

    // Display time in HH:MM:SS format
    void displayHMS() {
        std::cout << "HH:MM:SS => " << hours << ":" 
                  << std::setfill('0') << std::setw(2) << minutes << ":" 
                  << std::setfill('0') << std::setw(2) << seconds << std::endl;
    }

    // Display total seconds
    void displaySeconds() {
        std::cout << "Total seconds: " << totalSeconds << std::endl;
    }

    // Get total seconds
    long getTotalSeconds() {
        return totalSeconds;
    }

    // Validate seconds input
    bool validateSeconds(long sec) {
        return sec >= 0;
    }

    // Validate time components
    bool validateTime(int h, int m, int s) {
        return (h >= 0 && h <= 23) && (m >= 0 && m <= 59) && (s >= 0 && s <= 59);
    }
};

int main() {
    TimeConverter converter;
    int choice;
    
    std::cout << "=================================" << std::endl;
    std::cout << "     TIME CONVERTER UTILITY      " << std::endl;
    std::cout << "=================================" << std::endl;
    
    do {
        std::cout << "\n--- MENU ---" << std::endl;
        std::cout << "1. Convert Seconds to HH:MM:SS" << std::endl;
        std::cout << "2. Convert HH:MM:SS to Seconds" << std::endl;
        std::cout << "3. Exit" << std::endl;
        std::cout << "Enter your choice (1-3): ";
        std::cin >> choice;
        
        switch(choice) {
            case 1: {
                long seconds;
                std::cout << "\n--- Seconds to HH:MM:SS Conversion ---" << std::endl;
                std::cout << "Enter total seconds: ";
                std::cin >> seconds;
                
                if(converter.validateSeconds(seconds)) {
                    converter.convertSecondsToHMS(seconds);
                    converter.displayHMS();
                } else {
                    std::cout << "Error: Invalid seconds input!" << std::endl;
                }
                break;
            }
            
            case 2: {
                int hours, minutes, seconds;
                std::cout << "\n--- HH:MM:SS to Seconds Conversion ---" << std::endl;
                std::cout << "Enter hours: ";
                std::cin >> hours;
                std::cout << "Enter minutes: ";
                std::cin >> minutes;
                std::cout << "Enter seconds: ";
                std::cin >> seconds;
                
                if(converter.validateTime(hours, minutes, seconds)) {
                    converter.convertHMSToSeconds(hours, minutes, seconds);
                    converter.displaySeconds();
                } else {
                    std::cout << "Error: Invalid time input! Hours (0-23), Minutes/Seconds (0-59)" << std::endl;
                }
                break;
            }
            
            case 3:
                std::cout << "\nThank you for using Time Converter. Goodbye!" << std::endl;
                break;
                
            default:
                std::cout << "\nInvalid choice! Please enter 1, 2, or 3." << std::endl;
        }
        
    } while(choice != 3);
    
    return 0;
}