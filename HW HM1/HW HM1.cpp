
#include <iostream>
#include"task.h"

int main()
{
	std::ifstream file("XXX"); // путь к файлу PhoneBook.txt PhoneBook book(file);
	PhoneBook book;
	std::cout << book;
	std::cout << book;
	std::cout << "------SortByPhone-------" << std::endl;
	book.SortByPhone();
	std::cout << book;
	std::cout << "------SortByName--------" << std::endl;
	book.SortByName();
	std::cout << book;
	std::cout << "-----GetPhoneNumber-----" << std::endl;
	// лямбда функция, которая принимает фамилию и выводит номер телефона
	//человека, либо строку с ошибкой
		auto print_phone_number = [&book](const std::string& surname) {
			std::cout << surname << "\t";
		auto answer = book.GetPhoneNumber(surname);
		if (get<0>(answer).empty())
			std::cout << get<1>(answer);
		else
			std::cout << get<0>(answer);
		std::cout << std::endl;
	};
	// вызовы лямбды
	print_phone_number("Ivanov");
	print_phone_number("Petrov");
	std::cout << "----ChangePhoneNumber----" << std::endl;
	book.ChangePhoneNumber(Person{ "Kotov", "Vasilii", "Eliseevich" },
		PhoneNumber{ 7, 123, "15344458", std::nullopt });
	book.ChangePhoneNumber(Person{ "Mironova", "Margarita", "Vladimirovna" },
		PhoneNumber{ 16, 465, "9155448", 13 });
	std::cout << book;
}



