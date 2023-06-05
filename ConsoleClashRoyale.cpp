#include <iostream>
#include <vector>
#include <map>
#include <ctime>
#include <string>
#include <windows.h>

using namespace std;

HANDLE hConsole;
int randomNumber(int maxNumber) {
  srand(time(0));
  return rand() % maxNumber;
}
void printColorized(string text, int colorNumber) {
  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(hConsole, colorNumber);
  cout << text << endl;
  SetConsoleTextAttribute(hConsole, 7);
}

class IOInterface {
public:
  virtual istream& citire(istream& in) = 0;
  virtual ostream& afisare(ostream& out) const = 0;  

};

class Card: public IOInterface {
protected:
  string name;
  string rarity;
  int mana;
  int level;
  int demage;
  int cardsAmount;
  int cardsAmountForUpgrade;
  int upgradePrice;
public:
//constructors
  Card();
  Card(string, string, int, int);
  Card(const Card&);
//operators
  Card& operator=(const Card&);
  virtual istream& citire(istream&);
  friend istream& operator>>(istream&, Card&);
  virtual ostream& afisare(ostream&) const;
  friend ostream& operator<<(ostream&, const Card&);
//getters
  string getName();
  string getRarity();
  int getMana();
  int getLevel();
  int getDemage();
  int getCardsAmount();
  int getCardsAmountForUpgrade();
  int getUpgradePrice();
//setters
  void setName(string);
  void setRarity(string);
  void setMana(int);
  void setLevel(int);
  void setDemage(int);
  void setCardsAmount(int);
  void setCardsAmountForUpgrade(int);
  void setUpgradePrice(int);
//methods
  virtual Card* clone() const;
  virtual void upgrade();
  void increaseCardsAmount(int);
  bool isUpgradable();
};
//constructors
Card::Card() {
  this->name = "undefined";
  this->rarity = "undefined";
  this->mana = 0;
  this->level = 0;
  this->demage = 0;
  this->cardsAmount = 0;
  this->cardsAmountForUpgrade = 0;
  this->upgradePrice = 0;
}
Card::Card(string name, string rarity, int mana, int demage) {
  this->name = name;
  this->rarity = rarity;
  this->mana = mana;
  this->demage = demage;

  if (rarity == "common")
    this->level = 1;
  else if (rarity == "rare")
    this->level = 3;
  else if (rarity == "epic")
    this->level = 6;
  else if (rarity == "legendary")
    this->level = 9;
  else if (rarity == "champion")
    this->level = 11;

  this->upgradePrice = (1<<this->level) * 10 + 100;
  this->cardsAmount = 0;
  this->cardsAmountForUpgrade = (1<<this->level)*5 + 100;
}
Card::Card(const Card& card) {
  this->name = card.name;
  this->rarity = card.rarity;
  this->mana = card.mana;
  this->level = card.level;
  this->demage = card.demage;
  this->cardsAmount = card.cardsAmount;
  this->cardsAmountForUpgrade = card.cardsAmountForUpgrade;
  this->upgradePrice = card.upgradePrice;
}
//operators
Card& Card::operator=(const Card& card) {
  if (this != &card) {
    this->name = card.name;
    this->rarity = card.rarity;
    this->mana = card.mana;
    this->level = card.level;
    this->demage = card.demage;
    this->cardsAmount = card.cardsAmount;
    this->cardsAmountForUpgrade = card.cardsAmountForUpgrade;
    this->upgradePrice = card.upgradePrice;
  }
  return *this;
}
ostream& Card::afisare(ostream& out) const {
  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  cout << "_______________________\n";
  SetConsoleTextAttribute(hConsole, 5);
  out << "<" << this->level << "> ";
  SetConsoleTextAttribute(hConsole, 7);
  out << this->name;  
  SetConsoleTextAttribute(hConsole, 3);
  out << " (" << this->rarity << ")" << endl;
  SetConsoleTextAttribute(hConsole, 1);
  out << this->mana << " mana\n";
  SetConsoleTextAttribute(hConsole, 4);
  out << this->demage << " demage\n";
  SetConsoleTextAttribute(hConsole, 2);
  out << this->cardsAmount << '/' << this->cardsAmountForUpgrade << endl;
  SetConsoleTextAttribute(hConsole, 6);
  out << this->upgradePrice << " gold\n";
  SetConsoleTextAttribute(hConsole, 7);
  cout << "_______________________\n\n";
  return out;
}
ostream& operator<<(ostream& out, const Card& card) {
  return card.afisare(out);
}
istream& Card::citire(istream& in) {
  cout << "Name: ";
  in >> this->name;
  cout << "Rarity (common, rare, epic, legendary): ";
  in >> this->rarity;
  while (this->rarity != "common" && this->rarity != "rare" && this->rarity != "epic" && this->rarity != "legendary") {
    cout << "Invalid rarity! Rarity (common, rare, epic, legendary): ";
    in >> this->rarity;
  }
  cout << "Mana: ";
  in >> this->mana;
  cout << "Demage: ";
  in >> this->demage;

  if (rarity == "common")
    this->level = 1;
  else if (rarity == "rare")
    this->level = 3;
  else if (rarity == "epic")
    this->level = 6;
  else if (rarity == "legendary")
    this->level = 9;
  else if (rarity == "champion")
    this->level = 11;

  this->upgradePrice = (1<<this->level) * 10 + 100;
  this->cardsAmount = 0;
  this->cardsAmountForUpgrade = (1<<this->level) + 100;
  return in;
}
istream& operator>>(istream& in, Card& card) {
  return card.citire(in);
}
//getters
string Card::getName() {
  return this->name;
}
string Card::getRarity() {
  return this->rarity;
}
int Card::getMana() {
  return this->mana;
}
int Card::getLevel() {
  return this->level;
}
int Card::getDemage() {
  return this->demage;
}
int Card::getCardsAmount() {
  return this->cardsAmount;
}
int Card::getCardsAmountForUpgrade() {
  return this->cardsAmountForUpgrade;
}
int Card::getUpgradePrice() {
  return this->upgradePrice;
}
//setters
void Card::setName(string name) {
  this->name = name;
}
void Card::setRarity(string rarity) {
  this->rarity = rarity;
}
void Card::setMana(int mana) {
  this->mana = mana;
}
void Card::setLevel(int level) {
  this->level = level;
}
void Card::setDemage(int demage) {
  this->demage = demage;
}
void Card::setCardsAmount(int cardsAmount) {
  this->cardsAmount = cardsAmount;
}
void Card::setCardsAmountForUpgrade(int cardsAmountForUpgrade) {
  this->cardsAmountForUpgrade = cardsAmountForUpgrade;
}
void Card::setUpgradePrice(int upgradePrice) {
  this->upgradePrice = upgradePrice;
}
//methods
void Card::increaseCardsAmount(int nr) {
  this->cardsAmount += nr;
}
bool Card::isUpgradable() {
  return this->cardsAmount > this->cardsAmountForUpgrade;
}
Card* Card::clone() const {
  // cout << "Card::clone()\n";
  return new Card(*this);
}
void Card::upgrade() {
  this->level++;
  this->demage += this->demage / 10;
  this->upgradePrice = (1<<this->level) * 10 + 1000;
  this->cardsAmount -= this->cardsAmountForUpgrade;
  this->cardsAmountForUpgrade += (1<<this->level) * 5 + 100;
}
//end


