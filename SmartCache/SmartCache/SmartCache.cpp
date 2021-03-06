// SmartCache.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include "cache.h"
#include "user.h"


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

int main() {
	Cache<int, User, std::function<std::shared_ptr<User>(int)> > cache(user_factory);

	std::shared_ptr<User> ptr1, ptr2, ptr3, ptr4 ;
	ptr1 = cache[0];
	
	ptr2 = cache[1];
	ptr3 = cache[0];
	ptr4 = cache[0];

	ptr1 = cache[2];
	ptr2 = cache[2];
	ptr3 = cache[1];
	ptr4 = cache[3];
	ptr4 = cache[3];
	ptr4 = cache[0];
	

	ptr1->print_user();
	ptr2->print_user();
	ptr3->print_user();
	ptr4->print_user();

	std::cout << "Total number of unique users is " << cache.get_cache_size() <<  std::endl;
	std::cout << "Total number of deleted users is " << cache.get_number_of_deleted_users() << std::endl;

	ptr4 = cache[2];
	std::cout << "Total number of deleted users is " << cache.get_number_of_deleted_users() << std::endl;

	getchar();

}
