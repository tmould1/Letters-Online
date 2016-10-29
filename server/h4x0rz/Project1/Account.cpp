#include "Account.h"



Account::Account(std::string inEmail, bool inAdmin)
{
	email = inEmail;
	admin = inAdmin;
}

std::string Account::getEmail() {
	return email;
}

bool Account::isAdmin() {
	return admin;
}

void Account::Report(std::ostream & oStrm) {
	oStrm << getEmail() << std::endl;
	oStrm << isAdmin() << std::endl;
}
