/*
    现场实现，时间On，空间On，n为字符个数
    1. 将字符转换为高3位和低4位，计算对应的数字，转换十六进制输出
*/

#include <iostream>
#include <math.h>
#include <string>
#include <unordered_map>
using namespace std;
int main() {
    unordered_map<int, char> umap;
    for (int i = 0; i < 10; ++ i) {
        umap[i] = i + '0';
    }
    umap[10] = 'A';
    umap[11] = 'B';
    umap[12] = 'C';
    umap[13] = 'D';
    umap[14] = 'E';
    umap[15] = 'F';
    // 十六进制的umap

    string str = "jkl";
    string res = "0x";
    cout << res;

    // 遍历所有字符
    for (auto c : str) {
        int cur_num = 0;    // 低4位的十进制
        int x = 0;  // 二进制的位权
        int i = 0;  // ascii码二进制的位置
        for ( ; i < 4; ++ i) {  // 低4位计算
            int num = (c >> i) & 1;
            if (num == 1) {
                cur_num += pow(2, x);
            }
            ++ x;
        }

        int cur_num2 = 0;   // 高3位计算
        x = 0;
        for ( ; i < 7; ++ i) {
            int num = (c >> i) & 1;
            if (num == 1) {
                cur_num2 += pow(2, x);
            }
            ++ x;
        }
        cout << umap[cur_num2] << umap[cur_num];
    }
    return 0;
}

/*    优雅实现
#include <iostream>
#include <string>

std::string toHexChar(unsigned char c) {
    const char hexDigits[] = "0123456789ABCDEF";
    std::string hex;
    hex.push_back(hexDigits[c >> 4]);  // 高4位
    hex.push_back(hexDigits[c & 0x0F]);  // 低4位
    return hex;
}

std::string stringToHex(const std::string& input) {
    std::string hexOutput = "0x";
    for (char c : input) {
        hexOutput += toHexChar(static_cast<unsigned char>(c));
    }
    return hexOutput;
}

int main() {
    std::string input = "abc";
    std::string hexOutput = stringToHex(input);
    std::cout << "The hex representation of \"" << input << "\" is: " << hexOutput << std::endl;
    return 0;
}
*/