# clevon-memorylogger
This is solution project for embedded software engineer task. 
In short task is to develop a basic flash memory logger module for an embedded system, along 
with a mock framework to facilitate testing. The memory logger should be designed to track 
memory usage in flash memory, providing information about the current memory utilization, 
and allowing data retrieval from the flash memory
Task description provided separately.

## Dependencies
As far as author has known there are no additional dependencies necessary to compile and run the project.
The project has been made in Ubuntu 22.04 using default build essential tools.
If you start from fresh install, run 
```bash
sudo apt update
sudo apt upgrade -y
sudo apt install build-essential -y
```

## Install
Install by running make in project directory, it shall create main executable file in project main directory.
```bash
make
```

## Run
Run main file, like this:
```bash
-/main
```
Application will start generating logs with sequential ID's and random payload and add these into flash memory. ALso after each insertion the application asks memorylogger module about memory allocation and prints out memory allocation.
Memory allocation is calculated on current page in use and total allocation displayed in %.
The application will keep running until keyboard interrupt is detected in which case the application will shut down.

## Test
This solution has some unit tests to test main functionality of the code. This can be seen by running make test which compiler tester executable.
```bash
make test
```
To run tests, use:
```bash
./tester
```

Tester application runs unit tests that are located in /test directory

### Additional information

This software was developed in Visual Studio Code and comes with settings and launch.json which can be used for additional debugging.
Also this solution itself cannot be taken as a complete solution for simulating flash memory and all its shenanigans. This project is meant to provide solution for software engineering tasks to demonstrate problem solving, documentation etc. skills which are useful for everyday software engineering. Due to time constraints this solution also doesn't have full coverage of each imaginable test scenario that this application might encounter. Additional tests can be added to project in the future to test and increase its rigidity.
