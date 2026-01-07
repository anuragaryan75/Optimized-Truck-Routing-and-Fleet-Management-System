# Optimized-Truck-Routing-and-Fleet-Management-System
Overview
This project implements a truck routing and loading system using C++. It utilizes Dijkstra's algorithm for determining the shortest path for trucks from the source to the destination and employs dynamic programming for solving the knapsack problem to efficiently assign objects to trucks.


Features
- Truck Routing: Determines the shortest path for each truck from the source to the destination using Dijkstra's algorithm.
- Object Assignment: Assigns objects to trucks based on their weight and capacity using dynamic programming for the knapsack problem.
- Input Generation: Generates input files for trucks, objects, and map to simulate various scenarios.
- Output Visualization: Provides output files with the assigned trucks and their routes for visualization and analysis.

Classes
- box.h : For object Box
- graph.h : For map object, which will be used to keep track of the map
- truck.h : For storing truck object

Files
- main.cpp: Contains the main logic for the truck routing and loading system, and also the knapsack solution for the problem.
- testgenerator.h: Generates random data for map, trucks and boxes.
- design.cpp: For storing syle items, and to ensure the program enforces menu driven UI.


Input Files
- box.csv: Contains information about the objects to be loaded onto trucks (e.g., weight, dimensions).
- truck.csv: Provides details about each truck (e.g., capacity, available space).
- map.csv: Represents the map with nodes and edges for calculating routes.


Usage
- Open Command Prompt.
- Direct to code directory.
- Run g++ main.cpp -o out.exe
  out.exe

*** Use keys W, S to navigate Menu, Q to Go back, and X to select




