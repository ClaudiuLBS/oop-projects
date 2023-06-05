#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <list>
#include <string>

using namespace std;

class App;

class StandardUser {
protected:
  string username;
  string password;
  unsigned subscriptionPrice;
  unsigned daysLeft;
  vector<string> projectsOnApp;
  App* app;
  static unsigned lastId;
  const unsigned id;

public:
//constructors
  StandardUser();
  StandardUser(string, string);
  StandardUser(const StandardUser&);
  StandardUser& operator=(const StandardUser&);
//citire
  virtual istream& citire(istream& in);
  friend istream& operator>>(istream& in, StandardUser& user);
//afisare
  virtual ostream& afisare(ostream& out) const;
  friend ostream& operator<<(ostream& out, const StandardUser& user);
//getters
  string getUsername();
  string getProject(unsigned);
  int getProjectsCount();
  int getSubscriptionPrice();
  int getDaysLeft();
//setters
  void setUsername(string);
  void passDay();
//methods
  void resubscribeToApp();
  void createProject(string);
  void removeProject(string);
  void listProjects();
  bool checkPassword(string);
  virtual string getUserType() const;
private:
  void onUserCreated();
};


class PremiumUser: public StandardUser {
protected:
  list<string> contacts;
public:
//constructors
PremiumUser();
PremiumUser(string, string);
PremiumUser(const PremiumUser&);
PremiumUser& operator=(const PremiumUser&);
//citire
  virtual istream& citire(istream& in);
  friend istream& operator>>(istream& in, PremiumUser& user);
//afisare
  virtual ostream& afisare(ostream& out) const;
  friend ostream& operator<<(ostream& out, const PremiumUser& user);
//getters
  list<string> getContacts();
//methods
  void addContact(string);
  void removeContact(string);
  void listContacts();
  virtual string getUserType() const;
};


class UltimateUser: public PremiumUser {
private:
  set<string> plugins;
public:
//constructors
  UltimateUser();
  UltimateUser(string, string);
  UltimateUser(const UltimateUser&);
  UltimateUser& operator=(const UltimateUser&);
//citire
  istream& citire(istream& in);
  friend istream& operator>>(istream& in, UltimateUser& user);
//afisare
  ostream& afisare(ostream& out) const;
  friend ostream& operator<<(ostream& out, const UltimateUser& user);
//getters
  set<string> getPlugins();
//methods
  void addPlugin(string);
  void removePlugin(string);
  void listPlugins();
  string getUserType() const;
};


class App {
private:
  static App* app;
  int usersNumber;
  map<StandardUser*, bool> activeUsers;
//constructors
  App();
  App(const App&) = delete;
  App& operator=(const App&) = delete;
public:
  static App* getInstance();
  void setUserActivity(StandardUser* user, bool isActive);
  void nextDay();
  StandardUser* login(string, string);
};

//CLASS APP
App* App::app = 0;
App::App() {
  this->usersNumber = 0;
}
App* App::getInstance() {
  if (!app)
    app = new App();
  return app;
}
void App::setUserActivity(StandardUser* user, bool isActive) {
  activeUsers[user] = isActive;
}
void App::nextDay() {
  for (auto it = this->activeUsers.begin(); it != this->activeUsers.end(); it++) {
    it->first->passDay();
  }
}
StandardUser* App::login(string username, string password) {
  for (auto it = this->activeUsers.begin(); it != this->activeUsers.end(); it++) {
    if (it->first->getUsername() == username)
      if (it->first->checkPassword(password))
        return it->first;
      else {
        cout << "Invalid password\n";
        return nullptr;
      }
  }
  cout << "Invalid username\n";
  return nullptr;
}


