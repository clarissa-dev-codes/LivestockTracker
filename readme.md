# Livestock Tracker
**University Final Project | C++ Data Management System**

## Project Overview
This application is a terminal-based database system designed to track, manage, and audit livestock assets across four core categories: Chickens, Cows, Goats, and Horses. 

The system reads configuration and historical records from flat text files, processes operations in memory using clean C++ object-oriented logic, and commits updates back to disk for permanent storage.

---

## Technical Highlights & Cross-Platform Compatibility
* **Automated Line-Ending Conversion:** Windows and Linux handle text file line endings differently (CRLF vs LF). To ensure seamless cross-platform execution, the Makefile includes an automated build routine that converts data files to a Linux-friendly format without requiring manual user intervention.
* **Data Persistence:** Implemented robust file I/O handling to parse, manipulate, and save real-time state changes to static text files.

---

## Getting Started

### Prerequisites
* A C++ compiler (G++)
* Make utility

### Compilation & Execution
To compile the project and automatically handle the cross-platform file conversions, run:

```bash
make
./livestock_tracker
```

---

## Interactive Testing Scripts (Grading Guide)
To verify the application's full CRUD and data manipulation capabilities, the following test scenarios can be executed within the database interface:

### Horse Management (Status Updates)
* Locate **Metallic Boon** -> Update status to `Sold`
* Locate **Macs Little Dolly** -> Update status to `Deceased`
* Locate **Smart Lil Bugly** -> Transfer location to `Mikes`

### Goat Management (Record Additions & Logistics)
* Register **Belle's Triplets**:
  * Add **Harry** -> (Simulate logistical lifecycle by moving to `Sold`)
  * Add **Unknown 1** -> Move to `Deceased`
  * Add **Unknown 2** -> Move to `Deceased`

### Chicken Inventory Auditing
* Increment inventory by adding **4 Smokey Pearls**
* Update inventory by moving **2 Smokey Pearls** to `Deceased`
* Increment inventory by adding **1 Rhode Island (Purple)**
* Locate **Blaze** and **Red Black** -> Update status to `Deceased`

### Cattle Financial & Asset Updates
* Update inventory by moving **1 Heifer** to `Sold`
* Update inventory by moving **1 Registered Heifer** to `Deceased`
* Bulk update inventory by moving **9 Bulls** to `Sold`

---
*Developed as a Final Academic Project by Clarissa Edwards — Due Date: 12/11/2025*