class Troop: virtual public Card {
protected:
  int hitpoints;
  float attackSpeed;
  float range;
  string speed;
public:
//constructors
  Troop();
  Troop(string, string, int, int, int, float, float, string);
  Troop(const Troop&);
//operators
  Troop& operator=(const Troop&);
  ostream& afisare(ostream&) const;
  istream& citire(istream&);
//getters
  int getHitpoints();
  float getAttackSpeed();
  float getRange();
  string getSpeed();
//setters
  void setHitpoints(int);
  void setAttackSpeed(float);
  void setRange(float);
  void setSpeed(string);
//methods
  Troop* clone() const;
  void upgrade(); //increase demage and hitpoints
};
//constructors
Troop::Troop():Card(){
  this->hitpoints = 0;
  this->attackSpeed = 0;
  this->range = 0;
  this->speed = "undefined";
}
Troop::Troop(string name, string rarity, int mana, int demage, int hitpoints, float attackSpeed, float range, string speed):
  Card(name, rarity, mana, demage) {
    this->hitpoints = hitpoints;
    this->attackSpeed = attackSpeed;
    this->range = range;
    this->speed = speed;
  }
Troop::Troop(const Troop& troop):Card(troop) {
  this->hitpoints = troop.hitpoints;
  this->attackSpeed = troop.attackSpeed;
  this->range = troop.range;
  this->speed = troop.speed;
}
//operators
Troop& Troop::operator=(const Troop& troop) {
  if (this != &troop) {
    Card::operator=(troop);
    this->hitpoints = troop.hitpoints;
    this->attackSpeed = troop.attackSpeed;
    this->range = troop.range;
    this->speed = troop.speed;
  }
  return *this;
}
ostream& Troop::afisare(ostream& out) const{
  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  cout << "_______________________\n";
  SetConsoleTextAttribute(hConsole, 5);
  out << "<" << this->level << "> ";
  SetConsoleTextAttribute(hConsole, 7);
  out << this->name;  
  SetConsoleTextAttribute(hConsole, 3);
  out << " (" << this->rarity << ")" << endl;
  SetConsoleTextAttribute(hConsole, 1);
  out << this->mana << " mana\n";
  SetConsoleTextAttribute(hConsole, 4);
  out << this->demage << " demage\n";
  out << this->hitpoints << " hitpoints\n";
  out << this->attackSpeed << " attack speed\n";
  if (this->range)
    out << this->range << " range\n";
  else
    out << "melee range\n";
  out << this->speed << " speed\n";
  SetConsoleTextAttribute(hConsole, 2);
  out << this->cardsAmount << '/' << this->cardsAmountForUpgrade << endl;
  SetConsoleTextAttribute(hConsole, 6);
  out << this->upgradePrice << " gold\n";
  SetConsoleTextAttribute(hConsole, 7);
  cout << "_______________________\n\n";
  return out;
}
istream& Troop::citire(istream& in) {
  Card::citire(in);
  cout << "Hitpoints: ";
  in >> this->hitpoints;
  cout << "Attack Speed: ";
  in >> this->attackSpeed;
  cout << "Range: ";
  in >> this->range;
  cout << "Speed (Slow, Medium, Fast, Very Fast): ";
  in >> this->speed;
  while(this->speed != "Slow" && this->speed != "Medium" && this->speed != "Fast" && this->speed != "Very Fast") {
    cout << "Invalid Speed! Speed (Slow, Medium, Fast, Very Fast): ";
    in >> this->speed;
  }
  return in;
}

