#include <iostream>
#include <csignal>
#include <chrono>
#include <unistd.h>
#include <iomanip>

#include "memory_logger.hpp"


void signalHandler ( int signum )
{
    std::cout << "Interrupt signal (" << signum << ") received.\n";

    // cleanup and close up stuff here
    // terminate program
    exit(signum);
}

void main_loop()
{
    // register signal SIGINT and signal handler
    signal (SIGINT, signalHandler);
    MemoryLogger memlogger;
    uint16_t log_id = 0;
    uint8_t data[6];

    
    while(1)
    {    
        log_id++;
        std::cout << "making log " << (int)log_id << std::endl;

        memlogger.write_log(log_id, data);
        float total = 0;
        uint8_t page = 0; 
        memlogger.checkMemoryAllocation(&total, &page);
        std::cout << "Allocation: total: " << total << "% " << "Page: " << (int)page << "%" << std::endl;

        usleep(50000);
    }
}