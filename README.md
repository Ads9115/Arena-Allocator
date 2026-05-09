# Arena Allocator (C++)

A minimal, single-header arena allocator implementation with a simple reset API. It allocates from a fixed-size buffer and does not support individual frees.

## Features

- Fixed-capacity linear allocator
- Alignment-aware allocations
- Optional placement-new helper (`AllocateNew`)
- O(1) reset to reuse the arena

## Build (MSVC)

Use one of the options below from the repo root.

### Option A: VS Code task

1. Open the Command Palette.
2. Run "Tasks: Run Build Task".
3. Choose "MSVC Build Arena Allocator".

### Option B: Developer PowerShell

```bat
cl.exe /Zi /EHsc /nologo /Fe:build\ArenaAllocator.exe src\*.cpp /I include
```

## Run

```bat
build\ArenaAllocator.exe
```

## Usage

```cpp
#include "ArenaAllocator.hpp"

struct Foo {
    int x;
    float y;
};

int main() {
    ArenaAllocator arena(1024);

    // Raw allocation
    void* mem = arena.Allocate(sizeof(Foo), alignof(Foo));
    Foo* a = mem ? new (mem) Foo{1, 2.0f} : nullptr;

    // Convenience helper
    Foo* b = arena.AllocateNew<Foo>(3, 4.0f);

    // Reuse the arena (does not call destructors)
    arena.Reset();
    return 0;
}
```

## Notes

- `Reset()` only rewinds the offset; it does not call destructors.
- `Allocate()` returns `nullptr` when out of capacity.
- The arena is not thread-safe.

## Layout

- include/ArenaAllocator.hpp
- src/ArenaAllocator.cpp
- src/main.cpp

## License

MIT. See LICENSE.
