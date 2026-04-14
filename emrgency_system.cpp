#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <string>
#include <thread>
#include <chrono>

using namespace std;

// Structure to represent an emergency request
struct Emergency {
    int id;
    string type; // Fire, Medical, Police
    string priority; // High, Medium, Low
    string zone;
    int time; // simulated time in minutes
};

// Class to manage the emergency system
class EmergencySystem {
private:
    // Fixed-size array for predefined zones
    string zones[5] = {"North", "South", "East", "West", "Central"};
    // Vector to store all emergency requests dynamically
    vector<Emergency> allRequests;
    // Queue for managing incoming requests (FIFO)
    queue<Emergency> pending;
    // Stack for history of processed requests (LIFO)
    stack<Emergency> processed;
    int nextId = 1; // Auto-increment ID
    int currentTime = 0; // Simulated time counter

public:
    // Display the main menu
    void displayMenu() {
        cout << "\n=== Smart Emergency Response System ===\n";
        cout << "1. Add Emergency Request\n";
        cout << "2. View All Requests\n";
        cout << "3. Process Next Request\n";
        cout << "4. Undo Last Processed Request\n";
        cout << "5. Search Request (Linear Search)\n";
        cout << "6. Search Request (Binary Search)\n";
        cout << "7. Sort Requests by Priority\n";
        cout << "8. Sort Requests by ID\n";
        cout << "9. Sort Requests by Time\n";
        cout << "10. Exit\n";
        cout << "Choose an option: ";
    }

    // Add a new emergency request
    void addRequest() {
        Emergency e;
        e.id = nextId++;
        cout << "Select Type:\n1. Fire\n2. Medical\n3. Police\nChoice: ";
        int t;
        cin >> t;
        if (t == 1) e.type = "Fire";
        else if (t == 2) e.type = "Medical";
        else e.type = "Police";
        
        cout << "Select Priority:\n1. High\n2. Medium\n3. Low\nChoice: ";
        int p;
        cin >> p;
        if (p == 1) e.priority = "High";
        else if (p == 2) e.priority = "Medium";
        else e.priority = "Low";
        
        cout << "Select Zone:\n";
        for (int i = 0; i < 5; i++) {
            cout << i + 1 << ". " << zones[i] << endl;
        }
        int z;
        cin >> z;
        e.zone = zones[z - 1];
        e.time = currentTime++;
        
        // Add to vector and queue
        allRequests.push_back(e);
        pending.push(e);
        cout << "Emergency Added Successfully\n";
    }

    // View all requests
    void viewAll() {
        if (allRequests.empty()) {
            cout << "No requests available.\n";
            return;
        }
        cout << "All Requests:\n";
        for (auto &r : allRequests) {
            cout << "ID: " << r.id << " | Type: " << r.type << " | Priority: " << r.priority 
                 << " | Zone: " << r.zone << " | Time: " << r.time << endl;
        }
    }

    // Process the next request from queue
    void processNext() {
        if (pending.empty()) {
            cout << "No pending requests to process.\n";
            return;
        }
        Emergency e = pending.front();
        pending.pop();
        processed.push(e);
        cout << "Processing Request ID: " << e.id << " - " << e.type << " in " << e.zone << endl;
        // Simulate processing delay
        this_thread::sleep_for(chrono::seconds(1));
        cout << "Request processed successfully.\n";
    }

    // Undo the last processed request
    void undoLast() {
        if (processed.empty()) {
            cout << "No processed requests to undo.\n";
            return;
        }
        Emergency e = processed.top();
        processed.pop();
        pending.push(e);
        cout << "Undo Successful. Request ID " << e.id << " moved back to pending.\n";
    }

    // Linear search for a request by ID
    void searchLinear(int id) {
        for (auto &r : allRequests) {
            if (r.id == id) {
                cout << "Found via Linear Search: ID: " << r.id << " | Type: " << r.type 
                     << " | Priority: " << r.priority << " | Zone: " << r.zone << " | Time: " << r.time << endl;
                return;
            }
        }
        cout << "Request not found.\n";
    }

    // Binary search for a request by ID (requires sorted list)
    void searchBinary(int id) {
        // Create a sorted copy for binary search
        vector<Emergency> sorted = allRequests;
        selectionSort(sorted, 0); // Sort by ID
        int low = 0, high = sorted.size() - 1;
        while (low <= high) {
            int mid = (low + high) / 2;
            if (sorted[mid].id == id) {
                cout << "Found via Binary Search: ID: " << sorted[mid].id << " | Type: " << sorted[mid].type 
                     << " | Priority: " << sorted[mid].priority << " | Zone: " << sorted[mid].zone << " | Time: " << sorted[mid].time << endl;
                return;
            } else if (sorted[mid].id < id) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        cout << "Request not found.\n";
    }

    // Sort requests by priority using bubble sort
    void sortByPriority() {
        bubbleSort(allRequests);
        cout << "Requests sorted by Priority (High to Low):\n";
        viewAll();
    }

    // Sort requests by ID using selection sort
    void sortByID() {
        selectionSort(allRequests, 0);
        cout << "Requests sorted by ID:\n";
        viewAll();
    }

    // Sort requests by time using selection sort
    void sortByTime() {
        selectionSort(allRequests, 1);
        cout << "Requests sorted by Time:\n";
        viewAll();
    }

private:
    // Bubble sort implementation for priority
    void bubbleSort(vector<Emergency> &vec) {
        int n = vec.size();
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                int p1 = priorityToInt(vec[j].priority);
                int p2 = priorityToInt(vec[j + 1].priority);
                if (p1 < p2) { // Swap to sort high priority first
                    swap(vec[j], vec[j + 1]);
                }
            }
        }
    }

    // Selection sort implementation for ID or time
    void selectionSort(vector<Emergency> &vec, int by) { // 0 for ID, 1 for time
        int n = vec.size();
        for (int i = 0; i < n - 1; i++) {
            int minIdx = i;
            for (int j = i + 1; j < n; j++) {
                if ((by == 0 && vec[j].id < vec[minIdx].id) ||
                    (by == 1 && vec[j].time < vec[minIdx].time)) {
                    minIdx = j;
                }
            }
            swap(vec[i], vec[minIdx]);
        }
    }

    // Convert priority string to int for comparison
    int priorityToInt(string p) {
        if (p == "High") return 3;
        if (p == "Medium") return 2;
        return 1;
    }
};

int main() {
    EmergencySystem sys;
    int choice;
    do {
        sys.displayMenu();
        cin >> choice;
        switch (choice) {
            case 1:
                sys.addRequest();
                break;
            case 2:
                sys.viewAll();
                break;
            case 3:
                sys.processNext();
                break;
            case 4:
                sys.undoLast();
                break;
            case 5: {
                cout << "Enter ID to search: ";
                int id;
                cin >> id;
                sys.searchLinear(id);
                break;
            }
            case 6: {
                cout << "Enter ID to search: ";
                int id;
                cin >> id;
                sys.searchBinary(id);
                break;
            }
            case 7:
                sys.sortByPriority();
                break;
            case 8:
                sys.sortByID();
                break;
            case 9:
                sys.sortByTime();
                break;
            case 10:
                cout << "Exiting the system...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 10);
    return 0;
}