#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm> // For std::find

using namespace std;

// Define color codes for terminal output
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"

// Structure for Room
struct Room {
    int roomNumber;
    int bedsAvailable; // Each room has 3 beds initially
    Room(int number) : roomNumber(number), bedsAvailable(3) {}
};

// Structure for Floor
struct Floor {
    int floorNumber;
    vector<Room> rooms;
    Floor(int number, int numRooms) : floorNumber(number) {
        // Initialize rooms for this floor, each floor gets numRooms
        for (int i = 0; i < numRooms; ++i) {
            rooms.push_back(Room(i + 1)); // Room numbers start from 1
        }
    }
};

// Structure for Hostel
struct Hostel {
    string branchName;
    vector<Floor> floors;
    Hostel(string branch) : branchName(branch) {}

    // Add a floor to the hostel
    void addFloor(int floorNumber, int numRooms) {
        floors.push_back(Floor(floorNumber, numRooms));
    }

    // Find and allot a room to a student
    bool allotRoom(int floorNumber, int roomNumber) {
        for (auto &floor : floors) {
            if (floor.floorNumber == floorNumber) {
                for (auto &room : floor.rooms) {
                    if (room.roomNumber == roomNumber) {
                        if (room.bedsAvailable > 0) {
                            room.bedsAvailable--;
                            cout << "Room " << roomNumber << " on Floor " << floorNumber << " has been allotted. Remaining beds: " << room.bedsAvailable << endl;
                            return true;
                        } else {
                            cout << "Room " << roomNumber << " on Floor " << floorNumber << " is already full." << endl;
                            return false;
                        }
                    }
                }
            }
        }
        cout << "Room not found!" << endl;
        return false;
    }

    // Display hostel status in a table format
    void displayHostelStatus() {
        cout << BLUE << "Hostel Status for Branch: " << branchName << RESET << endl;
        for (auto &floor : floors) {
            cout << "Floor " << floor.floorNumber << "\n";
            cout << "------------------------------------------------------\n";
            cout << "| Room No | Beds Available | Beds Occupied |\n";
            cout << "------------------------------------------------------\n";
            for (auto &room : floor.rooms) {
                int occupied = 3 - room.bedsAvailable;
                cout << "| " << room.roomNumber << "      | " << room.bedsAvailable << "             | " << occupied << "              |\n";
            }
            cout << "------------------------------------------------------\n";
        }
    }
};

// Base class for User
class User {
protected:
    string name;
    string role; // admin or student

public:
    User(string n, string r) : name(n), role(r) {}

    virtual void menu() = 0;
    virtual void viewMenu() = 0;
};

// Admin class inherits from User
class Admin : public User {
private:
    vector<Hostel> hostels;
    string password = "1234";

public:
    Admin(string n) : User(n, "Admin") {}

    // Login function for admin with password
    bool login() {
        string enteredPassword;
        cout << "Enter admin password: ";
        cin >> enteredPassword;
        if (enteredPassword == password) {
            cout << GREEN << "Login successful!" << RESET << endl;
            return true;
        } else {
            cout << RED << "Invalid password!" << RESET << endl;
            return false;
        }
    }

    // Add a hostel for a specific branch
    void addHostel(string branchName) {
        hostels.push_back(Hostel(branchName));
        cout << "Hostel for " << branchName << " branch has been added.\n";
    }

    // Add a floor to a specific hostel
    void addFloorToHostel(string branchName, int floorNumber, int numRooms) {
        auto it = find_if(hostels.begin(), hostels.end(), [&](Hostel &h) { return h.branchName == branchName; });
        if (it != hostels.end()) {
            it->addFloor(floorNumber, numRooms);
            cout << "Floor " << floorNumber << " with " << numRooms << " rooms added to " << branchName << " hostel.\n";
        } else {
            cout << "Hostel for " << branchName << " not found.\n";
        }
    }

    // Allot room to a student in a specific hostel
    void allotRoomToStudent(string branchName, int floorNumber, int roomNumber) {
        auto it = find_if(hostels.begin(), hostels.end(), [&](Hostel &h) { return h.branchName == branchName; });
        if (it != hostels.end()) {
            it->allotRoom(floorNumber, roomNumber);
        } else {
            cout << "Hostel for " << branchName << " not found.\n";
        }
    }

    // Display hostel status
    void displayHostelStatus(string branchName) {
        auto it = find_if(hostels.begin(), hostels.end(), [&](Hostel &h) { return h.branchName == branchName; });
        if (it != hostels.end()) {
            it->displayHostelStatus();
        } else {
            cout << "Hostel for " << branchName << " not found.\n";
        }
    }

    void menu() override {
        cout << BLUE << "Admin Menu:" << RESET << "\n";
        cout << "1. Add Hostel\n";
        cout << "2. Add Floor to Hostel\n";
        cout << "3. Allot Room to Student\n";
        cout << "4. View Hostel Status\n";
        cout << "5. Return to Main Menu\n";
        cout << "6. Save Data\n";
        cout << "7. Exit\n";
    }

    void viewMenu() override {
        // Admin food menu can be shown here
    }

    // Save hostel data to file
    void saveToFile() {
        ofstream outFile("hostel_data.txt", ios::app);
        for (auto &hostel : hostels) {
            outFile << "Hostel Branch: " << hostel.branchName << "\n";
            for (auto &floor : hostel.floors) {
                outFile << "Floor " << floor.floorNumber << "\n";
                for (auto &room : floor.rooms) {
                    outFile << "Room " << room.roomNumber << " - " << room.bedsAvailable << " beds available\n";
                }
            }
        }
        outFile.close();
        cout << "Data saved to file.\n";
    }
};

