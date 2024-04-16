#include "kvstore.h"
#include <string>

KVStore::KVStore(const std::string &dir): KVStoreAPI(dir),blo(10),jl()
{
	memtable_size=HEAD_BYTES+BF_BYTES;
	keynum=0;
	init_levelcache();
	init_timestamp();
	init_filestamp();
}

KVStore::~KVStore()
{
	save();
}

/**
 * Insert/Update the key-value pair.
 * No return values for simplicity.
 */
void KVStore::put(uint64_t key, const std::string &s)
{


}
/**
 * Returns the (string) value of the given key.
 * An empty string indicates not found.
 */
std::string KVStore::get(uint64_t key)
{

	return "";
}
/**
 * Delete the given key-value pair if it exists.
 * Returns false iff the key is not found.
 */
bool KVStore::del(uint64_t key)
{

	return false;
}

/**
 * This resets the kvstore. All key-value pairs should be removed,
 * including memtable and all sstables files.
 */
void KVStore::reset()
{
	del_allfile();
	blo.clear();
	jl.clear();
	cache.restart();
	timestamp=1;
	keynum=0;
	memtable_size=HEAD_BYTES+BF_BYTES;

}

/**
 * Return a list including all the key-value pair between key1 and key2.
 * keys in the list should be in an ascending order.
 * An empty string indicates not found.
 */
void KVStore::scan(uint64_t key1, uint64_t key2, std::list<std::pair<uint64_t, std::string> > &list)
{	


}


void KVStore::init_timestamp(){
	
}

void KVStore::renew_timestamp(){
	++timestamp;
}

void KVStore::init_filestamp(){

}

void KVStore::init_levelcache(){

}

void KVStore::memtable_write(){

}

void KVStore::sstable_adjust(){

}

void KVStore::sstable_select(){

}

void KVStore::sstable_mergedown(){

}

void KVStore::save(){
	
}

void KVStore::del_allfile(){

}

void KVStore::del_fileandcache(string name){	//缓存文件名统一不带后缀
	string levelstr=name.substr(name.find_first_of("l")+1,name.find_first_of("f")-name.find_first_of("l")-1);
	string road="./level-"+levelstr+"/"+name+".sst";
	utils::rmfile(road.c_str());
	cache.removetable(name,stoi(levelstr));
}

void KVStore::add_file_cache(TableCache *tmp,uint64_t level){
	while(cache.getlevelnum()<level+1){cache.addLevlevel();}	//若插入所在层为未创建的层，则创建新层
	uint64_t filestamp=cache.getfilestamp(level);				//获取由缓存管理的层级文件戳
	string filename="l" + to_string(level) +"f"+to_string(filestamp);
	tmp->name=filename;
	cache.inserttable(tmp,level);
}

void KVStore::write_file_fromjumplist(){

}