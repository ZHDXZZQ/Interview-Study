// 思路： bfs广度优先搜索， 时间Onm，空间Omn，其中m为基因库中基因序列的数量，n为基因序列的长度
// 1. 对起始的基因序列的每个基因变换可能得到的情况，在基因库中且之前没有得到过则记录，此时记录的一定是最少的变化次数得到的序列
// 2. 依序对每种已经得到的基因序列做上述变化，知道得到结果
// 3. 具体看注释，宽搜利用队列，每次得到的一定都是最小值

class Solution {
public:
    int minMutation(string startGene, string endGene, vector<string>& bank) {
        int n = startGene.size();
        unordered_set<string> dictionary;   //存储bank中的所有基因序列，哈希表
        for (auto& gene : bank) {           
            dictionary.insert(gene);
        }
        queue<string> gene_q;       //宽搜用到的队列
        unordered_map<string, int> gene_steps;  //存储每种可得序列所需要的变化次数
        char chs[4] = {'A', 'C', 'G', 'T'}; //可变化的字符范围
        gene_steps[startGene] = 0;      //初始化，初始基因需要0次变化到达
        gene_q.push(startGene);         //初始化，插入原始基因序列
        while (gene_q.size()) {         //如果队不空
            auto& front_gene = gene_q.front();  //取出队头
            gene_q.pop();
            for (int i = 0; i < n; ++ i) {      //对基因序列中的每个基因尝试变换
                auto cur_gene = front_gene;
                for (int j = 0; j < 4; ++ j) {  //对每个位置进行变化的四种情况
                    char c = chs[j];
                    cur_gene[i] = c;
                    if (dictionary.count(cur_gene) && !gene_steps.count(cur_gene)) {        //如果当前变化后的基因在基因库中，并且之前没有出现过这种基因才去记录，否则已经被记录过或不存在基因库中都无需记录
                        gene_q.push(cur_gene);  //将当前基因插入队列中
                        gene_steps[cur_gene] = gene_steps[front_gene] + 1;  //记录当前基因所需变化次数（此时一定是最小的变化次数）
                        if (cur_gene == endGene) { return gene_steps[cur_gene]; }
                        // 如果变化得到了最终基因，则直接返回，一定是最少变化次数
                    }
                }
            }
        }
        return -1;
    }
};