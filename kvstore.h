#ifndef KVS
#define KVS

#include "kvstore_api.h"
#include "./bloom.h"
#include "./JumpList.h"
#include "./TableCache.h"
#include "./LevelCache.h"
#include "./utils.h"
#include<vector>
#include<cstdlib>

/**
* key: uint64_t
* value: std::string
* KVpair: pair<uint64_t, std::string>
* directory: level-x  x:the level number
* file: lxfy.sst  x:the level number  y:the file number
**/
#define MAX_BYTES 2097152	//2*1024*1024=2097152
#define HEAD_BYTES 32
#define BF_BYTES 10240
#define KEY_BYTES 8
#define OFFSET_BYTES 4

class KVStore : public KVStoreAPI {
	// You can add your implementation here
private:
	bloom blo;
	JumpList jl;
	LevelCache cache;

	uint64_t memtable_size;			//内存tabel的估测字节数大小
	uint64_t timestamp;			    //下一个时间戳
	uint64_t keynum;


	void init_timestamp();
	void renew_timestamp();
	void init_filestamp();
	void init_levelcache();
	void memtable_write(); 
	void sstable_adjust();
	void sstable_select();
	void sstable_mergedown();
	void save();			//退出时保存
	void del_allfile();
	void del_fileandcache(string name);
	void add_file_cache(TableCache* tmp,uint64_t level);
	void write_file_fromjumplist();

public:
	KVStore(const std::string &dir);

	~KVStore();

	void put(uint64_t key, const std::string &s) override;

	std::string get(uint64_t key) override;

	bool del(uint64_t key) override;

	void reset() override;

	void scan(uint64_t key1, uint64_t key2, std::list<std::pair<uint64_t, std::string> > &list) override;
};

#endif