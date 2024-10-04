#include <iostream>
#include <string.h>
using namespace std;

// To execute C++, please define "int main()"

// The TestCase is shown below
// Input : 1 2
// Output : 3

char* strcopy(char* destination, const char* source) {
        if (destination == nullptr || source == nullptr) {
                return nullptr;
        }
        size_t src_len = strlen(source);
        
        if (source < destination && source + src_len > destination) {
                destination += src_len + 1;
                *destination-- = '\0';
                source += src_len;
                while (src_len --) {
                        *(--destination) = *(--source);
                }
        } else {
                char* dest = destination;
                while (*source) {
                        *dest ++ = *source ++;
                }
                *dest = '\0';
        }
        return destination;
}
int main() {
        char src[] = "Hello world";
        char des[30];
        if (strcopy(des, src) != nullptr) {
                printf("%s\n", des);
        }
          return 0;
}