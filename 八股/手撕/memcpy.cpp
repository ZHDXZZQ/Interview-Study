#include <iostream>

void my_memcpy(void* dest, const void* src, size_t size) {
    char* dest_ptr = static_cast<char*>(dest);
    const char* src_ptr = static_cast<const char*>(src);
    for (size_t i = 0; i < size; ++ i) {
        dest_ptr[i] = src_ptr[i];
    }
}

int main() {
    int source[] = {1, 2, 3, 4, 5};
    int destination[5];

    my_memcpy(destination, source, sizeof(source));

    for (const auto& element : destination) {
        std::cout << element << " ";
    }
    return 0;
}