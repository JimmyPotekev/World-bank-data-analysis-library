# World Bank Time-Series Data Management (C++)

## Overview
This C++ software library efficiently processes, stores, and analyzes **real-world economic and social datasets** from the World Bank. The project handles 18,000+ CSV records across 1,500 unique indicators and supports time-series data spanning 60+ years for various countries.

This implementation is based on Parts 1 and 2 of the full project, focusing on storing, retrieving, and analyzing time-series data per country using linked lists for dynamic memory management and efficient operations.

## Features
- Efficient Data Storage: Uses linked lists to store and manage multiple time-series data per country, preserving dataset order.
- Data Operations: Supports `LOAD`, `ADD`, `UPDATE`, `DELETE`, and `LIST` operations for time-series data retrieval and modification.
- Statistical Analysis: Implements key functions such as **mean calculation, monotonicity checks, and best-fit line estimation (linear regression)
- Optimized Memory Management: Prevents memory leaks and dangling pointers using dynamic allocation and structured deallocation.

## Technologies Used
- C++ (Standard Library: iostream, string, fstream) for file processing and data structures
- Linked Lists for managing multiple time-series records per country
- Dynamic Memory Management** to ensure scalable processing of large datasets
- CSV Parsing for reading and processing structured World Bank data

## Installation & Setup
1. Clone the Repository:
   ```bash
   git clone <repository-url>
   cd <repository-folder>
   ```
2. Compile the Code:
   ```bash
   g++ -std=c++17 main.cpp country.cpp TimeSeries.cpp -o program
   ```
3. Run the Program:
   ```bash
   ./program < input.txt
   ```

## Usage
The program processes commands via standard input, simulating a database for time-series data. Example commands:
```
LOAD Egypt data.csv
ADD EG.FIN.INCL.ZS 2000 45.6
UPDATE EG.FIN.INCL.ZS 2000 50.2
LIST Egypt
DELETE EG.FIN.INCL.ZS
```
- `LOAD <country> <file>` – Loads time-series data from a CSV file.
- `ADD <series_code> <year> <value>` – Adds a new data point.
- `UPDATE <series_code> <year> <value>` – Updates an existing entry.
- `LIST <country>` – Lists all time series stored for a country.
- `DELETE <series_code>` – Removes a time series.

## Runtime Analysis
| Operation        | Complexity |
|-----------------|------------|
| `LOAD`          | O(N) |
| `ADD`           | O(N) |
| `UPDATE`        | O(N) |
| `DELETE`        | O(N) |
| `LIST`          | O(N) |
| `BIGGEST`       | O(N) |

(N = number of time-series records for a country)

## Future Work (Next Parts)
- Implementing Binary Search Trees (BSTs) for faster `O(log N)` lookups.
- Optimizing indexing with hash maps.
- Expanding dataset relationships with graphs for country-based analysis.



