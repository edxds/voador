# Voador — An Introduction to Databases Project

## Description

An Introduction to Databases assignment. This repository aims to explain how this project works, as well as provide the source code to better illustrate a solution. This project solves the problem of implementing a many-to-many relationship in C, in the form of a flight management software. In this software, the user can:

1. Register a passenger;
2. Register a flight;
3. Look up a passenger's information;
4. Look up a flight's information;
5. Assign a passenger to a flight;
6. Look up a passenger's flights;
7. Look up a flight's passengers.

All the data inputted in the program is saved to binary files that simulate database tables. The inner workings of the program are explained in the how it works section.

## Table of Contents

- [Compilation](#compilation)
- [Usage](#usage)
- [How It Works](#how-it-works)

## Compilation

This project was written in the CLion IDE, so a CMakeLists.txt file was made by default. If you have CLion or CMake installed, you can run the project through the IDE, or run the cmake command to generate a makefile and then build the project from there.

Or, if you want to go the simple route (which I recommend anyways, since it's just one command), you can use GCC to compile the source code. Run this command in the root folder of the project:

```bash
gcc -o voador src/main.c src/ui.c src/tables.c src/passengers.c src/flights.c src/relations.c
```

## Usage

Listen, it's just a command line interface. Just follow the instructions on-screen. It's not that hard. Here's a screenshot to prettify this page anyway:

![Console screenshot](https://i.imgur.com/0oEQxPM.png)

## How It Works

In a real database, sets of data are represented by tables. Yeah, like Excel tables. With rows and columns and everything. So, if you want to store students in a database, you would have a "Students" table, with a column for ID, one for name, another one for their birth date, whatever. And then each row will represent a student, with all that data, saved in the database.

In this project, these columns are represented by structs. So, if the flight struct has a code field, a origin field, and a destination field, these would map to the respective columns in a real database. Likewise, the rows are represented by an array of structs. So, for a row of flights, we actually have an array of flight structs. Nice, right?

Making the C/database parallel is important because it is crucial to understand how many-to-many relationships work in actual databases. By understanding how they work, we can just map that behaviour in our C program and call it a day. So, how the f\*\*\* do many-to-many relationships work?

In this project, we have two data types (so, two tables): flights and passengers. In this scenerio, a flight can have multiple passengers and passengers can have multiple flights. So how do we map this relationship? By creating a auxiliary table that links one flight code to one passenger code. So we would have one table for the flights, with code and other information as columns, and one table for the passengers, same deal. Then, we'd have an extra table that has the flight code and passenger code as columns.

So, whenever we need to lookup which flights a passenger has been assigned to, we just look up the "bridge" table for rows that have a matching passenger code, and print out the flight codes that we find. Not hard, huh?

Since the teacher also wanted persistance, we need to save these tables (that are actually arrays), to files. Each array has a corresponding \*.ctable file. Everytime we run the program, it reads the file and assigns the data from the file to the in-memory array, and everytime we register a new flight, passenger or assignment, that data gets saved to the file. That way, we can have an actual database-like behavior! C makes it really easy to transfer data from a binary file to an array, so implementing this was actually easier than I expected.

For the actual implementation, you can check out the source code. I did my best to document the code and I am actually a little proud of how clean this C program turned out to be. Any questions just drop me a message!