//getters
int Troop::getHitpoints() {
  return this->hitpoints;
}
float Troop::getAttackSpeed() {
  return this->attackSpeed;
}
float Troop::getRange() {
  return this->range;
}
string Troop::getSpeed() {
  return this->speed;
}
//setters
void Troop::setHitpoints(int hitpoints) {
  this->hitpoints = hitpoints;
}
void Troop::setAttackSpeed(float attackSpeed) {
  this->attackSpeed = attackSpeed;
}
void Troop::setRange(float range) {
  this->range = range;
}
void Troop::setSpeed(string speed) {
  this->speed = speed;
}
//methods
Troop* Troop::clone() const {
  // cout << "Troop::clone()\n";
  return new Troop(*this);
}
void Troop::upgrade() {
  Card::upgrade();
  this->hitpoints += this->hitpoints / 10;
}
//end


class Spell: virtual public Card {
protected:
  float duration;
  float stunDuration;
  float slowdownPercent;
  float radius;
public:
//constructors
  Spell();
  Spell(string, string, int, int, float, float, float, float);
  Spell(const Spell&);
//operators
  Spell& operator=(const Spell&);
  ostream& afisare(ostream&) const;
  istream& citire(istream&);
//getters
  float getDuration();
  float getStunDuration();
  float getSlowdownPercent();
  float getRadius();
//setters
  void setDuration(float);
  void setStunDuration(float);
  void setSlowdownPercent(float);
  void setRadius(float);
//methods
  Spell* clone() const;
  void upgrade(); // increase demage and duration 
};
//constructors
Spell::Spell():Card() {
  this->duration = 0;
  this->stunDuration = 0;
  this->slowdownPercent = 0;
  this->radius = 0;
}
Spell::Spell(string name, string rarity, int mana, int demage, float duration, float stunDuration, float slowdownPercent, float radius):
  Card(name, rarity, mana, demage) {
    this->duration = duration;
    this->stunDuration = stunDuration;
    this->slowdownPercent = slowdownPercent;
    this->radius = radius;
  }
Spell::Spell(const Spell& spell):Card(spell) {
  this->duration = spell.duration;
  this->stunDuration = spell.stunDuration;
  this->slowdownPercent = spell.slowdownPercent;
  this->radius = spell.radius;
}
//operators
Spell& Spell::operator=(const Spell& spell) {
  if (this != &spell) {
    Card::operator=(spell);
    this->duration = spell.duration;
    this->stunDuration = spell.stunDuration;
    this->slowdownPercent = spell.slowdownPercent;
    this->radius = spell.radius;
  }
  return *this;
}
ostream& Spell::afisare(ostream& out) const{
   hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  cout << "_______________________\n";
  SetConsoleTextAttribute(hConsole, 5);
  out << "<" << this->level << "> ";
  SetConsoleTextAttribute(hConsole, 7);
  out << this->name;  
  SetConsoleTextAttribute(hConsole, 3);
  out << " (" << this->rarity << ")" << endl;
  SetConsoleTextAttribute(hConsole, 1);
  out << this->mana << " mana\n";
  SetConsoleTextAttribute(hConsole, 4);
  out << this->demage << " demage\n";
  if (this->duration)
    out << this->duration << " duration\n";
  if (this->stunDuration)
    out <<this->stunDuration << " stun duration\n";
  if (this->slowdownPercent)
    out << this->slowdownPercent << "%% slowdown\n";
  if (this->radius)
    out << this->radius << " radius\n";
  SetConsoleTextAttribute(hConsole, 2);
  out << this->cardsAmount << '/' << this->cardsAmountForUpgrade << endl;
  SetConsoleTextAttribute(hConsole, 6);
  out << this->upgradePrice << " gold\n";
  SetConsoleTextAttribute(hConsole, 7);
  cout << "_______________________\n\n";
  return out;
}
istream& Spell::citire(istream& in) {
  Card::citire(in);
  cout << "Duration: ";
  cin >> this->duration;
  cout << "Stun Duration: ";
  cin >> this->stunDuration;
  cout << "Slowdown Percent: ";
  cin >> this->slowdownPercent;
  cout << "Radius: ";
  cin >> this->radius;
  return in;
}
//getters
float Spell::getDuration() {
  return this->duration;
}
float Spell::getStunDuration() {
  return this->stunDuration;
}
float Spell::getSlowdownPercent() {
  return this->slowdownPercent;
}
float Spell::getRadius() {
  return this->radius;
}
//setters
void Spell::setDuration(float duration) {
  this->duration = duration;
}
void Spell::setStunDuration(float stunDuration) {
  this->stunDuration = stunDuration;
}
void Spell::setSlowdownPercent(float slowdownPercent) {
  this->slowdownPercent = slowdownPercent;
}
void Spell::setRadius(float radius) {
  this->radius = radius;
}
//methods
Spell* Spell::clone() const {
  return new Spell(*this);
}
void Spell::upgrade() {
  Card::upgrade();
  this->duration += 0.3;
}
//end


