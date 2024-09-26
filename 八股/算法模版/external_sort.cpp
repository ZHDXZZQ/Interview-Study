/*
    外部排序用于处理无法完全放入内存的数据集。常见的方法是使用归并排序，特别适合处理大文件。

    外部排序的步骤
        分块：将大文件分割成多个小文件（块），每个块可以完全放入内存。
        内部排序：对每个块进行内部排序（例如使用快速排序或归并排序），然后将每个排序后的块写入临时文件。
        归并：将所有排序后的块归并成一个最终的排序文件。

    在实际应用中，需要处理异常和错误（如文件打开失败）。
    这段代码假设输入文件只包含整数，每个整数占一行。
    你可以根据自己的需求调整 chunkSize 的大小，以适应可用的内存。
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

// 合并两个已排序的文件
void mergeFiles(ifstream &f1, ifstream &f2, ofstream &out) {
    int num1, num2;
    bool read1 = f1 >> num1;
    bool read2 = f2 >> num2;

    while (read1 && read2) {
        if (num1 < num2) {
            out << num1 << endl;
            read1 = f1 >> num1;
        } else {
            out << num2 << endl;
            read2 = f2 >> num2;
        }
    }

    while (read1) {
        out << num1 << endl;
        read1 = f1 >> num1;
    }

    while (read2) {
        out << num2 << endl;
        out << num2 << endl;
        read2 = f2 >> num2;
    }
}

// 外部排序函数
void ExternalSort(const string &inputFile, const string &outputFile, int chunkSize) {
    vector<string> tempFiles;
    ifstream input(inputFile);
    int num;

    // Step 1: 分块排序
    while (input) {
        vector<int> numbers;
        for (int i = 0; i < chunkSize && input >> num; ++i) {
            numbers.push_back(num);
        }

        // 排序并写入临时文件
        if (!numbers.empty()) {
            sort(numbers.begin(), numbers.end());
            string tempFile = "temp" + to_string(tempFiles.size()) + ".txt";
            ofstream tempOut(tempFile);
            for (int number : numbers) {
                tempOut << number << endl;
            }
            tempOut.close();
            tempFiles.push_back(tempFile);
        }
    }

    // Step 2: 归并排序
    while (tempFiles.size() > 1) {
        vector<string> mergedFiles;

        for (size_t i = 0; i < tempFiles.size(); i += 2) {
            if (i + 1 < tempFiles.size()) {
                string mergedFile = "merged" + to_string(mergedFiles.size()) + ".txt";
                ifstream f1(tempFiles[i]);
                ifstream f2(tempFiles[i + 1]);
                ofstream out(mergedFile);
                mergeFiles(f1, f2, out);
                f1.close();
                f2.close();
                out.close();
                mergedFiles.push_back(mergedFile);
            } else {
                mergedFiles.push_back(tempFiles[i]);
            }
        }
        tempFiles = mergedFiles; // 更新临时文件列表
    }

    // Step 3: 将最终结果写入输出文件
    ifstream finalInput(tempFiles[0]);
    ofstream output(outputFile);
    while (finalInput >> num) {
        output << num << endl;
    }

    finalInput.close();
    output.close();
}

int main() {
    string inputFile = "input.txt"; // 输入文件名
    string outputFile = "output.txt"; // 输出文件名
    int chunkSize = 100; // 每个块的大小（可以根据内存限制进行调整）

    ExternalSort(inputFile, outputFile, chunkSize);
    return 0;
}
