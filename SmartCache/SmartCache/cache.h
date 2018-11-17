#include <map>
#include <iostream> 
#include <functional>
#include <algorithm>


template <class Tid, class Tobj, class TFactory>
class Cache {
private:
	std::map<int, std::weak_ptr<Tobj> > cache_table;
	TFactory factory_;
public:
	Cache() = delete;
	Cache(TFactory factory) : factory_(factory) {}
	~Cache() {}

	std::shared_ptr<Tobj> operator[] (int id) {
		auto it = cache_table.find(id);
		
		if (it == cache_table.end() || (it->second).lock() == nullptr) {
			if (it == cache_table.end()) {
				printf("There is no object with %d ID, let's create one\n", id);
			} 
			else {
				printf("Object with %d ID was deleted, we'll create it one more time\n", id);
			}
			std::shared_ptr<Tobj> ptr = factory_(id);
			cache_table[id] = std::weak_ptr<Tobj>(ptr);
			return ptr;
		}
		printf("Object with %d ID exists, return its pointer\n", id);
		return (it->second).lock();
		return nullptr;
	}

	size_t get_number_of_deleted_users() {
		size_t k = 0;
		std::for_each(cache_table.begin(), cache_table.end(), [&k](auto entry) {if (entry.second.lock() == nullptr) k++; });
		return k;
	}

	size_t get_cache_size() {
		return cache_table.size();
	}
};