// Goblin barrel, Barbarian Barrel, Graveyard, Mega Knight
class MixedCard: virtual public Troop, virtual public Spell {
  float spawnSpeed;
  int troopsAmount;
public:
//constructors
  MixedCard();
  MixedCard(string, string, int, int, int, float, float, string, float, float, float, float, float, int);
  MixedCard(const MixedCard&);
//operators
  MixedCard& operator=(const MixedCard&);
  ostream& afisare(ostream&) const;
  istream& citire(istream&);
//getters
  float getSpawnSpeed();
  int getTroopsAmount();
//setters
  void setSpawnSpeed(float);
  void setTroopsAmount(int);
//methods
  MixedCard* clone() const;
  void upgrade(); // increase troopLevel
};
//constructors
MixedCard::MixedCard():Card(), Troop(), Spell() {
  this->spawnSpeed = 0;
  this->troopsAmount = 0;
}
MixedCard::MixedCard(string name, string rarity, int mana, int demage, int hitpoints, float attackSpeed, float range, string speed, float duration, float stunDuration, float slowdownPercent, float radius, float spawnSpeed, int troopsAmount):
  Card(name, rarity, mana, demage),
  Troop(name, rarity, mana, demage, hitpoints, attackSpeed, range, speed),
  Spell(name, rarity, mana, demage, duration, stunDuration, slowdownPercent, radius) {
    this->spawnSpeed = spawnSpeed;
    this->troopsAmount = troopsAmount;
  }
MixedCard::MixedCard(const MixedCard& mixedCard):Card(mixedCard), Troop(mixedCard), Spell(mixedCard){
  this->spawnSpeed = mixedCard.spawnSpeed;
  this->troopsAmount = mixedCard.troopsAmount;
}
//operators
MixedCard& MixedCard::operator=(const MixedCard& mixedCard) {
  if (this != &mixedCard) {
    Card::operator=(mixedCard);
    Troop::operator=(mixedCard);
    Spell::operator=(mixedCard);
    this->spawnSpeed = mixedCard.spawnSpeed;
    this->troopsAmount = mixedCard.troopsAmount;
  }
  return *this;
}
ostream& MixedCard::afisare(ostream& out) const{
  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  cout << "_______________________\n";
  SetConsoleTextAttribute(hConsole, 5);
  out << "<" << this->level << "> ";
  SetConsoleTextAttribute(hConsole, 7);
  out << this->name;  
  SetConsoleTextAttribute(hConsole, 3);
  out << " (" << this->rarity << ")" << endl;
  SetConsoleTextAttribute(hConsole, 1);
  out << this->mana << " mana\n";
  SetConsoleTextAttribute(hConsole, 4);
  out << this->demage << " demage\n";
  out << this->hitpoints << " hitpoints\n";
  out << this->attackSpeed << " attack speed\n";
  if (this->range)
    out << this->range << " range\n";
  else
    out << "melee range\n";

  out << this->speed << " speed\n";
   if (this->duration)
    out << this->duration << " duration\n";
  if (this->stunDuration)
    out <<this->stunDuration << " stun duration\n";
  if (this->slowdownPercent)
    out << this->slowdownPercent << "%% slowdown\n";
  if (this->radius)
    out << this->radius << " radius\n";
  
  if (this->spawnSpeed)
    out << this->spawnSpeed << " spawn speed\n";
  if (this->troopsAmount > 1)
    out << this->troopsAmount << " troops\n";

  SetConsoleTextAttribute(hConsole, 2);
  out << this->cardsAmount << '/' << this->cardsAmountForUpgrade << endl;
  SetConsoleTextAttribute(hConsole, 6);
  out << this->upgradePrice << " gold\n";
  SetConsoleTextAttribute(hConsole, 7);
  cout << "_______________________\n\n";
  return out;
}
istream& MixedCard::citire(istream& in) {
  Troop::citire(in);
  cout << "Duration: ";
  cin >> this->duration;
  cout << "Stun Duration: ";
  cin >> this->stunDuration;
  cout << "Slowdown Percent: ";
  cin >> this->slowdownPercent;
  cout << "Radius: ";
  cin >> this->radius;
  cout << "Troops Amount: ";
  cin >> this->troopsAmount;
  cout << "Spawn Speed: ";
  cin >> this->spawnSpeed;
  return in;
}
//getters
float MixedCard::getSpawnSpeed() {
  return this->spawnSpeed;
}
int MixedCard::getTroopsAmount() {
  return this->troopsAmount;
}
//setters
void MixedCard::setSpawnSpeed(float spawnSpeed) {
  this->spawnSpeed = spawnSpeed;
}
void MixedCard::setTroopsAmount(int troopsAmount) {
  this->troopsAmount = troopsAmount;
}
//methods
MixedCard* MixedCard::clone() const {
  return new MixedCard(*this);
}
void MixedCard::upgrade() {
  Troop::upgrade();
  this->duration += 0.3;
}
//end

