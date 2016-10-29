#pragma once

#include <string>
#include <ostream>
class Account
{
public:
	//Account(std::string, std::string, std::string, std::string, bool);
	Account(std::string, bool);
//	~Account();
	std::string getEmail();
	bool isAdmin();
	void Report(std::ostream &);
private:
	std::string email;
	bool admin;
};

