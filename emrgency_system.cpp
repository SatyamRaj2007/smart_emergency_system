#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <string>
#include <iomanip>

using namespace std;

// Structure to represent an emergency request
struct Emergency {
    int id;
    string type; // Fire, Medical, Police
    string priority; // High, Medium, Low
    string zone;
    int timestamp; // simulated timestamp
};

// Class to manage the emergency system
class SmartEmergencyResponseSystem {
private:
    // Fixed-size array for predefined zones
    string zones[5] = {"North", "South", "East", "West", "Central"};
    // Vector to store all emergency requests dynamically
    vector<Emergency> allRequests;
    // Queue to store IDs of pending requests (FIFO)
    queue<int> pendingQueue;
    // Stack to store processed requests (LIFO)
    stack<Emergency> processedStack;
    int nextId = 1; // Auto-increment ID
    int currentTimestamp = 0; // Simulated timestamp counter

public:
    // Display the main menu
    void displayMenu() {
        cout << "\n=== Smart Emergency Response System (SERS) ===\n";
        cout << "1. Add Emergency Request\n";
        cout << "2. View All Requests\n";
        cout << "3. Process Next Request\n";
        cout << "4. Undo Last Processed Request\n";
        cout << "5. Search Request (Linear Search)\n";
        cout << "6. Search Request (Binary Search)\n";
        cout << "7. Sort Requests by Priority\n";
        cout << "8. Sort Requests by ID\n";
        cout << "9. Sort Requests by Timestamp\n";
        cout << "10. Display Pending Queue\n";
        cout << "11. Exit\n";
        cout << "Choose an option: ";
    }

    // Add a new emergency request
    void addRequest() {
        Emergency e;
        e.id = nextId++;
        cout << "Select Type:\n1. Fire\n2. Medical\n3. Police\nChoice: ";
        int t;
        cin >> t;
        while (t < 1 || t > 3) {
            cout << "Invalid choice. Enter 1-3: ";
            cin >> t;
        }
        if (t == 1) e.type = "Fire";
        else if (t == 2) e.type = "Medical";
        else e.type = "Police";
        
        cout << "Select Priority:\n1. High\n2. Medium\n3. Low\nChoice: ";
        int p;
        cin >> p;
        while (p < 1 || p > 3) {
            cout << "Invalid choice. Enter 1-3: ";
            cin >> p;
        }
        if (p == 1) e.priority = "High";
        else if (p == 2) e.priority = "Medium";
        else e.priority = "Low";
        
        cout << "Select Zone:\n";
        for (int i = 0; i < 5; i++) {
            cout << i + 1 << ". " << zones[i] << endl;
        }
        cout << "Choice: ";
        int z;
        cin >> z;
        while (z < 1 || z > 5) {
            cout << "Invalid choice. Enter 1-5: ";
            cin >> z;
        }
        e.zone = zones[z - 1];
        e.timestamp = currentTimestamp++;
        
        // Add to vector and queue (store ID only in queue)
        allRequests.push_back(e);
        pendingQueue.push(e.id);
        cout << "\nEmergency Request Added Successfully!\n";
        cout << "---------------------------------------\n";
        cout << "ID        : " << e.id << endl;
        cout << "Type      : " << e.type << endl;
        cout << "Priority  : " << e.priority << endl;
        cout << "Zone      : " << e.zone << endl;
        cout << "Timestamp : " << e.timestamp << endl;
        cout << "---------------------------------------\n";
    }

    // View all requests in tabular format
    void viewAll() {
        if (allRequests.empty()) {
            cout << "No requests available.\n";
            return;
        }
        cout << left << setw(5) << "ID" << setw(10) << "Type" << setw(10) << "Priority" 
             << setw(10) << "Zone" << setw(12) << "Timestamp" << endl;
        cout << string(47, '-') << endl;
        for (auto &r : allRequests) {
            cout << left << setw(5) << r.id << setw(10) << r.type << setw(10) << r.priority 
                 << setw(10) << r.zone << setw(12) << r.timestamp << endl;
        }
    }

    // Process the next request from queue
    void processRequest() {
        if (pendingQueue.empty()) {
            cout << "\033[31mNo pending requests to process.\033[0m\n";
            return;
        }
        int id = pendingQueue.front();
        pendingQueue.pop();
        // Find the request in vector
        Emergency e;
        for (auto &r : allRequests) {
            if (r.id == id) {
                e = r;
                break;
            }
        }
        processedStack.push(e);
        cout << "\033[34mProcessing Request ID: " << e.id << " - " << e.type << " in " << e.zone << "\033[0m\n";
        // Simulate processing delay (removed for compatibility)
        cout << "\033[32mRequest processed successfully.\033[0m\n";
    }

