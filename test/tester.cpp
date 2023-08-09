#include <stdint.h>
#include <cassert>
#include <iostream>

#include "tester.hpp"
#include "memory_logger.hpp"
#include "mock_flash_memory.hpp"


int main()
{
    return tester_main();
}

// Test cases
void test_write_log_success()
{
    MemoryLogger memlogger;
    int expected = 0;
    uint8_t test_data[6] = {1, 2, 3, 4, 5, 6};
    uint16_t test_log_id = 1234;
    int result = memlogger.write_log(test_log_id, test_data);
    if (result != expected) {
        std::cout << "Test case 'test_write_log_success' failed! Got " << result << ", expected " << expected << std::endl;
    } else {
        std::cout << "Test case 'test_write_log_success' passed!\n";
    }
}

void test_write_log_invalid_data()
{
    MemoryLogger memlogger;
    uint8_t* test_data = nullptr;
    int expected = 0;
    uint16_t test_log_id = 5678;
    int result = memlogger.write_log(test_log_id, test_data);
    if (result == expected) {
        std::cout << "Test case 'test_write_log_invalid_data' failed! Got " << result << ", expected " << expected << std::endl;
    } else {
        std::cout << "Test case 'test_write_log_invalid_data' passed!\n";
    }
}

void test_find_log_by_id()
{
    MemoryLogger memlogger;
    uint8_t test_data[6] = {1, 2, 3, 4, 5, 6};
    uint16_t test_log_id = 1234;
    memlogger.write_log(test_log_id, test_data);

    uint8_t found_data[6];
    int8_t result = memlogger.find_log_by_id(test_log_id, found_data);

    if (result == 0) {
        std::cout << "Test case 'test_find_log_by_id' passed! Found log with ID: " << test_log_id << std::endl;
    } else {
        std::cout << "Test case 'test_find_log_by_id' failed! Log with ID: " << test_log_id << " not found." << std::endl;
    }
}

void test_find_log_by_id_multiple_logs() 
{
    MemoryLogger memlogger;
    uint8_t test_data[6] = {1, 2, 3, 4, 5, 6};
    uint16_t test_log_id = 1234;
    memlogger.write_log(test_log_id, test_data);

    for (uint8_t i = 0; i < 70; i++) 
    {
        uint16_t log_id = i + 1235;
        uint8_t data[6] = {(uint8_t)i, (uint8_t)(i + 1), (uint8_t)(i + 2), (uint8_t)(i + 3), (uint8_t)(i + 4), (uint8_t)(i + 5)};
        memlogger.write_log(log_id, data);

    }

    uint8_t found_data[6];
    int8_t result = memlogger.find_log_by_id(test_log_id, found_data);

    if (result == 0) {
        std::cout << "Test case 'test_find_log_by_id_multiple_logs' passed! Found log with ID: " << test_log_id << std::endl;
    } else {
        std::cout << "Test case 'test_find_log_by_id_multiple_logs' failed! Log with ID: " << test_log_id << " not found." << std::endl;
    }
}

int tester_main()
{
    // Run the test cases
    test_write_log_success();
    test_write_log_invalid_data();
    test_find_log_by_id();
    test_find_log_by_id_multiple_logs();
    return 0;
}