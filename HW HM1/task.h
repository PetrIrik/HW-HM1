#pragma once

#include<iostream>
#include<optional>
#include <string>
#include<vector>
#include <iomanip>
#include<algorithm>
#include <fstream>

//struct SPerson
//{
//	std::string FirstName;
//	std::string LastName;
//	std:optional<std::string> Patronymic;
//};

class Person
{
public:
	Person(const std::string FName, const std::string LName, const std::optional<std::string>Patr)
		:FirstName(FName), LastName(LName), Patronymic(Patr) 
	{};

	std::string GetFirstname() { return FirstName; }
	std::string GetLasttname() { return LastName; }
	std::optional<std::string> GetPatr() { return Patronymic; }

	friend std::ostream& operator<<(std::ostream out, const Person& person);
	friend bool operator< (const Person& persbegin, const Person& persend);
	friend bool operator==(const Person& persbegin, const Person& persend);
	~Person();

private:
	std::string FirstName;
	std::string LastName;
	std::optional<std::string>  Patronymic;
};

class PhoneNumber
{
private:
	int Ccountry;
	int Ñcity;
	std::string Number;
	std::optional<int> Ex_Number;
public:
	PhoneNumber() = default;
	PhoneNumber(const int COD_CN, const int COD_CY, const std::string NUM, const std::optional<int>EX_NUM)
		: Ccountry(COD_CN), Ñcity(COD_CY), Number(NUM), Ex_Number(EX_NUM)
	{};

	int getCountry() { return Ccountry; }
	int getCity() { return Ñcity; }
	std::string getNumber() { return Number; }
	std::optional<int> getEX_Number() { return Ex_Number; }

	friend std::ostream& operator<<(std::ostream out, const PhoneNumber& PNum);
	friend bool operator< (const PhoneNumber& PNumB, const PhoneNumber& PNumE);
	friend bool operator== (const PhoneNumber& PNumB, const PhoneNumber& PNumE);
};

class PhoneBook
{
private:
	std::vector<std::pair<Person, PhoneNumber>>record;
public:
	PhoneBook(std::ifstream fstr);

	void SortByName();
	void SortByPhone();
	
	std::tuple<std::string, PhoneNumber> GetPhoneNumber(const std::string& LastName);

	void ChangePhoneNumber(const Person& person, const PhoneNumber& newPNum);

	friend std::ostream operator<<(std::ostream out, PhoneBook PhBook);
};

class Less
{
private:
	bool sortByPhone;

public:
	Less(bool flag = false) : sortByPhone(flag)
	{};

	bool operator() (const std::pair<Person, PhoneNumber>& left, const std::pair<Person, PhoneNumber>& right)
	{
		if (left.first == right.first || sortByPhone)
			return left.second < right.second;
		else return left.first < right.first;
	}
};