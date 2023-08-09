#include "mock_flash_memory.hpp"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>



const int FLASH_MEMORY_SIZE = TOTAL_PAGES * PAGE_SIZE;

MockFlashMemory::MockFlashMemory(const std::string& filename) : filename(filename) 
{
    initializeFlashMemoryFile();
}

bool MockFlashMemory::writePageToMemory(int pageNumber, const char* data) 
{
    if (pageNumber < 0 || pageNumber >= TOTAL_PAGES) {
        std::cerr << "Invalid page number." << std::endl;
        return false;
    }

    std::fstream flashFile(filename, std::ios::binary | std::ios::in | std::ios::out);
    if (!flashFile) {
        std::cerr << "Failed to open flash memory file." << std::endl;
        return false;
    }

    flashFile.seekp(pageNumber * PAGE_SIZE, std::ios::beg);
    flashFile.write(data, PAGE_SIZE);
    flashFile.close();
    return true;
}

bool MockFlashMemory::readPageFromMemory(int pageNumber, char* buffer) 
{
    if (pageNumber < 0 || pageNumber >= TOTAL_PAGES) {
        std::cerr << "Invalid page number." << std::endl;
        return false;
    }

    std::ifstream flashFile(filename, std::ios::binary | std::ios::in);
    if (!flashFile) {
        std::cerr << "Failed to open flash memory file." << std::endl;
        return false;
    }

    flashFile.seekg(pageNumber * PAGE_SIZE, std::ios::beg);
    flashFile.read(buffer, PAGE_SIZE);
    flashFile.close();
    return true;
}

void MockFlashMemory::initializeFlashMemoryFile() 
{
    std::ofstream flashFile(filename, std::ios::binary | std::ios::out);
    std::vector<char> emptyPage(PAGE_SIZE, 0);
    
    for (int i = 0; i < TOTAL_PAGES; ++i) {
        flashFile.write(&emptyPage[0], PAGE_SIZE);
    }
    flashFile.close();
}