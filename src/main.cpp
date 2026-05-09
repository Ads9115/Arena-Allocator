#include <iostream>
#include "ArenaAllocator.hpp"

// 1.custom math structures
struct vec3 { 
    float x, y, z; 
    vec3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
};

// alignas(16) forces the compiler to require strict 16-byte memory boundaries
struct alignas(16) mat4 { 
    float data[16] = {1.0f}; 
    mat4() {} 
};

int main() {
    // Buy a 1 Megabyte chunk of contiguous RAM from the OS.
    ArenaAllocator memoryBuffer(1024 * 1024);

    std::cout << "Engine starting. Memory block secured.\n\n";

    // Simulate a tiny 2-frame render loop
    for (int frame = 1; frame <= 2; ++frame) {
        
        // 1. Allocate a temporary matrix for this specific frame
        mat4* viewProjection = memoryBuffer.AllocateNew<mat4>();
        
        // 2. Allocate temporary vectors (e.g., for drawing debug lines)
        vec3* startPoint = memoryBuffer.AllocateNew<vec3>(0.0f, 0.0f, 0.0f);
        vec3* endPoint   = memoryBuffer.AllocateNew<vec3>(10.0f, 5.0f, 0.0f);

        std::cout << "Frame " << frame << " objects allocated.\n";
        std::cout << " - mat4 Address: " << viewProjection << "\n";
        std::cout << " - vec3 Address: " << startPoint << "\n";

        // 3. The frame is over. Reset the internal offset pointer to 0.
        // On the next loop, viewProjection will simply overwrite the old data.
        memoryBuffer.Reset();
    }

    std::cout << "\nEngine shutting down. Memory released to OS.\n";
    return 0;
}