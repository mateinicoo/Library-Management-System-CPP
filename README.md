# Library-Management-System-CPP
# 📚 Library Management System

A console-based Library Management application written in **C++** that demonstrates advanced Object-Oriented Programming (OOP) concepts.

## 🚀 About the Project
This project is an interactive console application designed to manage authors, publishing houses, and documents (books, articles) within a library. It was developed entirely from scratch to showcase the practical implementation of core and advanced C++ concepts.

## 💻 Technical Highlights
The codebase extensively utilizes the following C++ paradigms and features:

*   **Design Patterns:** Implementation of the **Singleton** pattern for manager classes (`ManagerAutori`, `ManagerEdituri`) to ensure a single, globally accessible instance.
*   **Inheritance & Polymorphism:** Use of abstract base classes (`Document` with pure virtual functions) and robust method overriding (using the `override` keyword).
*   **Solving the "Diamond Problem":** Utilization of virtual inheritance (`virtual Carte`) for the `CarteScoalaPrimara` class, which inherits from both `CarteEducativa` and `CarteCopii`.
*   **Generics (Templates):** Implementation of a generic `Biblioteca<T>` class capable of storing lists of any document type.
*   **RTTI (Run-time Type Information) & Exception Handling:** Safe type conversion using `dynamic_cast`, runtime type checking with `typeid`, and standard exception handling (`std::bad_cast` within `try-catch` blocks).
*   **Operator Overloading:** Custom behavior for I/O stream operators (`<<`, `>>`), math and increment operators (`+=`, `++`), and the copy assignment operator (`=`).
*   **Standard Template Library (STL):** Effective use of dynamic data structures (`std::vector`, `std::list`) and sorting algorithms (`std::sort` with custom static comparators).

## 🛠️ How to Run
The project is self-contained within a single source file. It can be compiled using any modern C++ compiler (MinGW/GCC, Clang, MSVC) that supports the C++11 standard or later.

```bash
g++ main.cpp -o library
./library
