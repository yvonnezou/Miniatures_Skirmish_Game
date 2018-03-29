/**/
/*
/* This file include class role, class specialism, class captain,
/* class hierophant, class soldier, class squad, class package, class player
/* The functions in these classes are in this file
/*
*/
#include "item.h"
#include "util.h"

Role::Role(double health, double fight, RoleType roleType): health_(health), fight_(fight), roleType_(roleType){
}

Role::~Role(){
}

bool Role::isDead(){
	return health_ <= 0;
}

RoleType Role::getRoleType(){
	return roleType_;
}

bool Role::gainExperienceAfterWinning(){
	return false;
}

bool Role::gainExperienceAfterLosing(){
	return false;
}

bool Role::increaseFightAbility(){
	return false;
}

std::string Role::toDB(){
	stringstream ss;
	ss << health_ << " " << fight_ << " " << roleType_;

	string str = ss.str();
	return str;
}

std::string Role::status(){
	stringstream ss;
	if (roleType_ == CAPTAIN){
		ss << "Captain\t";
	}else if(roleType_ == HIEROPHANT){
		ss << "Hierophant\t";
	}else if(roleType_ == SOLDIER){
		ss << "Soldier\t";
	}
	ss << "Health: " << health_ << "\tFight: " << fight_ << "\t";

	string str = ss.str();
	return str;
}

Specialism::Specialism(double health, double fight, RoleType roleType, double experience, SpecialismTree specialism):
Role(health, fight, roleType), experience_(experience), specialism_(specialism){
}

bool Specialism::gainExperienceAfterWinning(){
	experience_ += 10;
	return true;
}

bool Specialism::gainExperienceAfterLosing(){
	experience_ += 2;
	return true;
}

bool Specialism::increaseFightAbility(){
	if (experience_ >= 10){
		experience_ -= 10;
		fight_ += fightToAdd;
		return true;
	}else{
		return false;
	}
}

std::string Specialism::toDB(){
	stringstream ss;
	ss << Role::toDB() << " " << experience_ << " " << specialism_;

	return ss.str();
}

std::string Specialism::status(){
	stringstream ss;
	ss << Role::status() << "Exp: " << experience_ << "\tSpecial: ";
	if (specialism_ == A){
		ss << "A";
	}else if(specialism_ == B){
		ss << "B";
	}

	return ss.str();
}

Captain::Captain(double health, double fight, double experience, SpecialismTree specialism):
Specialism(health, fight, CAPTAIN, experience, specialism){
}

Hierophant::Hierophant(double health, double fight, double experience, SpecialismTree specialism):
Specialism(health, fight, HIEROPHANT, experience, specialism){
}

Soldier::Soldier(double health, double fight):Role(health, fight, SOLDIER){
}

Squad::Squad(){
	maxSize = 10;
}

Squad::~Squad(){
}

Player::Player( Roster* roster, Squad* squad, int credit ): credit_(credit), roster_(roster), squad_(squad){
}

Player::~Player(){
	delete roster_;
	roster_ = NULL;
	delete squad_;
	squad_ = NULL;
}

bool Player::isRosterEmpty(){
	return roster_->isEmpty();
}

bool Player::isSquadEmpty(){
	return squad_->isEmpty();
}

bool Player::isRosterFull(){
	return roster_->isFull();
}

bool Player::isSquadFull(){
	return squad_->isFull();
}

int Player::getCurrentCredit(){
	return credit_;
}

void Player::addMemberToRoster( Role* role ){
	roster_->addMember(role);
}

void Player::addMemberToSquad( Role* role ){
	squad_->addMember(role);
}

void Player::addMemberToSquad( int idxInRoster ){
	--idxInRoster;
	Role * roleInRoster = roster_->removeMember(idxInRoster);
	squad_->addMember(roleInRoster);
}

void Player::removeMemberFromSquad( int idxInSquad ){
	--idxInSquad;
	Role * roleInSquad = squad_->removeMember(idxInSquad);
	roster_->addMember(roleInSquad);
}

void Player::switchMember( int idxInSquad, int idxInRoster ){
	--idxInSquad;
	--idxInRoster;
	Role * roleInSquad = squad_->removeMember(idxInSquad);
	Role * roleInRoster = roster_->removeMember(idxInRoster);
	squad_->addMember(idxInSquad, roleInRoster);
	roster_->addMember(idxInRoster, roleInSquad);
}

bool Player::buyNewMember( RoleType type ){
	switch(type){
	case CAPTAIN:{
		if (credit_ >= creditCostForCaptain){
			credit_ -= creditCostForCaptain;
			addMemberToRoster(Utils::generateNewCaptain(defaultHealthOfCaptain, defaultFightOfCaptain));
		}else{
			return false;
		}
		break;
				 }
	case HIEROPHANT:{
		if (credit_ >= creditCostForHierophant){
			credit_ -= creditCostForHierophant;
			addMemberToRoster(Utils::generateNewHierophant(defaultHealthOfHierophant, defaultFightOfHierophant));
		}else{
			return false;
		}
		break;
					}
	case SOLDIER:{
		if (credit_ >= creditCostForSoldier){
			credit_ -= creditCostForSoldier;
			addMemberToRoster(Utils::generateNewSoldier(defaultHealthOfSoldier, defaultFightOfSoldier));
		}else{
			return false;
		}
		break;
				}
	default:{
		return false;
			}
	}

	return true;
}

bool Player::sellMemberInRoster( int idxInRoster ){
	--idxInRoster;
	Role * roleInRoster = roster_->removeMember(idxInRoster);
	switch(roleInRoster->getRoleType()){
	case CAPTAIN:{
		credit_ += creditCostForCaptain;
		return true;
				 }
	case HIEROPHANT:{
		credit_ += creditCostForHierophant;
		return true;
					}
	case SOLDIER:{
		credit_ += creditCostForSoldier;
		return true;
				 }
	default:{
		return false;
			}
	}
}

bool Player::increaseFightAbility( int idxInSquad ){
	--idxInSquad;
	return squad_->increaseFightAbility(idxInSquad);
}

bool Role::fight(Role * enemyRole){
	while(true){
		double rate = Utils::randomBetween(1, 100);
		double rateOfEnemy = Utils::randomBetween(1, 100);
		double attackToEnemy = fight_ * rate / 100;
		double attackFromEnemy = enemyRole->fight_ * rateOfEnemy / 100;
		enemyRole->health_ -= attackToEnemy;
		if (enemyRole->isDead()){
			return true;
		}else{
			health_ -= attackFromEnemy;
			if (isDead()){
				return false;
			}
		}
	}
}

bool Squad::fight( Squad * enemySquad ){
	bool win = false;
	int sizeOfSquad = getCurrentSize();
	int sizeOfEnemySquad = enemySquad->getCurrentSize();
	int cIdxOfSquad = 0;
	int cIdxOfEnemy = 0;

	while(cIdxOfSquad < sizeOfSquad && cIdxOfEnemy < sizeOfEnemySquad){
		Role* cSquad = roleVec[cIdxOfSquad];
		Role* cEnemy = enemySquad->roleVec[cIdxOfEnemy];
		if(cSquad->fight(cEnemy)){
			++cIdxOfEnemy;
		}else{
			++cIdxOfSquad;
		}
	}

	delete enemySquad;
	win = (cIdxOfSquad != sizeOfSquad);
	return win;
}

void Squad::removeDead(){
	for(vector<Role *>::iterator it= roleVec.begin(); it != roleVec.end(); ){
		if((*it)->isDead()) {
			Role * cRole = *it;
			it = roleVec.erase(it);
			delete cRole;
		}else{
			++it;
		}
	}
}

void Squad::gainExperience(){
	int size = roleVec.size();
	for (int i = 0; i < size; ++i){
		Role* cRole = roleVec[i];
		cRole->gainExperienceAfterWinning();
	}
}

bool Squad::increaseFightAbility( int idx ){
	return roleVec[idx]->increaseFightAbility();
}

bool Player::fight(Squad * enemySquad){
	bool result = squad_->fight(enemySquad);
	if (!result){
		squad_->freeMemory();
	}else{
		squad_->removeDead();
		squad_->gainExperience();
		gainCredit();
	}

	return result;
}

std::string Player::currentStatusOfRoster(){
	return roster_->status();
}

std::string Player::currentStatusOfSquad(){
	return squad_->status();
}

void Player::gainCredit(){
	credit_ += 50;
}

std::string Player::toDB(){
	stringstream ss;
	ss << credit_ << endl;
	ss << roster_->toDB();
	ss << squad_->toDB();

	string str = ss.str();
	return str;
}

Roster::Roster(){
	maxSize = 20;
}

Roster::~Roster(){
}

Package::Package(){
}

Package::~Package(){
	freeMemory();
	roleVec.clear();
}

bool Package::isFull(){
	return roleVec.size() == maxSize;
}

bool Package::isEmpty(){
	return roleVec.empty();
}

int Package::getCurrentSize(){
	return roleVec.size();
}

void Package::addMember( Role * role ){
	roleVec.push_back(role);
}

void Package::addMember( int idx , Role * role){
	roleVec.insert(roleVec.begin() + idx, role);
}

void Package::shuffleTeam(){
	random_shuffle(roleVec.begin(), roleVec.end());
}

Role * Package::removeMember( int idx ){
	Role * target = roleVec[idx];
	roleVec.erase(roleVec.begin() + idx);
	return target;
}

std::string Package::toDB(){
	stringstream ss;
	int size = getCurrentSize();
	ss << size << endl;
	for (int i = 0 ; i < size; ++i){
		ss << roleVec[i]->toDB() << endl;
	}
	
	string str = ss.str();
	return str;
}

std::string Package::status(){
	int size = getCurrentSize();
	stringstream ss;
	if(size != 0){
		for (int i = 0 ; i < size; ++i){
			ss << "[" << (i + 1) << "] " << roleVec[i]->status() << endl;
		}
	}else{
		ss << "[empty]" << endl;
	}

	string str = ss.str();
	return str;
}

void Package::freeMemory(){
	int size = roleVec.size();
	for (int i = 0 ; i < size; ++i){
		delete roleVec[i];
	}
}
