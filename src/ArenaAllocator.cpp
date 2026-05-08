#include "include/ArenaAllocator.hpp"


ArenaAllocator::ArenaAllocator(std::size_t size)
 :m_capacity(size), m_offset(0)    
{
    m_buffer = new unsigned char[size];
}

ArenaAllocator::~ArenaAllocator(){
    delete[] m_buffer;
}

void ArenaAllocator::Reset(){
    m_offset = 0;
}

void* ArenaAllocator::Allocate(size_t size, size_t alignment){

    uintptr_t cast = reinterpret_cast<uintptr_t>(m_buffer + m_offset);
    size_t padding = (alignment - (cast % alignment)) % alignment;
    if((m_offset + padding + size) > m_capacity)
        return nullptr;
    
    m_offset += padding;
    void* ptr =  m_buffer + m_offset;
    m_offset += size;

    return ptr;
}
