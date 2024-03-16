// 思路：拓扑排序， 时间On+m，空间On+m，其中n表示课程的个数，m表示先修关系的个数
// 1. 此题类似于拓扑排序，需要被先修的课程可以看做弧尾，需要后修的课程可以看做弧头，将所有的课程看做结点，每次找入度为0的结点（即没有被其他结点指向的结点）
// 2. 入度为0的结点就是需要被先修的课程，我们认为他现在可以被学习，学习之后就可以学习那些依赖于他的课程，然后找下一个入度为0的结点进行学习
// 3. 当把所有入度为0的结点学习完之后，如果学习的课程等于所有可成，则可以，否则不可以。

class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<int> ind(numCourses, 0);             //用于存储每个结点的入度，初始化为0
        vector<vector<int>> edge(numCourses);       //用于存储边集，外层的vec的每个位置表示以该下标对应节点为弧尾的所有边，这样方便我们在找到入度为0的点时找到依赖其的点
        for (auto& vec : prerequisites) {           //遍历先修关系，填充边集和入度向量
            ++ ind[vec[0]];                         //依赖于其他课程的课程的入度+1
            edge[vec[1]].push_back(vec[0]);         //边集中被依赖课程的vec多一个依赖其的课程的下标
        }
        queue<int> zero_ind;                        //队列记录当前入度为0的点，开始拓扑排序。队列适用于所有需要边加入边判断的情况
        for (int i = 0; i < numCourses; ++ i) {     //如果当前点的入度为0，则入队
            if (ind[i] == 0) {
                zero_ind.push(i);
            }
        }
        int study_courses = 0;                      //已经学习的课程，即入度为0的结点
        while (zero_ind.size()) {                   //遍历队列，队列是不停往里加结点的，所以只要不空则循环
            int zero_point = zero_ind.front();      //取出队头任意结点，即可以现在学习的，入度为0，无先修课程的课程
            ++ study_courses;                       //学习该课程
            auto& edge_vec = edge[zero_point];      //取出依赖该课程的所有课程
            for (auto& point : edge_vec) {          
                -- ind[point];                      //该课程学习后，依赖该课程的课程需要先修的课程-1，即入度-1
                if (ind[point] == 0) {              //如果依赖该课程的课程入度为0，则入队
                    zero_ind.push(point);
                }
            }
            zero_ind.pop();                         //当前课程出队
        }
        return numCourses == study_courses;         //判断全部学习的课程是否等于所有课程
    }
};