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
				std::cout << "There is no object with " << id <<" ID, let's create one\n";
			} 
			else {
				std::cout << "Object with " << id << " ID was deleted, we'll create it one more time\n";
			}
			std::shared_ptr<Tobj> ptr = factory_(id);
			cache_table[id] = std::weak_ptr<Tobj>(ptr);
			return ptr;
		}
		std::cout << "Object with " << id << " ID exists, return its pointer\n";
		return (it->second).lock();
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
