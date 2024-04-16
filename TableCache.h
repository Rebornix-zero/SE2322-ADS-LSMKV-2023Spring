#ifndef TC
#define TC

#include<vector>
#include<string>
using namespace std;

class TableCache{
public:
    string name;
    uint64_t timestamp;
    uint64_t storenum;
    uint64_t maxkey;
    uint64_t minkey;
    char* bloom;
    vector<pair<uint64_t,uint64_t>> key_offset_pairs;   //first is key,second is offset
    ~TableCache(){ delete[]bloom; }
    TableCache(){ bloom=new char[10240]; }
};

#endif