    // Undo the last processed request
    void undoProcess() {
        if (processedStack.empty()) {
            cout << "\033[31mNo processed requests to undo.\033[0m\n";
            return;
        }
        Emergency e = processedStack.top();
        processedStack.pop();
        pendingQueue.push(e.id);
        cout << "\033[33mUndo Successful. Request ID " << e.id << " moved back to pending.\033[0m\n";
    }

    // Linear search for a request by ID, show comparisons
    void linearSearch(int id) {
        int comparisons = 0;
        for (auto &r : allRequests) {
            comparisons++;
            if (r.id == id) {
                cout << "\033[36mFound via Linear Search (Comparisons: " << comparisons << "):\033[0m\n";
                displaySingleRequest(r);
                return;
            }
        }
        cout << "\033[31mRequest not found after " << comparisons << " comparisons.\033[0m\n";
    }

    // Binary search for a request by ID after sorting
    void binarySearch(int id) {
        // Create a sorted copy by ID
        vector<Emergency> sorted = allRequests;
        selectionSort(sorted, 0); // Sort by ID
        int low = 0, high = sorted.size() - 1;
        int comparisons = 0;
        while (low <= high) {
            comparisons++;
            int mid = (low + high) / 2;
            if (sorted[mid].id == id) {
                cout << "\033[36mFound via Binary Search (Comparisons: " << comparisons << "):\033[0m\n";
                displaySingleRequest(sorted[mid]);
                return;
            } else if (sorted[mid].id < id) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        cout << "\033[31mRequest not found after " << comparisons << " comparisons.\033[0m\n";
    }

    // Sort requests by priority using bubble sort
    void bubbleSortPriority() {
        cout << "Before sorting by Priority:\n";
        viewAll();
        bubbleSort(allRequests);
        cout << "After sorting by Priority (High to Low):\n";
        viewAll();
    }

    // Sort requests by ID using selection sort
    void selectionSortID() {
        cout << "Before sorting by ID:\n";
        viewAll();
        selectionSort(allRequests, 0);
        cout << "After sorting by ID:\n";
        viewAll();
    }

    // Sort requests by timestamp using selection sort
    void selectionSortTimestamp() {
        cout << "Before sorting by Timestamp:\n";
        viewAll();
        selectionSort(allRequests, 1);
        cout << "After sorting by Timestamp:\n";
        viewAll();
    }

    // Display pending queue
    void displayPendingQueue() {
        if (pendingQueue.empty()) {
            cout << "Pending queue is empty.\n";
            return;
        }
        cout << "Pending Queue (IDs): ";
        queue<int> temp = pendingQueue;
        while (!temp.empty()) {
            cout << temp.front() << " ";
            temp.pop();
        }
        cout << "\nQueue Size: " << pendingQueue.size() << endl;
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

    // Selection sort implementation for ID or timestamp
    void selectionSort(vector<Emergency> &vec, int by) { // 0 for ID, 1 for timestamp
        int n = vec.size();
        for (int i = 0; i < n - 1; i++) {
            int minIdx = i;
            for (int j = i + 1; j < n; j++) {
                if ((by == 0 && vec[j].id < vec[minIdx].id) ||
                    (by == 1 && vec[j].timestamp < vec[minIdx].timestamp)) {
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

    // Display a single request in tabular format
    void displaySingleRequest(const Emergency &r) {
        cout << left << setw(5) << "ID" << setw(10) << "Type" << setw(10) << "Priority" 
             << setw(10) << "Zone" << setw(12) << "Timestamp" << endl;
        cout << string(47, '-') << endl;
        cout << left << setw(5) << r.id << setw(10) << r.type << setw(10) << r.priority 
             << setw(10) << r.zone << setw(12) << r.timestamp << endl;
    }
};

int main() {
    SmartEmergencyResponseSystem sers;
    int choice;
    do {
        sers.displayMenu();
        cin >> choice;
        switch (choice) {
            case 1:
                sers.addRequest();
                break;
            case 2:
                sers.viewAll();
                break;
            case 3:
                sers.processRequest();
                break;
            case 4:
                sers.undoProcess();
                break;
            case 5: {
                cout << "Enter ID to search: ";
                int id;
                cin >> id;
                sers.linearSearch(id);
                break;
            }
            case 6: {
                cout << "Enter ID to search: ";
                int id;
                cin >> id;
                sers.binarySearch(id);
                break;
            }
            case 7:
                sers.bubbleSortPriority();
                break;
            case 8:
                sers.selectionSortID();
                break;
            case 9:
                sers.selectionSortTimestamp();
                break;
            case 10:
                sers.displayPendingQueue();
                break;
            case 11:
                cout << "\033[35mExiting the system...\033[0m\n";
                break;
            default:
                cout << "\033[31mInvalid choice. Please try again.\033[0m\n";
        }
    } while (choice != 11);
    return 0;
}