//CLASS STANDARD USER
//constructors
unsigned StandardUser::lastId = 0;
void StandardUser::onUserCreated() {
  this->app = this->app->getInstance();
  app->setUserActivity(this, true);
  this->daysLeft = 1;
}
StandardUser::StandardUser(): subscriptionPrice(10), username("undefined"), password("undefined"), id(++lastId) {
  onUserCreated();
}
StandardUser::StandardUser(string username, string password): subscriptionPrice(10), id(++lastId) {
  this->username = username;
  this->password = password;
  onUserCreated();
}
StandardUser::StandardUser(const StandardUser& user): id(++lastId) {
  this->username = user.username;
  this->password = user.password;
  this->subscriptionPrice = user.subscriptionPrice;
  this->daysLeft = user.daysLeft;
  this->projectsOnApp = user.projectsOnApp;
  this->app = user.app;
}
StandardUser& StandardUser::operator=(const StandardUser& user) {
  if (this != &user) {
    this->username = user.username;
    this->password = user.password;
    this->subscriptionPrice = user.subscriptionPrice;
    this->daysLeft = user.daysLeft;
    this->projectsOnApp = user.projectsOnApp;
    this->app = user.app;
  }
  return *this;
}
//citire
istream& StandardUser::citire(istream& in) {
  cout << "Username: ";
  in >> this->username;
  cout << "Password: ";
  in >> this->password;

  char input;
  string project;

  while (true) {
    cout << "Add project? (y/n) ";
    cin >> input;
    if (input == 'y'){
      cout << "-> ";
      cin >> project;
      this->projectsOnApp.push_back(project);
    }
    else
      break;
  }
  return in;
}
istream& operator>>(istream& in, StandardUser& user) {
  return user.citire(in);
}
//afisare
ostream& StandardUser::afisare(ostream& out) const {
  cout << "(" << this->getUserType() << ") " << this->username << " | " << this->daysLeft << " days left\n";
  cout << "Projects: " << this->projectsOnApp.size() << endl;
  return out;
}
ostream& operator<<(ostream& out, const StandardUser& user) {
  return user.afisare(out);
}
//getters
string StandardUser::getUsername() {
  return this->username;
}
string StandardUser::getProject(unsigned index) {
  try {
    if (index > this->projectsOnApp.size()) throw "Out of range";
    return this->projectsOnApp[index];
  }
  catch (char const* e) {
    return "undefined";  
  }
}
int StandardUser::getProjectsCount() {
  return this->projectsOnApp.size();
}
int StandardUser::getSubscriptionPrice() {
  return this->subscriptionPrice;
}
int StandardUser::getDaysLeft() {
  return this->daysLeft;
}
//setters
void StandardUser::setUsername(string username) {
  this->username = username;
}
void StandardUser::passDay() { 
  try {
    this->daysLeft--;
    if (this->daysLeft < 0) throw "Subscription allready ended\n";
    if (this->daysLeft == 0)
      app->setUserActivity(this, false);
  } 
  catch (const char* e) {
    return;
  }
}
//methods
void StandardUser::resubscribeToApp() {
  if (this->daysLeft <= 0) {
    this->daysLeft = 30;
    this->app->setUserActivity(this, true);
    cout << "Resubscribed.\n";
  } else {
    cout 
      << "Your subscription has not ended! You have " 
      << this->daysLeft << " days left.\n";
  }

}
void StandardUser::createProject(string projectName) {
  this->projectsOnApp.push_back(projectName);
  cout << "Created project " << projectName << endl;
}
void StandardUser::removeProject(string projectName) {
  try {
    bool deleted = false;
    for (int i = 0; i < this->projectsOnApp.size(); i++)
      if (this->projectsOnApp[i] == projectName) {
        this->projectsOnApp.erase(this->projectsOnApp.begin() + i);
        deleted = true;
      }
    if (!deleted) throw "Project Not Found\n";
    cout << "Removed project " << projectName << endl;
  }
  catch (const char* e) {
    cout << e;
  }

}
bool StandardUser::checkPassword(string password) {
  return this->password == password;
}
void StandardUser::listProjects() {
  try {
    if (this->projectsOnApp.size() == 0) throw "No projects\n";
    cout << "Projects:\n";
    for (int i = 0; i < this->projectsOnApp.size(); i++)
      cout << "  -> " << this->projectsOnApp[i] << endl;
  }
  catch(const char* e) {
    cout << e;
  }
}
string StandardUser::getUserType() const {
  return "Standard";
}


