// 思路： bfs， 时间Onl，空间Onl，其中n为list中单词的数量，l为最长的单词长度 
// 1. 把头单词插入队列进行bfs，每次遍历队头单词的每个位置，判断替换为26个字母的新单词是否存在于wordlist中
// 2. 如果存在且路径不存在，则构造为下一层的结点
// 3. 如果碰到结尾单词，则返回最短路径

class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_map<string, int> dist;    //记录到达每个结点所需要的距离
        unordered_set<string> words;        //记录可以到达的结点
        for (auto& word : wordList) {
            words.insert(word);
        }
        queue<string> bfs_q;
        dist[beginWord] = 1;    //初始化，到达第一个节点所需要的距离为1
        bfs_q.push(beginWord);  //插入队列，开始bfs
        while (bfs_q.size()) {
            auto& word = bfs_q.front(); //取出队头
            auto front = word;
            for (int i = 0; i < front.size(); ++ i) {
                front = word;
                for (char j = 'a'; j <= 'z'; ++ j) {    //改变队头的每个字母，看看哪种情况存在结点
                    front[i] = j;
                    if (words.count(front) && !dist.count(front)) { //如果存在结点且没有在dist数组中，则表明当前走到新节点为最短的路径
                        dist[front] = dist[word] + 1;       //记录到达该结点的距离
                        if (front == endWord) {             //如果该节点为终点，则直接返回最短距离
                            return dist[endWord];
                        }
                        bfs_q.push(front);              //将当前节点作为下一层插入队列中
                    }
                }
            }
            bfs_q.pop();
        }
        return 0;       //如果没有符合的最短路径，返回0
    }
};