class Player {
  string username;
  int trophies;
  int arena;
  int trophiesRequiredForNextArena;
  int level;
  int xp;
  int xpForNextLevel;
  int gold;
  int gems;
  int chests;
  vector<Card*> cards;

public:
//constructors
  Player();
  Player(string);
  Player(string, int, int, int, int, int, int, int, int, int, vector<Card*>);
  Player(const Player&);
//operators
friend ostream& operator<<(ostream&, const Player&);
//getters
  string getUsername();
  int getTrophies();
  int getArena();
  int getTrophiesRequiredForNextArena();
  int getLevel();
  int getXp();
  int getXpForNextLevel();
  int getGold();
  int getGems();
  int getChests();
  int getCardsNumber();
  Card* getCard(int);
//setters
  void setUsername(string);
  void setTrophies(int);
  void setArena(int);
  void setTrophiesRequiredForNextArena(int);
  void setLevel(int);
  void setXp(int);
  void setXpForNextLevel(int);
  void setGold(int);
  void setGems(int);
  void setChests(int);
  void setCard(int, Card*);
//methods
private:
  void rewardPlayer();
  void checkArena();
  void penalizePlayer();
public:
  void playGame();
  void openChest(vector<Card*>);
  void upgradeCard(int);
  void showAllCards();
  bool showUpgradableCards();
//destructor
  ~Player();
};
//constructors
Player::Player() {
  this->username = "undefined";
  this->trophies = 0;
  this->arena = 0;
  this->trophiesRequiredForNextArena = 0;
  this->level = 0;
  this->xp = 0;
  this->xpForNextLevel = 0;
  this->gold = 0;
  this->gems = 0;
  this->chests = 0;
}
Player::Player(string username) {
  this->username = username;
  this->trophies = 0;
  this->arena = 1;
  this->trophiesRequiredForNextArena = 400;
  this->level = 1;
  this->xp = 0;
  this->xpForNextLevel = 2000;
  this->gold = 100;
  this->gems = 10;
  this->chests = 4;
}
Player::Player(string username, int trophies, int arena, int trophiesRequiredForNextArena, int level, int xp, int xpForNextLevel, int gold, int gems, int chests, vector<Card*> cards) {
  this->username = username;
  this->trophies = trophies;
  this->arena = arena;
  this->trophiesRequiredForNextArena = trophiesRequiredForNextArena;
  this->level = level;
  this->xp = xp;
  this->xpForNextLevel = xpForNextLevel;
  this->gold = gold;
  this->gems = gems;
  this->chests = chests;
  this->cards = cards;
} 
Player::Player(const Player& player) {
  this->username = player.username;
  this->trophies = player.trophies;
  this->arena = player.arena;
  this->trophiesRequiredForNextArena = player.trophiesRequiredForNextArena;
  this->level = player.level;
  this->xp = player.xp;
  this->xpForNextLevel = player.xpForNextLevel;
  this->gold = player.gold;
  this->gems = player.gems;
  this->chests = player.chests;
  this->cards = player.cards;
}
//operators
ostream& operator<<(ostream& out, const Player& player) {
  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(hConsole, 3);
  cout << "[level " << player.level << " | " << player.xp << "/" << player.xpForNextLevel << "] ";
  SetConsoleTextAttribute(hConsole, 8);
  cout <<  player.username;
  SetConsoleTextAttribute(hConsole, 6);
  cout  << " [" << player.trophies << " trophies]\n";
  SetConsoleTextAttribute(hConsole, 6);
  cout << player.gold << " gold\n";
  SetConsoleTextAttribute(hConsole, 2);
  cout << player.gems << " gems\n";
  SetConsoleTextAttribute(hConsole, 5);
  cout << "arena " << player.arena << endl;
  cout << player.chests << " chests\n";
  cout << player.cards.size() << " cards\n";
  SetConsoleTextAttribute(hConsole, 7);
  
}
//getters
string Player::getUsername() {
  return this->username;
}
int Player::getTrophies() {
  return this->trophies;
}
int Player::getArena() {
  return this->arena;
}
int Player::getTrophiesRequiredForNextArena() {
  return this->trophiesRequiredForNextArena;
}
int Player::getLevel() {
  return this->level;
}
int Player::getXp() {
  return this->xp;
}
int Player::getXpForNextLevel() {
  return this->xpForNextLevel;
}
int Player::getGold() {
  return this->gold;
}
int Player::getGems() {
  return this->gems;
}
int Player::getChests() {
  return this->chests;
}
int Player::getCardsNumber() {
  return this->cards.size();
}
Card* Player::getCard(int cardIndex) {
  return this->cards[cardIndex];
}
//setters
void Player::setUsername(string username) {
  this->username = username;
}
void Player::setTrophies(int trophies) {
  this->trophies = trophies;
}
void Player::setArena(int arena) {
  this->arena = arena;
}
void Player::setTrophiesRequiredForNextArena(int trophiesRequiredForNextArena) {
  this->trophiesRequiredForNextArena = trophiesRequiredForNextArena;
}
void Player::setLevel(int level) {
  this->level = level;
}
void Player::setXp(int xp) {
  this->xp = xp;
}
void Player::setXpForNextLevel(int xpForNextLevel) {
  this->xpForNextLevel = xpForNextLevel;
}
void Player::setGold(int gold) {
  this->gold = gold;
}
void Player::setGems(int gems) {
  this->gems = gems;
}
void Player::setChests(int chests) {
  this->chests = chests;
}
void Player::setCard(int cardIndex, Card* card) {
  this->cards[cardIndex] = card;
}
//methods
void Player::rewardPlayer() {
  printColorized("You won!", 2);
  this->trophies += 30;
  cout << "+30 trophies\n";

  this->gold += 50;
  cout << "+50 gold\n";
  
  if (this->chests < 4) {
    cout << "+1 chest\n";
    this->chests += 1;
  }
}
void Player::checkArena() {
  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  if (this->trophies >= this->trophiesRequiredForNextArena && this->arena < 15) {
    this->arena++;
    this->trophiesRequiredForNextArena += 400;
    SetConsoleTextAttribute(hConsole, 2);
    cout << "You have reached arena " << this->arena << endl;
  }
  else if (this->trophies < this->trophiesRequiredForNextArena - 400) {
    this->arena--;
    this->trophiesRequiredForNextArena -= 400; 
    SetConsoleTextAttribute(hConsole, 4);
    cout << "You went down to arena " << this->arena << endl;
  }
  SetConsoleTextAttribute(hConsole, 7);
}
void Player::penalizePlayer() {
  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(hConsole, 4);
  cout << "You lost!\n";
  SetConsoleTextAttribute(hConsole, 7);
  if (this->trophies > 20) {
    this->trophies -= 20; 
    cout << "-20 trophies\n";
  }
  else
    this->trophies = 0;
  SetConsoleTextAttribute(hConsole, 7);
}
void Player::playGame() {
  if (randomNumber(3)) {
    rewardPlayer();
  }
  else {
    penalizePlayer();
  }
  checkArena();
}
void Player::openChest(vector<Card*> totalGameCards) {
    //daca playeru are chesturi
    if (this->chests > 0) {
      this->chests--;
      int randomCardIndex = randomNumber(totalGameCards.size()); // alegem un nr random de la 0 la nr de carduri din joc
      int cardAmount = 100 - randomNumber(20); // alegem un nr random intre 100 si 81
      int goldAmount = 200 - randomNumber(50);
      this->gold += goldAmount;

      string cardName = totalGameCards[randomCardIndex]->getName();

      int cardIndex = 0;
      while (cardIndex < this->cards.size() && this->cards[cardIndex]->getName() != cardName)
        cardIndex++;

      if (cardIndex < this->cards.size()) // daca nu e prima data cand primeste cardul
        this->cards[cardIndex]->increaseCardsAmount(cardAmount); // incrementam nr de carduri;
      else {
        this->cards.push_back(totalGameCards[randomCardIndex]->clone()); // adaugam in lista de carduri
        this->cards[cards.size()-1]->increaseCardsAmount(cardAmount); //incrementam nr de carduri
      }
      cout << "You got " << goldAmount << " gold and " << cardAmount << " " << cardName << " cards!\n"; 
    }
    else
      cout << "You don't have any chests.\n";
  }
