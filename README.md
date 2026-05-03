# FitZone Gym Management System

A comprehensive C++ interactive CLI application designed to manage gym operations and memberships efficiently.

## Project Overview

**FitZone** is a Gym Management System built as part of the LLT-1 Project: Application Development Using Design Concepts. This application provides a user-friendly command-line interface for managing gym members, memberships, and fitness plans.

## Features

- **Member Management**: Add, edit, and view gym members
- **Membership Plans**: Manage different gym subscription plans
- **Membership Tracking**: Track active memberships and renewals
- **Input Validation**: Robust input handling with error checking
- **Interactive CLI**: User-friendly command-line interface with clear navigation

## Technical Details

- **Language**: C++
- **Platform**: Cross-platform (Windows/Linux)
- **Standards**: Object-Oriented Programming with Design Concepts
- **Build**: Standard C++ compilation

## Requirements

- C++ compiler (C++11 or later)
- Standard C++ libraries

## Compilation

To compile the project:

```bash
g++ -std=c++11 main.c++ -o fitzone
```

Or using your preferred C++ compiler:

```bash
clang++ -std=c++11 main.c++ -o fitzone
```

## Usage

Run the compiled executable:

```bash
./fitzone
```

or on Windows:

```cmd
fitzone.exe
```

Follow the on-screen menu prompts to navigate through the system's features.

## Project Structure

- `main.c++` - Main application file containing the complete system implementation

## Key Design Concepts

- **Abstraction**: Pure virtual functions for polymorphic behavior
- **Encapsulation**: Private data members with public accessors
- **Object-Oriented Design**: Class hierarchies for different user types and gym resources
- **Input Validation**: Safe user input handling with retry mechanisms

## License

This is an educational project

---

**Developed for**: Application Development Using Design Concepts Course
