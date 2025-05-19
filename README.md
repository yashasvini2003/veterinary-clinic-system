# 🐾 Veterinarian Clinic System – C Final Project

This project is a **Veterinary Clinic Appointment Management System** developed in **C**, as part of the final assignment for the **BTP144 (C Programming)** course at **Seneca College**.

The system manages **patient contact information** and **appointment scheduling** for a veterinary clinic. The project is developed incrementally in **three milestones**, each building on the last to achieve a complete and functional solution.

---

## 📌 Milestones Overview

### ✅ Milestone 1 – Helper Functions

> Focus: Developing reusable helper functions for validation and I/O

**Key Features:**
- Input validation functions (e.g., integer, string, range checks)
- Utilities for clearing input buffer and waiting for user interaction
- Formatting and display helpers

**Purpose:** These functions improve readability, reduce redundancy, and ensure consistency across the project.

---

### ✅ Milestone 2 – Patient Management

> Focus: Implementing patient record handling logic

**Key Features:**
- Add, edit, and remove patient records
- Store patient contact information
- Display a list of patients in a formatted view
- Use of helper functions from Milestone 1

**Files Introduced:**
- `clinic.h` / `clinic.c` – Core patient data structures and logic

---

### ✅ Milestone 3 – Appointment Management

> Focus: Full appointment scheduling system

**Key Features:**
- Add, remove, and view appointments
- Appointment time/date validation
- Display schedule sorted by date and time
- Prevent scheduling conflicts
- Persistent menu-driven interface for clinic staff

**Final Deliverables:**
- A fully functioning C-based appointment system
- Modular, maintainable code using helper functions and structured design
- Reflection submitted as per project rubric

---

## 🛠️ How to Compile & Run

```bash
gcc clinic.c main.c -o vet_clinic
./vet_clinic
