#include <map>
#include <iostream> 


template <class T>
class Cache {
private:
	std::map<int, std::weak_ptr<T> > cache_table;
	std::shared_ptr<T> (*factory_)(int id);
public:
	Cache() = delete;
	Cache(std::shared_ptr<T>(*factory)(int id)) : factory_(factory) {}
	~Cache() {}

	std::shared_ptr<T> operator[] (int id) {
		auto it = cache_table.find(id);
		
		if (it == cache_table.end() || (it->second).lock() == nullptr) {
			if (it == cache_table.end()) {
				printf("There is no object with %d ID, let's create one\n", id);
			} 
			else {
				printf("Object with %d ID was deleted, we'll create it one more time\n", id);
			}
			std::shared_ptr<T> ptr = factory_(id);
			cache_table[id] = std::weak_ptr<T>(ptr);
			return ptr;
		}
		printf("Object with %d ID exists, return its pointer\n", id);
		return (it->second).lock();
		return nullptr;
	}
};
