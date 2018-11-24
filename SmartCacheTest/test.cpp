#include "pch.h"
#include "../SmartCache/SmartCache/cache.h"
#include "../SmartCache/SmartCache/user.h"

const size_t N = 6;

const std::string Names[] = {
	"Masha",
	"Vadim",
	"Mark",
	"Vanya",
	"Anton",
	"Misha"
};

const std::string Mails[] = {
	"masha@gmail.com",
	"vadim@gmail.com",
	"mark@gmail.com",
	"vanya@gmail.com",
	"anton@gmail.com",
	"misha@gmail.com",
};

std::shared_ptr<User> user_factory(int id) {
	return std::make_shared<User>(id, Names[id % N], Mails[id % N]);
}

Cache<int, User, std::function<std::shared_ptr<User>(int)> > cache(user_factory);

TEST(CreateUsers, OneToMany) {
	
	std::shared_ptr<User> ptr1, ptr2;
	ptr1 = cache[0];
	ptr2 = cache[0];
	ASSERT_EQ(cache.get_cache_size(), 1);
}

TEST(CreateUsers, ManyToMany) {

	std::shared_ptr<User> ptr1, ptr2;
	ptr1 = cache[0];
	ptr2 = cache[1];
	ASSERT_EQ(cache.get_cache_size(), 2);
}

TEST(CreateUsers, ManyToOne) {

	std::shared_ptr<User> ptr1;
	ptr1 = cache[0];
	ptr1 = cache[1];
	ASSERT_EQ(cache.get_cache_size(), 2);
}

TEST(CreateUsers, DeletedUsers) {

	std::shared_ptr<User> ptr1;
	ptr1 = cache[0];
	ptr1 = cache[1];
	ptr1 = cache[2];
	ptr1 = cache[3];
	ptr1 = cache[4];
	ASSERT_EQ(cache.get_number_of_deleted_users(), 4);
}
