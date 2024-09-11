/*
    内存池的结构：
        使用双向链表管理内存块，每个节点代表一个内存块。
        内存块包含指向前后块的指针、块的大小以及是否空闲的信息。
    内存分配算法：
        采用“首次适应算法”（First Fit）查找第一个足够大的空闲块来分配内存。
        如果找到的空闲块过大，可以将其分割为一个分配块和一个新的空闲块。
    碎片处理算法：
        当内存释放时，检查相邻的内存块是否空闲，如果是空闲的则进行合并以减少碎片化。
*/

#include <iostream>
#include <cstddef> // for size_t

// 内存块结构
struct Block {
    size_t size;           // 块大小
    bool free;             // 是否空闲
    Block* prev;           // 指向前一个块
    Block* next;           // 指向下一个块
};

// 内存池类
class MemoryPool {
public:
    MemoryPool(size_t poolSize);
    ~MemoryPool();

    void* allocate(size_t size);
    void deallocate(void* ptr);
    void printMemoryLayout(); // 打印当前内存池的布局，调试用

private:
    Block* findFreeBlock(size_t size);     // 找到合适的空闲块
    void splitBlock(Block* block, size_t size); // 分割块
    void mergeAdjacentBlocks(Block* block); // 合并相邻空闲块

    void* poolStart;                       // 内存池的起始地址
    Block* head;                           // 链表的头指针
};

MemoryPool::MemoryPool(size_t poolSize) {
    poolStart = malloc(poolSize); // 初始化内存池
    head = reinterpret_cast<Block*>(poolStart); // 将头部指针指向池起始
    head->size = poolSize - sizeof(Block); // 设置初始大小
    head->free = true; // 初始块为空闲状态
    head->prev = nullptr;
    head->next = nullptr;
}

/*
1. head->size = poolSize - sizeof(Block); // 设置初始大小 这里为什么要减去 sizeof(Block)？
原因：sizeof(Block) 表示 Block 结构体自身的大小。内存池中的每个内存块不仅包含实际用户可用的内存数据区域，还需要包含用于管理该内存块的元数据（如大小、前后指针、是否空闲等）。

细节：当初始化内存池时，将整个池的内存分配给 head 块。head->size 表示实际可用的内存大小，而不是包括管理信息的大小。为了计算实际可用的内存大小，需要从总池大小中减去 sizeof(Block)。

示例：假设内存池总大小为 1024 字节，如果不减去 sizeof(Block)，会导致计算错误，因为这部分空间是用于管理块信息的，而不是用户可用的内存。因此，head->size 设置为 poolSize - sizeof(Block)，确保 size 表示真正的可用空间。
*/

MemoryPool::~MemoryPool() {
    free(poolStart); // 释放内存池
}

void* MemoryPool::allocate(size_t size) {
    Block* block = findFreeBlock(size); // 查找适合的空闲块
    if (!block) {
        std::cerr << "No sufficient memory to allocate." << std::endl;
        return nullptr;
    }
    splitBlock(block, size); // 分割块（如果必要）
    block->free = false; // 标记块为已使用
    return reinterpret_cast<void*>(block + 1); // 返回块的数据部分
}

/*
2. return reinterpret_cast<void*>(block + 1); // 返回块的数据部分 这里为什么要返回 +1？
原因：block 是一个指向 Block 结构体的指针，而 block + 1 会跳过这个 Block 结构体，指向块的数据区域。

细节：在 C++ 中，block + 1 并不是字节级的偏移，而是按类型进行偏移。因为 block 是 Block* 类型，所以 block + 1 会将指针移动 sizeof(Block) 个字节的位置，这样就跳过了管理信息，直接指向用户可用的内存区域。
具体来说，block + 1 会将指针移动到当前块的 data 部分，而不是 Block 结构体的起始地址，从而返回的是用户可以使用的内存。

示例：如果 block 的地址是 0x1000，且 sizeof(Block) 为 32 字节，那么 block + 1 就是 0x1020，指向的正是用户可用的内存区域。
*/

void MemoryPool::deallocate(void* ptr) {
    if (!ptr) return;
    Block* block = reinterpret_cast<Block*>(ptr) - 1; // 获取对应的块指针，-1指向了block的元数据
    block->free = true; // 标记块为空闲
    mergeAdjacentBlocks(block); // 尝试合并相邻空闲块
}

Block* MemoryPool::findFreeBlock(size_t size) {
    Block* current = head;
    while (current) {
        if (current->free && current->size >= size) {
            return current;
        }
        current = current->next;
    }
    return nullptr; // 没有找到合适的块
}

void MemoryPool::splitBlock(Block* block, size_t size) {
    if (block->size <= size + sizeof(Block)) return; // 如果空间不足以分割新块则返回
    // 把剩余空间独立成下一个块
    Block* newBlock = reinterpret_cast<Block*>(reinterpret_cast<char*>(block) + sizeof(Block) + size);
    newBlock->size = block->size - size - sizeof(Block);
    newBlock->free = true;
    newBlock->next = block->next;
    newBlock->prev = block;

    block->size = size;
    block->next = newBlock;

    if (newBlock->next) {
        newBlock->next->prev = newBlock;
    }
}

void MemoryPool::mergeAdjacentBlocks(Block* block) {
    // 合并前一个块
    if (block->prev && block->prev->free) {
        block->prev->size += block->size + sizeof(Block);
        block->prev->next = block->next;
        if (block->next) {
            block->next->prev = block->prev;
        }
        block = block->prev;    // 当前块合并完成，指向该块
    }
    // 合并后一个块
    if (block->next && block->next->free) {
        block->size += block->next->size + sizeof(Block);
        block->next = block->next->next;
        if (block->next) {
            block->next->prev = block;
        }
    }
}

void MemoryPool::printMemoryLayout() {
    Block* current = head;
    std::cout << "Memory Pool Layout:" << std::endl;
    while (current) {
        std::cout << "[Block at " << current << ", size: " << current->size
                  << ", free: " << (current->free ? "yes" : "no") << "]" << std::endl;
        current = current->next;
    }
}

int main() {
    MemoryPool pool(1024); // 创建一个大小为1024字节的内存池

    void* ptr1 = pool.allocate(100); // 分配100字节
    void* ptr2 = pool.allocate(200); // 分配200字节

    pool.printMemoryLayout(); // 打印内存池布局

    pool.deallocate(ptr1); // 释放第一个内存块
    pool.deallocate(ptr2); // 释放第二个内存块

    pool.printMemoryLayout(); // 打印内存池布局

    return 0;
}

/*
代码解释
    数据结构：Block 结构表示一个内存块，包括大小、是否空闲、前后指针。
    分配内存：采用首次适应算法寻找合适块，必要时分割块。
    释放内存：标记块为空闲，合并相邻的空闲块以减少碎片化。
    内存池布局打印：方便调试，查看当前内存池的状态。
主要特点
    高效分配和释放：通过链表管理，避免频繁的系统级分配和释放。
    碎片处理：通过分割和合并机制减少内存碎片化，提高内存利用率。
    扩展性好：可以扩展为更复杂的内存管理策略，如最佳适应或伙伴系统。
此内存池示例是一个基础实现，适用于小型嵌入式系统或需要优化性能的应用场景，可根据实际需求进行优化和扩展。
*/