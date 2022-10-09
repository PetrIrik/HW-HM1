#include"task.h"
#include<tuple>

std::ostream& operator<<(std::ostream out, const Person& person)
{
	 return out << person.LastName << " " << person.FirstName << " " << person.Patronymic.value_or("");
	
}

bool operator<(const Person& persbegin, const Person& persend)
{
	return std::tie(persbegin.LastName, persbegin.FirstName, persbegin.Patronymic) < std::tie(persend.LastName, persend.FirstName, persend.Patronymic);
}

bool operator==(const Person& persbegin, const Person& persend)
{
	return std::tie(persbegin.LastName, persbegin.FirstName, persbegin.Patronymic) == std::tie(persend.LastName, persend.FirstName, persend.Patronymic);
}

std::ostream& operator<<(std::ostream out, const PhoneNumber& PNum)
{
	return out << "+" << PNum.Ccountry << "(" << PNum.Ñcity << ")" << PNum.Number << PNum.Ex_Number.value_or("");
}

bool operator<(const PhoneNumber& PNumB, const PhoneNumber& PNumE)
{
	return std::tie(PNumB.Ccountry, PNumB.Ñcity, PNumB.Number, PNumB.Ex_Number) < std::tie(PNumE.Ccountry, PNumE.Ñcity, PNumE.Number, PNumE.Ex_Number);
}

bool operator==(const PhoneNumber& PNumB, const PhoneNumber& PNumE)
{
	return std::tie(PNumB.Ccountry, PNumB.Ñcity, PNumB.Number, PNumB.Ex_Number) == std::tie(PNumE.Ccountry, PNumE.Ñcity, PNumE.Number, PNumE.Ex_Number);
}

std::ostream operator<<(std::ostream out, PhoneBook PhBook)
{
	for (const auto& [person, number] : PhBook.record)
	{
		out << person << std::setw(5) << number << std::endl;
	}
	return out;
}

PhoneBook::PhoneBook(std::ifstream fstream)
{
	std::string LastName;
	std::string FirstName;
	std::optional<std::string>  Patronymic;
	int Ccountry;
	int Ñcity;
	std::string Number;
	std::optional<std::string> ext;
	std::optional<int> Ex_Number;

	if (fstream.is_open())
	{
		while (fstream>>LastName>>FirstName>>Patronymic.emplace() >> Ccountry>> Ñcity >>Number>>Ex_Number.emplace())
		{
			if (Patronymic.has_value())
			{
				if (Patronymic.value() == "-")
				{
					Patronymic = std::nullopt;
				}
			}
			Person person(LastName, FirstName, Patronymic);
			if (ext.has_value())
			{
				if (ext.value() == "-")
				{
					Ex_Number = std::stoi(ext.value());
				}
				else
				{
					Ex_Number.emplace() = std::stoi(ext.value());
				}
			}
			PhoneNumber phoneNum(Ccountry, Ñcity, Number, Ex_Number);

			record.push_back(std::make_pair(person, phoneNum));
		}
	}
	fstream.close();
}

void PhoneBook::SortByName()
{
	Less less;
	std::sort(record.begin(), record.end(), less);
}

void PhoneBook::SortByPhone()
{
	Less less(true);
	std::sort(record.begin(), record.end(), less);
}

std::tuple<std::string, PhoneNumber> PhoneBook::GetPhoneNumber(const std::string& LastName)
{
	PhoneNumber nubmer;
	std::string res = "";
	int count = 0;
	std::for_each(record.begin(), record.end(), 
		[&](const auto& rec)
		{
			if (rec.first.GetLasttname() == LastName)
			{
				nubmer = rec.second;
				count++;
			}
		});
	if (count == 0) 
	res = "not found";
	else if (count > 1) res = "found more than 1";
	return std::make_tuple(res, nubmer);
	

}

void PhoneBook::ChangePhoneNumber(const Person& person, const PhoneNumber& newPNum)
{
	auto find_rec = std::find_if(record.begin(), record.end(),
		[&person](const auto& rec)
		{
			return rec.first == person;
		});
	if (find_rec != record.end()) find_rec->second = newPNum;
}
