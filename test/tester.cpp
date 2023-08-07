#include "tester.hpp"
#include "memory_logger.hpp"
#include <stdint.h>
#include <cassert>
#include <iostream>

int main()
{
    return tester_main();
}

// Test cases
void test_write_log_success()
{
    MemoryLogger memlogger;
    uint8_t test_data[6] = {1, 2, 3, 4, 5, 6};
    uint16_t test_log_id = 1234;
    int result = memlogger.write_log(test_log_id, test_data);
    assert(result == 0);
    std::cout << "Test case 'test_write_log_success' passed!\n";
}

void test_write_log_invalid_data()
{
    MemoryLogger memlogger;
    uint8_t* test_data = nullptr;
    uint16_t test_log_id = 5678;
    int result = memlogger.write_log(test_log_id, test_data);
    assert(result != 0);
    std::cout << "Test case 'test_write_log_invalid_data' passed!\n";
}

int tester_main()
{
    // Run the test cases
    test_write_log_success();
    test_write_log_invalid_data();

    return 0;
}