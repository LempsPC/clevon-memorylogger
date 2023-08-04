#include <iostream>
#include <cstring>
#include "memory_logger.hpp"

MemoryLogger::MemoryLogger() {
    flashMemory = new MockFlashMemory("flash_memory.bin");
    std::memset(&currentPage, 0, sizeof(page_struct_t));
    currentPageNumber = 0;
    // Initialize memory allocation array to 0
    std::memset(memoryAllocation, 0, sizeof(memoryAllocation));
    checkWholeMemoryForAllocation();
}

MemoryLogger::~MemoryLogger() {
    delete flashMemory;
}

void MemoryLogger::flushLogsToFlash() 
{
    // Write the page to flash memory
     if (flashMemory->writePageToMemory(currentPage.log_count, reinterpret_cast<char*>(&currentPage))) 
    {
        //if successful, then fetch another page and start using it
        updateMemoryAllocation();
        currentPageNumber = findAvailablePage();
        std::cout << "New available page " << currentPageNumber << std::endl;
        std::memset(&currentPage, 0, sizeof(page_struct_t));
        readPage(currentPageNumber, currentPage);
    }
}

int8_t MemoryLogger::write_log(uint16_t log_id, uint8_t *data) 
{
    if (currentPage.log_count == MAX_LOGS_IN_PAGE) 
    {    
        flushLogsToFlash();
    }
    currentPage.payload[currentPage.log_count].log_id = log_id;
    std::memcpy(currentPage.payload[currentPage.log_count].log_data, data, 6);
    currentPage.log_count++;
    updateMemoryAllocation();
    return 0;
}

void MemoryLogger::readPage(uint32_t pageNumber, page_struct_t& pageData) 
{ 
    char buffer[256]; 
    if (flashMemory->readPageFromMemory(pageNumber, buffer)) { 
        std::copy(buffer, buffer + sizeof(page_struct_t), (char*)&pageData); 
    } 
}


int MemoryLogger::checkMemoryAllocation(float *total, uint8_t *page) {
    int totalLogs = 0;
    int usedPages = 0;

    for (int i = 0; i < TOTAL_PAGES; ++i) {
        totalLogs += memoryAllocation[i];
        if (memoryAllocation[i] > 0) {
            usedPages++;
        }
    }
    //int usedLogs = totalLogs - memoryAllocation[0]; // Exclude the logs in unused pages (count = 0)

    if (totalLogs == 0) {
        return 0;
    }

    float pageAllocation = (float)currentPage.log_count / MAX_LOGS_IN_PAGE;
    *page = (uint8_t)(pageAllocation*100);

    float percentage = ((float)totalLogs * 100) / (TOTAL_PAGES * 31);
    *total = percentage;
    return (int)percentage;
}

void MemoryLogger::updateMemoryAllocation() 
{
    memoryAllocation[currentPageNumber] = currentPage.log_count;
}

/**
 * Loops through whole flash memory and reads headers, notes total memory allocation into array
*/
void MemoryLogger::checkWholeMemoryForAllocation() {
    std::memset(memoryAllocation, 0, sizeof(memoryAllocation));
    for(int i = 0; i < TOTAL_PAGES; i++)
    {
        page_struct_t tempPage;
        readPage(i, tempPage);
        memoryAllocation[i] = tempPage.log_count;
    }

    //check by printing:
    std::cout << "Allocation array: " << std::endl;
    for(int i = 0; i < TOTAL_PAGES; i++)
    {
        std::cout << (int)memoryAllocation[i] << " ";
    }
    std::cout << std::endl;
}

int MemoryLogger::findAvailablePage()
{
    uint8_t emptiest_page_id = 0;
    uint8_t current;
    float total = 0;
    if(100 == checkMemoryAllocation(&total, &current))
    {
        emptiest_page_id = findOldestPage();
        return emptiest_page_id;
    }
    
    uint8_t emptiest_page_allocation = MAX_LOGS_IN_PAGE;

    for(int i = 0; i < TOTAL_PAGES; i++)
    {
        if(!memoryAllocation[i])
        {
            //emptiest page found, return its index
            emptiest_page_id = i;
            break;
        }
        if(memoryAllocation[i] < emptiest_page_allocation)
        {
            emptiest_page_allocation = memoryAllocation[i];
            emptiest_page_id = i;
        }
    }
    return emptiest_page_id;
}

int MemoryLogger::findOldestPage()
{
    uint16_t oldest_log = UINT16_MAX;
    uint8_t oldest_page_id = 0;
    
    for(int i = 0; i < TOTAL_PAGES; i++)
    {
        page_struct_t tempPage;
        readPage(i, tempPage);
        
        if(tempPage.log_count)
        {
            for(uint64_t j = 0; j < tempPage.log_count; j++)
            {
                if(tempPage.payload[j].log_id < oldest_log)
                {
                    oldest_log = tempPage.payload[j].log_id;
                    oldest_page_id = i;
                }
            }
        }
    }
    return oldest_page_id;
}

int8_t MemoryLogger::find_log_by_id(uint16_t log_id_to_find, uint8_t *data)
{
    int8_t result = 0;
    /*
    for(uint16_t i = 0; i < currentPage.log_count, i++)
    {
        if(currentPage.payload[i].log_id == log_id_to_find)
        {
            
        }
    }
    */
    return result;
}