// Student class inherits from User
class Student : public User {
private:
    string branch;
    int floor;
    int roomNumber;

public:
    Student(string n) : User(n, "Student") {}

    void setStudentDetails(string branchName, int floorNum, int roomNum) {
        branch = branchName;
        floor = floorNum;
        roomNumber = roomNum;
        cout << "Student details updated: Branch: " << branch << ", Floor: " << floor << ", Room Number: " << roomNumber << endl;
    }

    void menu() override {
        cout << BLUE << "Student Menu:" << RESET << "\n";
        cout << "1. View Food Menu\n";
        cout << "2. Register Complaint\n";
        cout << "3. Exit\n";
    }

    void viewMenu() override {
        // Food menu will be displayed here for the student
        cout << BLUE << "Food Menu (Weekly):" << RESET << "\n";
        cout << "--------------------------------------------------\n";
        cout << "| Day       | Menu Item                         |\n";
        cout << "--------------------------------------------------\n";
        cout << "| Monday    | Sandwich & Juice                  |\n";
        cout << "| Tuesday   | Pizza & Salad                     |\n";
        cout << "| Wednesday | Pasta                             |\n";
        cout << "| Thursday  | Rice & Curry                      |\n";
        cout << "| Friday    | Burger & Fries                    |\n";
        cout << "| Saturday  | Spaghetti                         |\n";
        cout << "| Sunday    | Biryani                           |\n";
        cout << "--------------------------------------------------\n";
    }

    void registerComplaint() {
        int complaintType;
        cout << "Enter Complaint Type:\n";
        cout << "1. Room Issues (Fan, Light, Furniture)\n";
        cout << "2. Personal Issues\n";
        cout << "Enter choice: ";
        cin >> complaintType;

        if (complaintType == 1) {
            string issue;
            cout << "Enter room issue (Fan/Light/Furniture): ";
            cin >> issue;
            cout << "Complaint registered: " << issue << "\n";
        } else if (complaintType == 2) {
            string personalIssue;
            cout << "Describe your personal issue: ";
            cin.ignore();  // To ignore the newline character left by previous input
            getline(cin, personalIssue);
            cout << "Complaint registered: " << personalIssue << "\n";
        } else {
            cout << RED << "Invalid choice for complaint type." << RESET << endl;
        }
    }
};

// Main function
int main() {
    // Print system title
    cout << MAGENTA << "========================" << RESET << endl;
    cout << MAGENTA << "HOSTEL MANAGEMENT SYSTEM" << RESET << endl;
    cout << MAGENTA << "========================" << RESET << endl;

    Admin admin("Admin1");
    Student student("Student1");

    bool isAdminLoggedIn = false;
    bool isStudentLoggedIn = false;
    int choice;

    while (true) {
        cout << "Welcome! Please select your role:\n";
        cout << "1. Admin\n";
        cout << "2. Student\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            isAdminLoggedIn = true;
            if (admin.login()) {  // Admin login authentication
                while (true) {
                    admin.menu();
                    cout << "Enter choice: ";
                    cin >> choice;

                    if (choice == 1) {
                        string branchName;
                        cout << "Enter branch name for hostel: ";
                        cin >> branchName;
                        admin.addHostel(branchName);
                    } else if (choice == 2) {
                        string branchName;
                        int floorNumber, numRooms;
                        cout << "Enter branch name for the hostel: ";
                        cin >> branchName;
                        cout << "Enter floor number: ";
                        cin >> floorNumber;
                        cout << "Enter number of rooms on this floor: ";
                        cin >> numRooms;
                        admin.addFloorToHostel(branchName, floorNumber, numRooms);
                    } else if (choice == 3) {
                        string branchName;
                        int floorNumber, roomNumber;
                        cout << "Enter branch name: ";
                        cin >> branchName;
                        cout << "Enter floor number: ";
                        cin >> floorNumber;
                        cout << "Enter room number to allot: ";
                        cin >> roomNumber;
                        admin.allotRoomToStudent(branchName, floorNumber, roomNumber);
                    } else if (choice == 4) {
                        string branchName;
                        cout << "Enter branch name to view status: ";
                        cin >> branchName;
                        admin.displayHostelStatus(branchName);
                    } else if (choice == 5) {
                        cout << "Returning to the main menu...\n";
                        break; // Exit admin menu and return to main menu
                    } else if (choice == 6) {
                        admin.saveToFile();  // Save data to file
                    } else if (choice == 7) {
                        cout << "Exiting program.\n";
                        return 0;
                    }
                }
            }
        } else if (choice == 2) {
            isStudentLoggedIn = true;
            string branchName;
            int floorNum, roomNum;

            // Ask for student details to book a room
            cout << "Enter your branch name: ";
            cin >> branchName;
            cout << "Enter floor number: ";
            cin >> floorNum;
            cout << "Enter room number: ";
            cin >> roomNum;

            student.setStudentDetails(branchName, floorNum, roomNum);

            while (true) {
                student.menu();
                cout << "Enter choice: ";
                cin >> choice;

                if (choice == 1) {
                    student.viewMenu();
                } else if (choice == 2) {
                    student.registerComplaint();  // Handle complaint registration
                } else if (choice == 3) {
                    cout << "Student logged out.\n";
                    break; // Exiting the program
                }
            }
        } else {
            cout << RED << "Invalid choice! Exiting...\n" << RESET;
            break; // Exit the loop and terminate the program if invalid choice
        }
    }

    return 0;
}