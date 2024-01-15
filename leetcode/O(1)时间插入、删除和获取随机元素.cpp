// 思路： 动手实现一个类，包含其成员变量和方法

class RandomizedSet {
public:
    RandomizedSet() {
        srand((unsigned)time(NULL)); //随机种子
    }
    
    bool insert(int val) {
        if(hash_map.find(val) != hash_map.end()) return false;   //如果集合中已有该数，则错误
        random_set.push_back(val);          //否则插入该数到集合中，并在map中记录位置
        hash_map[val] = random_set.size() - 1;
        return true;
    }
    
    bool remove(int val) {
        if(hash_map.find(val) == hash_map.end()) return false;
        int pos = hash_map[val];                                 //找到该数在集合中的位置
        random_set[pos] = random_set[random_set.size() - 1];        //将集合中末尾的数交换到pos处，后续resize掉最后一个相当于移除
        hash_map[random_set[pos]] = pos;                        //更新末尾移过来的数在map中的位置记录
        hash_map.erase(hash_map.find(val));                        //处理掉要删除的数的信息，并resize数组
        random_set.resize(random_set.size() - 1);
        return true;
    }
    
    int getRandom() {
        return random_set[rand() % random_set.size()]; //由种子取模找出随机位置所指向的数，这里在C++中不是严格随机，当数组大小超过32767时，后面的数无法被选取
    }

private:
    unordered_map<int, int> hash_map;   //记录每个数所在集合中的位置
    vector<int> random_set;             //集合
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */