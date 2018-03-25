#include "account.h"

UserAccount::UserAccount(int id, const string& name, const string& password): id_(id),
	name_(name), password_(password){
}

int UserAccount::getID(){
	return id_;
}

std::string UserAccount::getName(){
	return name_;
}

std::string UserAccount::getPassword(){
	return password_;
}

void UserAccount::setPassword(const string& password){
	password_ = password;
}

std::string UserAccount::toDB(){
	stringstream ss;
	ss << id_ << " " << name_ << " " << password_;

	return ss.str();
}

