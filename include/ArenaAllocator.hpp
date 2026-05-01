#pragma once

#include<cstddef>
#include<cstdint>
#include<new>
#include<utility>


class ArenaAllocator{

private:
    unsigned char* m_buffer;
    std::size_t m_capacity;
    std::size_t m_offset;
    
public:
    //Life Cycle
    ArenaAllocator(std::size_t capacity);
    ~ArenaAllocator();

    //Deleteing the Copy Constructors
    ArenaAllocator(const ArenaAllocator&) = delete;
    ArenaAllocator operator=(const ArenaAllocator&) = delete;

    void* Allocate(size_t size, size_t alignment);
    void* Reset();

    //Template
    template<typename T, typename... Args>
    T* AllocateNew(Args&&... args){
        void* ptr =  Allocate(sizeof(T), alignof(T));

        if(!ptr)
            return nullptr;

        return new(ptr) T(std::forward<Args>(args)...);

    }


    


    

};