void Player::upgradeCard(int index) {
  //daca avem bani si carduri pentru a face upgrade-ul
  if (this->gold >= this->cards[index]->getUpgradePrice() && this->cards[index]->isUpgradable()) { 
    this->cards[index]->upgrade();
    cout << *cards[index];
    int xpReceived = 2 << this->cards[index]->getLevel() + 100;
    this->xp += xpReceived;
    while (this->xp >= this->xpForNextLevel) { 
      this->xp -= this->xpForNextLevel;
      this->level++;
      this->xpForNextLevel = 2000 + this->xpForNextLevel * 14 / 10;
      cout << "You reached level " << this->level << endl;
      cout << this->xp << '/' << this->xpForNextLevel << " up to the next level\n";
    }
  }
  else 
    cout << "Not enough cards\n";
}
void Player::showAllCards() {
  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  if (this->cards.size() == 0) {
    printColorized("You don't have any cards!", 4);
  }
  for (int i = 0; i < this->cards.size(); i++) {
    cout << *(this->cards[i]);
  }
}
bool Player::showUpgradableCards() {
  bool playerHasUpgradableCards = false;
  for (int i = 0; i < this->cards.size(); i++) {
    if (this->cards[i]->isUpgradable() && this->cards[i]->getUpgradePrice() <= this->gold) {
      cout << "(" << i << ") " << cards[i]->getCardsAmount() << "/" << cards[i]->getCardsAmountForUpgrade() << " ";
      cout << cards[i]->getName() << " - " << cards[i]->getUpgradePrice() << " gold" << endl;
      playerHasUpgradableCards = true;
    }
  }
  return playerHasUpgradableCards;
}
//destructor
Player::~Player() {
  for(int i = 0; i < this->cards.size(); i++) {
    delete this->cards[i];
  }
}
//end



//app methods
void loadGameCards(vector<Card*>& gameCards) {
  gameCards.push_back(new Troop("Electro Spirit", "common", 1, 39, 90, 0.3, 2.5, "Very Fast"));
  gameCards.push_back(new Troop("Fire Spirit", "common", 1, 89, 90, 0.3, 2.5, "Very Fast"));
  gameCards.push_back(new Troop("Ice Spirit", "common", 1, 43, 90, 0.3, 2.5, "Very Fast"));
  gameCards.push_back(new Troop("Skeletons", "common", 1, 32, 32, 1, 0, "Very Fast"));
  gameCards.push_back(new Troop("Bats", "common", 2, 32, 32, 1.3, 0, "Very Fast"));
  gameCards.push_back(new Troop("Spear Goblins", "common", 2, 32, 52, 1.7, 5, "Very Fast"));
  gameCards.push_back(new Troop("Elite Barbarians", "common", 6, 300, 1048, 1.4, 0, "Fast"));
  gameCards.push_back(new Troop("Royal Giant", "common", 6, 120, 1200, 1.7, 5, "Slow"));

  gameCards.push_back(new Troop("Ice Golem", "rare", 2, 40, 565, 2.5, 0, "Slow"));
  gameCards.push_back(new Troop("Mega Minion", "rare", 3, 146, 395, 1.6, 0, "Medium"));
  gameCards.push_back(new Troop("Hog Rider", "rare", 4, 150, 800, 1.6, 0, "Very Fast"));
  gameCards.push_back(new Troop("Valkyrie", "rare", 4, 126, 900, 1.5, 0, "Medium"));
  gameCards.push_back(new Troop("Wizard", "rare", 5, 133, 340, 1.5, 5.5, "Medium"));
  gameCards.push_back(new Troop("Giant", "rare", 5, 120, 1930, 1.5, 0, "Slow"));

  gameCards.push_back(new Troop("Hunter", "epic", 4, 431, 520, 2.2, 4, "Medium"));
  gameCards.push_back(new Troop("Baby Dragon", "epic", 4, 123, 613, 1.4, 3.5, "Medium"));
  gameCards.push_back(new Troop("Executioner", "epic", 5, 235, 550, 2.1, 4.5, "Medium"));
  gameCards.push_back(new Troop("Prince", "epic", 5, 315, 812, 1.4, 0, "Very Fast"));
  gameCards.push_back(new Troop("Golem", "epic", 8, 195, 3200, 2.5, 0, "Slow"));

  gameCards.push_back(new Troop("Princess", "legendary", 3, 105, 210, 1.6, 12, "Medium"));
  gameCards.push_back(new Troop("Miner", "legendary", 3, 87, 830, 1.2, 0, "Fast"));
  gameCards.push_back(new Troop("Lumberjack", "legendary", 4, 214, 790, 0.8, 0, "Very Fast"));
  gameCards.push_back(new Troop("Lava Hound", "legendary", 7, 53, 2800, 0.8, 3, "Slow"));

  gameCards.push_back(new Spell("Zap", "common", 2, 75, 0, 0.5, 0, 2.5));
  gameCards.push_back(new Spell("Arrows", "common", 3, 112, 0, 0, 0, 3.5));
  gameCards.push_back(new Spell("Earthquake", "rare", 3, 68, 3, 0, 50, 3.5));
  gameCards.push_back(new Spell("Fireball", "rare", 4, 325, 0, 0, 0, 2.5));
  gameCards.push_back(new Spell("Poison", "epic", 4, 90, 8, 0, 15, 3.5));
  gameCards.push_back(new Spell("Freeze", "epic", 4, 112, 6, 6, 0, 3.5));
  gameCards.push_back(new Spell("The Log", "legendary", 2, 120, 3, 1, 0, 2.5));

  gameCards.push_back(new MixedCard("Goblin Barrel", "epic", 3, 12, 100, 1.3, 0, "Fast", 0, 0, 0, 4.5, 0.3, 3));
  gameCards.push_back(new MixedCard("Electro Wizzard", "Legendary", 4, 105, 210, 1.6, 12, "Medium", 0, 1, 0, 2, 0, 1));
  gameCards.push_back(new MixedCard("Graveyard", "legendary", 5, 45, 100, 1.3, 0, "Fast", 7, 0, 0, 4.5, 0.3, 21));
  gameCards.push_back(new MixedCard("Mega Knight", "legendary", 7, 130, 4100, 1.9, 0, "Slow", 0, 1, 0, 2, 0, 1));
}
int getNumberInput(int maxNumber) {
  int numberInput;
  cout << "-> ";
  cin >> numberInput;
  while (numberInput < 0 || numberInput > maxNumber) {
    cout << "Invalid operation! Try again.\n";
    cout << "-> ";
    cin >> numberInput;
  }
  return numberInput;
}

