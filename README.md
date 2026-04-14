# Smart Emergency Response System (SERS)

A comprehensive C++ console application simulating a real-world emergency management system for handling ambulance, fire, and police requests. This project demonstrates advanced use of data structures and algorithms in a practical, modular design.

## Features

- **Emergency Request Management**: Add, view, process, and undo emergency requests with detailed attributes (ID, type, priority, zone, timestamp).
- **Data Structures**:
  - Fixed-size array for predefined zones (North, South, East, West, Central).
  - Vector for dynamic storage of all emergency records.
  - Queue (FIFO) for managing pending requests using IDs only.
  - Stack (LIFO) for processed requests to enable undo functionality.
- **Algorithms**:
  - Linear Search: Searches unsorted vector and displays comparison count.
  - Binary Search: Requires sorted data by ID, shows efficiency comparison.
  - Bubble Sort: Sorts requests by priority (High > Medium > Low).
  - Selection Sort: Sorts requests by ID or timestamp.
- **Menu-Driven Interface**: User-friendly console menu with options for all operations.
- **Edge Case Handling**: Validates inputs, handles empty collections, and provides meaningful feedback.
- **Formatted Output**: Tabular displays with proper alignment and color-coded messages.

## Requirements

- C++ Compiler (e.g., g++, clang++)
- Standard C++ libraries: iostream, vector, queue, stack, string, iomanip

## Compilation

To compile the program, use the following command in your terminal:

```bash
g++ emrgency_system.cpp -o sers
```

## Usage

Run the compiled executable:

```bash
./sers
```

Follow the on-screen menu to interact with the system:
1. Add Emergency Request
2. View All Requests
3. Process Next Request
4. Undo Last Processed Request
5. Search Request (Linear Search)
6. Search Request (Binary Search)
7. Sort Requests by Priority
8. Sort Requests by ID
9. Sort Requests by Timestamp
10. Display Pending Queue
11. Exit

## Project Structure

- `emrgency_system.cpp`: Main source file containing the complete application.
- `README.md`: This documentation file.

## Example Usage

```
=== Smart Emergency Response System (SERS) ===
1. Add Emergency Request
...
Choice: 1
Select Type:
1. Fire
2. Medical
3. Police
Choice: 3
Select Priority:
1. High
2. Medium
3. Low
Choice: 2
Select Zone:
1. North
2. South
3. East
4. West
5. Central
Choice: 5

🚨 Emergency Request Added Successfully!
---------------------------------------
ID        : 1
Type      : Police
Priority  : Medium
Zone      : Central
Timestamp : 1
---------------------------------------
```

## Contributing

Feel free to fork this repository and submit pull requests for improvements or additional features.

## License

This project is open-source and available under the MIT License.