# Smart Emergency Response System (SERS)

A comprehensive C++ console application simulating a real-world emergency response center for handling ambulance, fire, and police requests. This project demonstrates advanced use of core data structures and algorithms in a practical, modular design.

## Features

- **Emergency Request Management**: Add, view, process, and undo emergency requests with detailed attributes (ID, type, priority, zone, timestamp).
- **Data Structures**:
  - Fixed-size array for predefined zones (North, South, East, West, Central).
  - Vector for dynamic storage of all emergency records.
  - Queue (FIFO) for managing pending requests using IDs only.
  - Stack (LIFO) for processed requests to enable undo functionality.
- **Algorithms**:
  - Linear Search: Searches the unsorted vector and displays comparison count.
  - Binary Search: Uses sorted data by ID to demonstrate efficiency.
  - Bubble Sort: Sorts requests by priority (High > Medium > Low).
  - Selection Sort: Sorts requests by ID or timestamp.
- **Menu-Driven Interface**: User-friendly console menu for all operations.
- **Edge Case Handling**: Validates inputs, handles empty collections, and provides meaningful feedback.
- **Formatted Output**: Displays tables with alignment and colored messages in supported terminals.

## Requirements

- C++ Compiler (e.g., g++, clang++)
- Standard C++ libraries: iostream, vector, queue, stack, string, iomanip
- C++17 or later is recommended

## Compilation

To compile the program, use the following command in your terminal:

```bash
g++ emrgency_system.cpp -o sers
```

On Windows, you can run the executable as:

```powershell
.\sers.exe
```

## Usage

Run the compiled executable:

```bash
./sers
```

Then follow the on-screen menu:
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

```text
=== Smart Emergency Response System (SERS) ===
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
Choose an option: 1
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

 Emergency Request Added Successfully!
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