int main() {
  vector<Player*> players;
  vector<Card*> gameCards;
  loadGameCards(gameCards);

  while (true) {
    int numberInput;
    string stringInput;
    system("CLS");
    cout << "(1) Join Game\n";
    cout << "(2) Enter admin panel\n";
    cout << "(0) Leave\n";

    numberInput = getNumberInput(2);

    if (numberInput == 0) {
      break;
    }
    else if (numberInput == 1) {
      cout << "Enter your username.\n-> ";
      cin >> stringInput;
      Player* player;
      int playerIndex = 0;
      while (playerIndex < players.size() && players[playerIndex]->getUsername() != stringInput)
        playerIndex++;
      if (playerIndex < players.size())
        player = players[playerIndex];
      else {
        player = new Player(stringInput);
        players.push_back(player);
      }
      
      while (true) {
        cout << "\n(1) Play Game\n";
        cout << "(2) Show Stats\n";
        cout << "(3) Show Cards\n";
        cout << "(4) Open Chest\n";
        cout << "(5) Upgrade Card\n";
        cout << "(0) Log out\n";

        numberInput = getNumberInput(5);
        system("CLS");
        if (numberInput == 0) {
          break;
        }
        else if (numberInput == 1) {
          player->playGame();
        }
        else if (numberInput == 2) {
          cout << *player;
        }
        else if (numberInput == 3) {
          player->showAllCards();
        }
        else if (numberInput == 4) {
          player->openChest(gameCards);
        }
        else if (numberInput == 5) {
          bool playerHasUpgradableCards = player->showUpgradableCards();
          if (playerHasUpgradableCards) {
            cout << "Pick the card you want to upgrade.\n";
            numberInput = getNumberInput(player->getCardsNumber() - 1);
            while (!player->getCard(numberInput)->isUpgradable()) {
              cout << "Can't upgrade that card! Pick another one\n";
              numberInput = getNumberInput(player->getCardsNumber() - 1);
            }
            system("CLS");
            player->upgradeCard(numberInput);
          }
          else
            cout << "No upgradable cards\n";
        }
      }
    }
    else if (numberInput == 2) {
      while (true) {
        cout << "(1) Add New Card\n";
        cout << "(2) Show all cards\n";
        cout << "(0) Go back\n";

        numberInput = getNumberInput(2);
        if (numberInput == 0)
          break;
        else if (numberInput == 1) {
          Card* newCard;
          cout << "Pick the card type.\n";
          cout << "(1) Troop\n(2) Spell\n(3) Mixed Card\n(0) Go back\n";
          numberInput = getNumberInput(3);
          if (numberInput == 1) {
            newCard = new Troop;
          }
          else if (numberInput == 2) {
            newCard = new Spell;
          }
          else if (numberInput == 3) {
            newCard = new MixedCard;
          }
          else {
            break;
          }
          cin >> *newCard;
          gameCards.push_back(newCard);
        }
        else if (numberInput == 2) {
          for (int i = 0; i < gameCards.size(); i++) {
            cout << *gameCards[i];
          }
        }
      }
    }
  }
}