// CLASS PREMIUM USER
//constructors
PremiumUser::PremiumUser() {
  this->subscriptionPrice = 30;
}
PremiumUser::PremiumUser(string username, string password):StandardUser(username, password) {
  this->subscriptionPrice = 30;
};
PremiumUser::PremiumUser(const PremiumUser& user):StandardUser(user) {
  this->contacts = user.contacts;
}
PremiumUser& PremiumUser::operator=(const PremiumUser& user) {
  StandardUser::operator=(user);
  if (this != &user)
    this->contacts = user.contacts;
  return *this;
}
//citire
istream& PremiumUser::citire(istream& in) {
  StandardUser::citire(in);

  char input;
  string contact;
  while(true) {
    cout << "Add contact? (y/n) ";
    cin >> input;
    if (input == 'y') {
      cin >> contact;
      this->contacts.push_back(contact);
    }
    else
      break;
  }
  return in;
}
istream& operator>>(istream& in, PremiumUser& user) {
  return user.citire(in);
}
//afisare
ostream& PremiumUser::afisare(ostream& out) const {
  StandardUser::afisare(out);
  cout << "Contacts: " << this->contacts.size() << endl;
  return out;
}
ostream& operator<<(ostream& out, const PremiumUser& user) {
  return user.afisare(out);
}
//getters
list<string> PremiumUser::getContacts() {
  return this->contacts;
}
//methods
void PremiumUser::addContact(string contact) {
  this->contacts.push_back(contact);
  cout << "Addded contact " << contact << endl;
}
void PremiumUser::removeContact(string contact) {
  for (auto it = this->contacts.begin(); it != this->contacts.end(); it++) {
    if (*it == contact) {
      this->contacts.erase(it);
      break;
    }
  }
  cout << "Removed contact " << contact << endl; 
}
void PremiumUser::listContacts() {
  cout << "Contacts:\n";
  for (auto it = this->contacts.begin(); it != this->contacts.end(); it++)
    cout << "  -> " << *it << endl;
}
string PremiumUser::getUserType() const {
  return "Premium";
}


// CLASS ULTIMATE USER
//constructors
UltimateUser::UltimateUser() {
  this->subscriptionPrice = 50;
}
UltimateUser::UltimateUser(string username, string password):PremiumUser(username, password) {
  this->subscriptionPrice = 50;
}
UltimateUser::UltimateUser(const UltimateUser& user):PremiumUser(user) {
  this->plugins = user.plugins;
}
UltimateUser& UltimateUser::operator=(const UltimateUser& user) {
  PremiumUser::operator=(user);
  if (this != &user)
    this->plugins = user.plugins;
  return *this;
}
//citire
istream& UltimateUser::citire(istream& in) {
  PremiumUser::citire(in);

  char input;
  string plugin;
  while(true) {
    cout << "Add plugin? (y/n) ";
    cin >> input;
    if (input == 'y') {
      cin >> plugin;
      this->plugins.insert(plugin);
    }
    else
      break;
  }
  return in;
}
istream& operator>>(istream& in, UltimateUser& user) {
  return user.citire(in);
}
//afisare
ostream& UltimateUser::afisare(ostream& out) const {
  PremiumUser::afisare(out);
  cout << "Plugins: " << this->plugins.size() << endl;
  return out;
}
ostream& operator<<(ostream& out, const UltimateUser& user) {
  return user.afisare(out);
}
//getters
set<string> UltimateUser::getPlugins() {
  return this->plugins;
}
//methods
void UltimateUser::addPlugin(string plugin) {
  this->plugins.insert(plugin);
  cout << "Added plugin " << plugin << endl;
}
void UltimateUser::removePlugin(string plugin) {
  this->plugins.erase(plugin);
  cout << "Removed plugin " << plugin << endl;
}
void UltimateUser::listPlugins() {
  cout << "Plugins:\n";
  for (auto it = this->plugins.begin(); it != this->plugins.end(); it++)
    cout << "  -> " << *it << endl;
}
string UltimateUser::getUserType() const {
  return "Ultimate";
}


class AppMenu {
private:
  App* app;
  string str_input;
  int int_input;
  StandardUser* currentUser;

