#ifndef LC
#define LC

#include<list>
#include <cstdint>
#include<vector>
#include<cmath>
#include"./TableCache.h"
enum ssmode{Tiering,Leveling};
using namespace std;

class LevelCache{
    struct levelcache{
        ssmode mode;
        uint64_t level;
        uint64_t maxnum;
        uint64_t nownum;
        list<TableCache> data;
        levelcache(uint64_t lev,ssmode mo=Leveling){ 
            level=lev; 
            nownum=0; 
            maxnum=pow(2,level+1);
            mode=mo;
        }
        void inserttable(TableCache* obj);
        void removetable(string delname);
        void clear();
    };

    private:
    vector<levelcache> cache_list;
    vector<uint64_t> filestamps;                          //
    uint64_t size;

    public:
    ~LevelCache(){}
    LevelCache(){ size=0; }
    void restart();
    void addLevlevel();
    void inserttable(TableCache* obj,uint64_t level);    // 0base
    void removetable(string delname,uint64_t level);    // 0base
    uint64_t getlevelnum(){ return(size);}
    uint64_t getfilestamp(uint64_t lev){ return(filestamps[lev]); }
};

#endif