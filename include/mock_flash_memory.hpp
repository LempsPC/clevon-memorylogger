#ifndef MOCK_FLASH_MEMORY_HPP
#define MOCK_FLASH_MEMORY_HPP

#include <string>
#include <vector>

#define TOTAL_PAGES 256
#define PAGE_SIZE 256

class MockFlashMemory {
public:
    MockFlashMemory(const std::string& filename);

    bool writePageToMemory(int pageNumber, const char* data);
    bool readPageFromMemory(int pageNumber, char* buffer);

private:
    const std::string filename;
    void initializeFlashMemoryFile();
};

#endif // MOCK_FLASH_MEMORY_HPP