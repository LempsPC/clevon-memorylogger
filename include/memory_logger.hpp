#ifndef MEMORY_LOGGER_HPP
#define MEMORY_LOGGER_HPP

#include <cstdint>
#include "mock_flash_memory.hpp"

#define MAX_LOGS_IN_PAGE 31

class MemoryLogger {
private:
    typedef struct payload {
        uint16_t log_id;
        uint8_t log_data[6];
    } payload_t;
    typedef struct __attribute__((packed)) {
        uint64_t log_count;
        payload_t payload[MAX_LOGS_IN_PAGE];
    } page_struct_t;

    page_struct_t currentPage;

    uint32_t currentPageNumber;
    MockFlashMemory* flashMemory;
    uint8_t memoryAllocation[TOTAL_PAGES]; // Fixed-size array to store the number of logs in each page

    void flushLogsToFlash();
    void updateMemoryAllocation();
    void checkWholeMemoryForAllocation();
    int findAvailablePage();
    int findOldestPage();
public:
    MemoryLogger();
    ~MemoryLogger();

    int8_t write_log(uint16_t log_id, uint8_t *data);
    void readPage(uint32_t pageNumber, page_struct_t& pageData);
    int8_t find_log_by_id(uint16_t log_id, uint8_t *data);
    int checkMemoryAllocation(float *total, uint8_t *page);
};

#endif // MEMORY_LOGGER_HPP