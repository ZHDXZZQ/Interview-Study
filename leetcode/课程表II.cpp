// 思路：拓扑排序， 时间On+m，空间On+m，其中n表示课程的个数，m表示先修关系的个数
// 1. 此题类似于拓扑排序，需要被先修的课程可以看做弧尾，需要后修的课程可以看做弧头，将所有的课程看做结点，每次找入度为0的结点（即没有被其他结点指向的结点）
// 2. 入度为0的结点就是需要被先修的课程，我们认为他现在可以被学习，学习之后将其加入结果中，然后就可以学习那些依赖于他的课程，然后找下一个入度为0的结点进行学习
// 3. 当把所有入度为0的结点学习完之后，如果学习的课程等于所有课程数量，则可以，否则不可以。

class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        if (prerequisites.empty()) {    //如果没有任何先后关系，则依次输出即可
            vector<int> res;
            for (int i = 0; i < numCourses; ++ i){
                res.push_back(i);
            }
            return res;
        }
        vector<int> in_points(numCourses, 0);   //存储每个节点的入度
        vector<vector<int>> edges(numCourses);  //存储边，即课程的先后关系
        for (auto& it : prerequisites) {        //构建图
            auto& prior = it[1];
            auto& last = it[0];
            edges[prior].push_back(last);
            ++ in_points[last];
        }
        queue<int> zero_in_points;          //存储入度为0的点
        for (int i = 0; i < numCourses; ++ i) {
            if (in_points[i] == 0) {
                zero_in_points.push(i);
            }
        }
        vector<int> res;
        while (!zero_in_points.empty()) {   //只要还有入度为0的点
            auto prior_course = zero_in_points.front(); //这里如果加引用，下面就不能先pop
            zero_in_points.pop();
            res.push_back(prior_course);    //将该课程插入结果中
            for (auto& course : edges[prior_course]) {  //遍历该课程的所有后继课程
                -- in_points[course];           //该课程的先修课程已学完
                if (in_points[course] == 0) {   //如果该课程已经没有先修课程
                    zero_in_points.push(course);    //则插入可学习队列中
                }
            }
        }
        if (res.size() == numCourses) { //如果结果的课程数量等有所有数量数
            return res;
        }
        return {};  //否则返回空
    }
};