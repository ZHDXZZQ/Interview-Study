//思路：从后往前一一插入nums1中，可以直接覆盖而不会丢失数据，避免了排序或复制操作。时间Om+n，空间O1

class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int pos_1 = m - 1;  //记录nums1和nums2当前参与比较的元素的下标
        int pos_2 = n - 1;
        m = m + n - 1;      //记录要插入到nums1中的位置
        while(pos_1 >= 0 && pos_2 >= 0 && m >= 0) { //将nums1或nums2的元素全部按顺序插入，当其中一个插完时，必然另一个未插完
            if(nums1[pos_1] > nums2[pos_2]) {  //选择更大的数插入
                nums1[m --] = nums1[pos_1 --];
            } else {
                nums1[m --] = nums2[pos_2 --];
            }
        }
        if(pos_1 < 0) {  //如果nums2没有插完，那需要补到前面，否则不需要补
            while(m >= 0) {
                nums1[m --] = nums2[pos_2 --];
            }
        }
    }
};