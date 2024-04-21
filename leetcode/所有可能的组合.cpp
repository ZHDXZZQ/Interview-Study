// 题目： 给定一个数组，内容比如[1,2,3,4,5]，输出所有数字的组合情况（注意不是全排列），给定数组的数字不重复。
// 比如给定[1,2,3]，输出结果为 12、23、13、123、1、2、3、空 
// 思路： dfs回溯，时间O2^n，空间On*2^n ，其中，n为数字的个数，结果一共有2的n次方，最长的字符串是所有数字的组合，
#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
using namespace std;

unordered_set<string> res;  //unordered_set方便无序插入
int n;

void dfs(int i, vector<int>& nums, string temp) {   //temp为临时结果
	res.insert(temp);   //先插入一次当前结果
	if (i == n) {       //如果遍历到最后了，则不做任何操作
		return;
	}
	for (int j = i + 1; j < n; ++ j) {  //否则从这个数往后遍历，可以避免重复
		temp += to_string(nums[j]);     //将当前这个数字插入结果中
		dfs(j, nums, temp);             //dfs补充后续数字
		temp.pop_back();                //将当前这个数字弹出，进行回溯，方便插入下一个数字
	}
}

int main() {
	vector<int> nums = {1, 2, 3};
	n = nums.size();
	for (int i = 0; i < n; ++ i) {
		string temp = to_string(nums[i]);
		dfs(i, nums, temp);         //进入递归
	}
	res.insert("");     //插入空结果的情况
	for (auto& str : res) {
		cout << str << endl;
	}
  	return 0;
}