  template<typename T>
  void getUserInput(int options=0) {
    if (sizeof(T) == 24) //daca e string
      getline(cin>>ws, str_input);
    else {
      cin >> int_input;
      while (int_input < 0 || int_input > options) {
        cout << "Pick a number between 0 and " << options << "\n-> ";
        cin >> int_input; 
      }
    }
    system("CLS");
  }
  void showMainOptions() {
    cout 
      << "(1) Login\n"
      << "(2) Register\n"
      << "(3) End day\n"
      << "(0) Exit\n"
      << "-> ";  
    getUserInput<int>(3);
  }
  void showUserOptions() {
    cout
      << "(1)  Profile\n"
      << "==============================\n"
      << "(2)  Add Project\n"
      << "(3)  List Projects\n"
      << "(4)  Remove Project\n"
      << "==============================\n"
      << "(5)  Add Contact\n"
      << "(6)  Remove Contact\n"
      << "(7)  List Contacts\n"
      << "==============================\n"
      << "(8)  Add Plugin\n"
      << "(9)  List Plugins\n"
      << "(10) Remove Plugin\n"
      << "==============================\n"
      << "(11) Resubscribe\n"
      << "(0)  Log Out\n"
      << "-> ";
      getUserInput<int>(11);
  }
  bool loginUser() {
    cout << "Username: ";
    getUserInput<string>();
    string username = str_input;
    cout << "Password: ";
    getUserInput<string>();
    string password = str_input;

    currentUser = app->login(username, password); 
    return currentUser;
  }
  bool registerUser() {
    cout << "Username: ";
    getUserInput<string>();
    string username = str_input;
    cout << "Password: ";
    getUserInput<string>();
    string password = str_input;
    cout << "License: (Standard/Premium/Ultimate) ";
    getUserInput<string>();

    while (str_input != "Standard" && str_input != "Premium" && str_input !="Ultimate") {
      cout << "Not a valid license! Enter again: (Standard/Premium/Ultimate) ";
      getUserInput<string>();
    }

    if (str_input == "Standard")
      currentUser = new StandardUser(username, password);
    else if (str_input == "Premium")
      currentUser = new PremiumUser(username, password);
    else
      currentUser = new UltimateUser(username, password);
    
    return true;
  }
public:
  AppMenu() {
    app = app->getInstance();
  }
  void start() {
    while (true) {
      showMainOptions();
      bool loggedIn = false;
      if (int_input == 1)
        loggedIn = loginUser();
      else if (int_input == 2)
        loggedIn = registerUser();
      else if (int_input == 3) {
        app->nextDay();
        cout << "Day ended\n";
      }
      else {
        break;
      }

      if (loggedIn) {
        while (true) {
          showUserOptions();
          if (int_input == 1) {
            // PROFILE
            cout << *currentUser;
          }
          else if (int_input == 2) {
            // ADD PROJECT
            cout << "Project Name: ";
            getUserInput<string>();
            currentUser->createProject(str_input);
          }
          else if (int_input == 3) {
            // LIST PROJECTS
            currentUser->listProjects();
          } 
          else if (int_input == 4) {
            // REMOVE PROJECT
            cout << "Project Name: ";
            getUserInput<string>();
            currentUser->removeProject(str_input);
          }
          else if (int_input == 5) {
            // ADD CONTACT
            if (currentUser->getUserType() != "Standard") {
              PremiumUser* user = dynamic_cast<PremiumUser*>(currentUser);
              cout << "Contact Name: ";
              getUserInput<string>();
              user->addContact(str_input);
            }
            else
              cout << "You need to buy a premium or ultimate license for this!\n";
          }
          else if (int_input == 6) {
            // LIST CONTACTS
            if (currentUser->getUserType() != "Standard") {
              PremiumUser* user = dynamic_cast<PremiumUser*>(currentUser);
              user->listContacts();
            }
            else
              cout << "You need to buy a premium or ultimate license for this!\n";
          }
          else if (int_input == 7) {
            // REMOVE CONTACT
            if (currentUser->getUserType() != "Standard") {
              PremiumUser* user = dynamic_cast<PremiumUser*>(currentUser);
              cout << "Contact Name: ";
              getUserInput<string>();
              user->removeContact(str_input);
            }
            else
              cout << "You need to buy a premium or ultimate license for this!\n";
          }
          else if (int_input == 8) {
            // ADD PLUGIN
            if (currentUser->getUserType() == "Ultimate") {
              UltimateUser* user = dynamic_cast<UltimateUser*>(currentUser);
              cout << "Plugin Name: ";
              getUserInput<string>();
              user->addPlugin(str_input);
            }
            else
              cout << "You need to buy an ultimate license for this!\n";
          }
          else if (int_input == 9) {
            // LIST PLUGINS
            if (currentUser->getUserType() == "Ultimate") {
              UltimateUser* user = dynamic_cast<UltimateUser*>(currentUser);
              user->listPlugins();
            }
            else
              cout << "You need to buy an ultimate license for this!\n";
          }
          else if (int_input == 10) {
            // REMOVE PLUGIN
            if (currentUser->getUserType() == "Ultimate") {
              UltimateUser* user = dynamic_cast<UltimateUser*>(currentUser);
              cout << "Plugin Name: ";
              getUserInput<string>();
              user->removePlugin(str_input);
            }
            else
              cout << "You need to buy an ultimate license for this!\n";
          }
          else if (int_input == 11) {
            // RESUBSCRIBE
            currentUser->resubscribeToApp();
          }
          else {
            break;
          }  
        }
      }
    }
  }
};

int main() {
  AppMenu app;
  StandardUser user("IOn", "vas");
  user.getProject(10);
  app.start();
}
