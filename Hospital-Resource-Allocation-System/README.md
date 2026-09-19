# Smart Hospital & Resource Allocation System

A command-line Smart Hospital & Resource Allocation System developed in C. The program registers patients, assigns available ward beds, calculates bills, prioritizes emergency cases, and generates hospital performance reports.

## Features

- View doctor specialties, consultation fees, consultation times, and daily patient caps.
- View hospital wards, daily bed rates, and bed capacities.
- Register patients with name, age, emergency level, specialty, and admission details.
- Assign the first available bed in a selected ward.
- Track bed occupancy using a two-dimensional array.
- Calculate estimated waiting time for each specialty queue.
- Calculate consultation fees, emergency surcharges, ward charges, age subsidies, and final payable amounts.
- Display patients by emergency priority: Critical, Urgent, then Normal.
- Generate a performance report with patient counts, revenue, discounts, bed occupancy, and the highest-paying patient.
- Save patient billing records to a text file.
- Save and restore bed-occupancy status between program runs.

## Technologies Used

- C Programming Language
- GCC Compiler
- Command Line Interface (CLI)

## Project Structure

```text
Hospital-Resource-Allocation-System/
|
|-- main.c                 # Program entry point and menu control
|-- Booking.c              # Patient registration, bed assignment, and billing
|-- Data.c                 # Lookup data, shared arrays, and file handling
|-- HospitalDisplay.c      # Menu, patient display, priority list, and reports
|-- patient_records.txt    # Created automatically for patient billing records
|-- beds_status.txt        # Created automatically for bed occupancy status
`-- README.md
```

## How to Compile

Using GCC:

```bash
gcc main.c Booking.c Data.c HospitalDisplay.c -o hospital
```

## How to Run

### Windows

```bash
hospital.exe
```

## Doctor Specialty Data

| ID | Specialty | Base Fee (LKR) | Consultation Time | Daily Cap |
|---:|---|---:|---:|---:|
| 1 | General Practice (OPD) | 1,500.00 | 15 mins | 30 |
| 2 | Paediatrics | 2,500.00 | 20 mins | 20 |
| 3 | Cardiology | 4,500.00 | 30 mins | 12 |
| 4 | Neurology | 5,000.00 | 30 mins | 10 |

## Hospital Ward Data

| ID | Ward | Daily Bed Rate (LKR) | Capacity |
|---:|---|---:|---:|
| 1 | General Ward | 3,000.00 | 20 |
| 2 | Paediatric Ward | 6,000.00 | 10 |
| 3 | Surgical Ward | 12,000.00 | 10 |
| 4 | ICU (Intensive Care Unit) | 25,000.00 | 5 |

## Billing Rules

- Normal (Level 1): 20% emergency surcharge on the consultation fee.
- Urgent (Level 2) and Critical (Level 3): 50% emergency surcharge on the consultation fee.
- Ward stay cost: days admitted × ward daily bed rate.
- Patients younger than 5 or older than 65 receive a 15% discount on the gross total bill.

## Menu

1. Register a patient and generate a bill
2. Display priority order
3. Display bed occupancy status
4. Display doctor specialties
5. Display hospital wards
6. Generate performance report
7. View saved patient records
8. Save bed status and exit

## File Handling

- `patient_records.txt` stores permanent patient billing records. New records are appended without removing earlier records.
- `beds_status.txt` stores the two-dimensional bed occupancy matrix. It is loaded when the program starts and saved when the program exits through option 8.

## Input Validation

The program validates patient age, emergency level, specialty ID, admission choice, ward ID, and number of admitted days. It also prevents registrations after a specialty reaches its daily patient cap and prevents bed assignment when a ward is full.

## Author

Add your name here.
