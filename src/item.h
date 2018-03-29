/**/
/*
/* This file include class role, class specialism, class captain, 
/* class hierophant, class soldier, class squad, class package, class player
/* These classes mainly responsible for operations with squad and its members
/*
*/
#ifndef _ITEM_H_
#define _ITEM_H_

#include "common_header.h"

enum SpecialismTree{
	A, B
};

enum RoleType{
	CAPTAIN, HIEROPHANT, SOLDIER
};

class Role{
public:
	Role(double health, double fight, RoleType roleType);
	virtual ~Role();

	bool isDead();
	RoleType getRoleType();

	virtual bool gainExperienceAfterWinning();
	virtual bool gainExperienceAfterLosing();
	virtual bool increaseFightAbility();

	virtual string toDB();
	virtual string status();

	bool fight(Role * enemyRole);
protected:
	double health_;
	double fight_;
	RoleType roleType_;
};

class Specialism: public Role{
public:
	Specialism(double health, double fight, RoleType roleType, double experience, SpecialismTree specialism);
	bool gainExperienceAfterWinning();
	bool gainExperienceAfterLosing();
	bool increaseFightAbility();

	string toDB();
	string status();
protected:
	double experience_;
	SpecialismTree specialism_;
};

class Captain: public Specialism{
public:
	Captain(double health, double fight, double experience, SpecialismTree specialism);
};

class Hierophant:public Specialism{
public:
	Hierophant(double health, double fight, double experience, SpecialismTree specialism);
};

class Soldier: public Role{
public:
	Soldier(double health, double fight);
};

class Package{
public:
	Package();
	virtual ~Package();

	bool isFull();
	bool isEmpty();
	int getCurrentSize();
	void addMember(Role * role);
	Role * removeMember(int idx);
	void addMember(int idx, Role * role);

	void shuffleTeam();

	string toDB();
	string status();

	void freeMemory();

protected:
	vector<Role *> roleVec;
	int maxSize;
};

class Squad: public Package{
public:
	Squad();
	~Squad();

	bool fight(Squad * enemySquad);
	void removeDead();
	void gainExperience();
	bool increaseFightAbility(int idx);
};

class Roster: public Package{
public:
	Roster();
	~Roster();
};

class Player{
public:
	Player(Roster* roster, Squad* squad, int credit = 500);
	~Player();

	bool isRosterEmpty();
	bool isSquadEmpty();
	bool isRosterFull();
	bool isSquadFull();
	int getCurrentCredit();

	string currentStatusOfRoster();
	string currentStatusOfSquad();

	void gainCredit();
	string toDB();

	void addMemberToRoster(Role* role);
	void addMemberToSquad(Role* role);
	void switchMember(int idxInSquad, int idxInRoster);
	void addMemberToSquad(int idxInRoster);
	void removeMemberFromSquad(int idxInSquad);

	bool buyNewMember(RoleType type);
	bool sellMemberInRoster(int idxInRoster);

	bool increaseFightAbility(int idxInSquad);

	bool fight(Squad * enemySquad);

private:
	int credit_;
	Roster* roster_;
	Squad* squad_;
};

#endif