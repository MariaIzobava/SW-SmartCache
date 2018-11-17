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

std::shared_ptr<User> factory(int id) {
	return std::make_shared<User>(id, Names[id % N], Mails[id % N]);
}

int main() {
	Cache<User> cache(factory);

	std::shared_ptr<User> ptr1, ptr2, ptr3, ptr4;
	ptr1 = cache[0];
	
	ptr2 = cache[1];

	ptr3 = cache[2];
	ptr4 = cache[3];
	ptr1 = cache[4];
	ptr1 = cache[0];
	ptr1 = cache[1];

	ptr1 = cache[2];
	ptr1 = cache[3];
	ptr1 = cache[4];
	getchar();

}
