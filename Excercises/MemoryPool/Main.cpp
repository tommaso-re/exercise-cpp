#include <stdint.h>
#include <iostream>

struct MemoryPoolManager
{
    static constexpr uint16_t m_numBlocks = 8;
    static constexpr uint16_t m_blockSize = 64; 
    static constexpr uint32_t m_totalSize = m_numBlocks * m_blockSize;

    char* m_poolBuffer = nullptr;//create a pool buffer the start of the pool

    void* m_freeListHead = nullptr;//first free block   

    MemoryPoolManager()
    {
        m_poolBuffer = new char[m_totalSize];//we assign to poolbuffer the start of the pool

        m_freeListHead = m_poolBuffer;

        char* currentBlock = m_poolBuffer;

        for (uint16_t i = 0; i < m_numBlocks - 1; i++)
        {
            char* nextBlock = currentBlock + m_blockSize;

            *(void**)currentBlock = nextBlock;

            currentBlock = nextBlock;
        }

        *(void**)currentBlock = nullptr;

        std::cout << "Memory Pool was created\n";
        std::cout << "Byte Allocated:  " << m_totalSize << "\n";
    }

    ~MemoryPoolManager()
    {
        delete[] m_poolBuffer;
        std::cout << "Memory Pool was destroyed\n";
    }
};

int main()
{
    MemoryPoolManager memoryPool;

}