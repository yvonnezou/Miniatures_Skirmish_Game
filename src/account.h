/**/
/*
/* This file include the class related to user's account
/* All functions needing to use user's personal information are in this file
/*
*/

#ifndef _ACCOUNT_H
#define _ACCOUNT_H

#include "common_header.h"

class UserAccount{
public:
	UserAccount(int id, const string& name, const string& password);
	int getID();
	string getName();
	string getPassword();
	void setPassword(const string& password);

	string toDB();
private:
	int id_;
	string name_;
	string password_;
};

#endif