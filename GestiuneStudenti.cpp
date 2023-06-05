#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

class Student;
class Facultate;
class Camin;
class Universitate;
class SolicitareCazare;


class SolicitareCazare {
  Student* student;
  vector<Camin*> caminePrioritare;
public:
  //constructors
  SolicitareCazare(Student* student, vector<Camin*> caminePrioritare);
  SolicitareCazare(Student* student);
  SolicitareCazare(const SolicitareCazare& solicitareCazare);
  SolicitareCazare();
  //setters
  void setStudent(Student* student) { this->student = student; }
  void setCaminPrioritar(Camin* caminPrioritar,int index) { this->caminePrioritare[index] = caminPrioritar; }
  //getters
  Student* getStudent() { return this->student; }
  int getNrCaminePrioritare() { return this->caminePrioritare.size(); }
  Camin* getCamin(int index);
  //supraincarcarea operatorilor
  SolicitareCazare& operator=(const SolicitareCazare& solicitareCazare);
  friend istream& operator>>(istream& in, SolicitareCazare& solicitareCazare);
  friend ostream& operator<<(ostream& out, const SolicitareCazare& solicitareCazare);
  Camin* operator[](int index);
  SolicitareCazare& operator--();
  SolicitareCazare operator--(int);
  friend SolicitareCazare operator+(SolicitareCazare solicitareCazare, Camin* camin);
  friend SolicitareCazare operator+(Camin* camin, SolicitareCazare solicitareCazare);
  friend SolicitareCazare operator-(SolicitareCazare solicitareCazare, Camin* camin);
  friend SolicitareCazare operator-(Camin* camin, SolicitareCazare solicitareCazare);
  explicit operator string();
  bool operator>(SolicitareCazare solicitareCazare);
  bool operator==(SolicitareCazare solicitareCazare);
  //methods
  int getIndexCamin(Camin* element);
  void repartizareStudent(int indexCamin);
};
//constructors
SolicitareCazare::SolicitareCazare() {
  this->student = NULL;
}
SolicitareCazare::SolicitareCazare(Student* student) {
  this->student = student;
}
SolicitareCazare::SolicitareCazare(Student* student, vector<Camin*> caminePrioritare) {
  this->student = student;
  this->caminePrioritare = caminePrioritare;
}
SolicitareCazare::SolicitareCazare(const SolicitareCazare& solicitareCazare){
  this->student = solicitareCazare.student;
  this->caminePrioritare.clear();
  for (int i = 0; i < solicitareCazare.caminePrioritare.size(); i++) {
    this->caminePrioritare.push_back(solicitareCazare.caminePrioritare[i]);
  }
}

class Facultate {
  string nume;
  int nrStudenti;
  vector<SolicitareCazare*> solicitariCazare;
  const int id;
  static int contorId;
public:
  //constructors
  Facultate(string nume, int nrStudenti, vector<SolicitareCazare*> solicitariCazare);
  Facultate(string nume, int nrStudenti);
  Facultate(const Facultate& facultate);
  Facultate();
  //setters
  void setNume(string nume) { this->nume = nume; }
  void setNrStudenti(int nrStudenti) { this->nrStudenti = nrStudenti; }
  void setSolicitariCazare(vector<SolicitareCazare*> solicitariCazare) { this->solicitariCazare = solicitariCazare; }
  //getters
  string getNume() { return this->nume; }
  int getNrStudenti() { return this->nrStudenti; }
  int getNrSolicitariCazare() { return this->solicitariCazare.size(); }
  SolicitareCazare* getSolicitareCazare(int index) { return this->solicitariCazare[index]; }
  int getId() { return this->id; }
  int getContorId() { return this->contorId; }
  //supraincarcarea operatorilor
  Facultate& operator=(const Facultate& facultate);
  friend istream& operator>>(istream& in, Facultate& facultate);
  friend ostream& operator<<(ostream& out, const Facultate& facultate);
  SolicitareCazare* operator[](int index);
  Facultate& operator++();
  Facultate operator++(int);
  friend Facultate operator+(Facultate facultate, int nrStudenti);
  friend Facultate operator+(int nrStudenti, Facultate facultate);
  friend Facultate operator-(Facultate facultate, int nrStudenti);
  friend Facultate operator-(int nrStudenti, Facultate facultate);
  explicit operator int();
  bool operator<(const Facultate& facultate);
  bool operator==(const Facultate& facultate);
  //methods
  void inregistrareSolicitareCazare(SolicitareCazare* solicitareCazare);
  void ordoneazaSolicitarileDupaPunctaj();
};
int Facultate::contorId = 0;
//constructors
Facultate::Facultate(string nume, int nrStudenti, vector<SolicitareCazare*> solicitariCazare):id(contorId++) {
  this->nume = nume;
  this->nrStudenti = nrStudenti;
  this->solicitariCazare = solicitariCazare; 
}
Facultate::Facultate(string nume, int nrStudenti):id(contorId++) {
  this->nume = nume;
  this->nrStudenti = nrStudenti;
}
Facultate::Facultate():id(contorId++) {
  this->nume = "";
  this->nrStudenti = 0;
}
Facultate::Facultate(const Facultate& facultate):id(contorId++) {
  this->nume = facultate.nume;
  this->nrStudenti = facultate.nrStudenti;
  this->solicitariCazare = facultate.solicitariCazare; 
}
//supraincarcarea operatorilor
Facultate& Facultate::operator=(const Facultate& facultate) {
  if (this != &facultate) {
    this->nume = facultate.nume;
    this->nrStudenti = facultate.nrStudenti;
    this->solicitariCazare = facultate.solicitariCazare;
  }
  return *this;
}
istream& operator>>(istream& in, Facultate& facultate) {
  cout << "Nume: ";
  getline(in >> ws, facultate.nume);
  cout << "Numar Studenti: ";
  in >> facultate.nrStudenti;
  return in;
}
ostream& operator<<(ostream& out, const Facultate& facultate) {
  out << facultate.nume;
  return out;
}
SolicitareCazare* Facultate::operator[](int index) {
  return this->solicitariCazare[index];
}
Facultate& Facultate::operator++() {
  this->nrStudenti++;
  return *this;
}
Facultate Facultate::operator++(int) {
  Facultate aux = *this;
  this->nrStudenti++;
  return aux;
}
Facultate operator+(Facultate facultate, int nrStudenti) {
  facultate.nrStudenti += nrStudenti;
  return facultate;
}
Facultate operator+(int nrStudenti, Facultate facultate) { 
  facultate.nrStudenti++;
  return facultate;
}
Facultate operator-(Facultate facultate, int nrStudenti) {
  facultate.nrStudenti -= nrStudenti;
  return facultate;
}
Facultate operator-(int nrStudenti, Facultate facultate) {
  facultate.nrStudenti -= nrStudenti;
  return facultate;
}
Facultate::operator int() {
  return this->nrStudenti;
}
bool Facultate::operator<(const Facultate& facultate) {
  return this->nrStudenti < facultate.nrStudenti;
}
bool Facultate::operator==(const Facultate& facultate) {
  if (this->nume != facultate.nume) return false;
  if (this->nrStudenti != facultate.nrStudenti) return false;
  if (this->solicitariCazare.size() != facultate.solicitariCazare.size()) return false;
  for (int i = 0; i < this->solicitariCazare.size(); i++) {
    if (!(this->solicitariCazare[i] == facultate.solicitariCazare[i])) return false;
  }
  return true;
}
//methods
void Facultate::inregistrareSolicitareCazare(SolicitareCazare* solicitareCazare) {
  this->solicitariCazare.push_back(solicitareCazare);
}
void Facultate::ordoneazaSolicitarileDupaPunctaj() {
  for (int i = 0; i < this->solicitariCazare.size() - 1; i++)
    for (int j = i; j < this->solicitariCazare.size(); j++) 
      if (*solicitariCazare[j] > *solicitariCazare[i]) {
        swap(solicitariCazare[i], solicitariCazare[j]);
      }
}

class Camin {
  string nume;
  int nrLocuri;
  int nrLocuriLibere;
  int nrFacultati;
public:
  //constructors
  Camin(string nume, int nrLocuri, int nrLocuriLibere, int nrFacultati);
  Camin(string nume);
  Camin(const Camin& camin);
  Camin();
  //setters
  void setNume(string nume) { this->nume = nume; }
  void setNrLocuri(int nrLocuri) { this->nrLocuri = nrLocuri; }
  void setNrLocuriLibere(int nrLocuriLibere) { this->nrLocuriLibere = nrLocuriLibere; }
  void setNrFacultati(int nrFacultati) { this->nrFacultati = nrFacultati; }
  //getters
  string getNume() { return this->nume; }
  int getNrLocuri() { return this->nrLocuri; }
  int getNrLocuriLibere() { return this->nrLocuriLibere; }
  int getNrFacultati() { return this->nrFacultati; }
  //supraincarcarea operatorilor
  Camin& operator=(const Camin& camin);
  friend istream& operator>>(istream& in, Camin& camin);
  friend ostream& operator<<(ostream& out, const Camin& camin);
  Camin& operator--();
  Camin operator--(int);
  friend Camin operator+(Camin camin, int nrLocuriEliberate);
  friend Camin operator+(int nrLocuriEliberate, Camin camin);
  friend Camin operator-(Camin camin, int nrLocuriEliberate);
  friend Camin operator-(int nrLocuriEliberate, Camin camin);
  explicit operator int();
  bool operator<(const Camin& camin);
  bool operator==(const Camin& camin);
  bool operator!=(const Camin& camin);
  //methods
  void elibereazaLoc();
  void ocupaLoc() {
    this->nrLocuriLibere--;
  }
};
//constructors
Camin::Camin() {
  this->nume = "";
  this->nrLocuri = 0;
  this->nrLocuriLibere = 0;  
  this->nrFacultati = 0;
}
Camin::Camin(string nume) {
  this->nume = nume;
  this->nrLocuri = 0;
  this->nrLocuriLibere = 0;  
  this->nrFacultati = 0;
}
Camin::Camin(string nume, int nrLocuri, int nrLocuriLibere, int nrFacultati) {
  this->nume = nume;
  this->nrLocuri = nrLocuri;
  this->nrLocuriLibere = nrLocuriLibere;
  this->nrFacultati = nrFacultati;
}
Camin::Camin(const Camin& camin) {
  this->nume = camin.nume;
  this->nrLocuri = camin.nrLocuri;
  this->nrLocuriLibere = camin.nrLocuriLibere;
  this->nrFacultati = camin.nrFacultati;
}
//supraincarcarea operatorilor
Camin& Camin::operator=(const Camin& camin) {
  if (this != &camin) {
  this->nume = camin.nume;
  this->nrLocuri = camin.nrLocuri;
  this->nrLocuriLibere = camin.nrLocuriLibere;
  this->nrFacultati = camin.nrFacultati;
  }
  return *this;
}
istream& operator>>(istream& in, Camin& camin) {
  cout << "Nume: ";
  getline(in >> ws, camin.nume);
  cout << "Numar locuri: ";
  in >> camin.nrLocuri;
  cout << "Numar locuri libere: ";
  in >> camin.nrLocuriLibere;
  cout << "Numar facultati in camin: ";
  in >> camin.nrFacultati;
  return in;
}
ostream& operator<<(ostream& out, const Camin& camin) {
  cout << camin.nume << " - " << camin.nrLocuriLibere << " locuri libere";
  return out;
}
Camin& Camin::operator--() {
  this->nrLocuriLibere--;
  return *this;
}
Camin Camin::operator--(int) {
  Camin aux = *this;
  this->nrLocuriLibere--;
  return aux;
}
Camin operator+(Camin camin, int nrLocuriEliberate) {
  camin.nrLocuriLibere += nrLocuriEliberate;
  return camin;
}
Camin operator+(int nrLocuriEliberate, Camin camin) {
  camin.nrLocuriLibere += nrLocuriEliberate;
  return camin;
}
Camin operator-(Camin camin, int nrLocuriOcupate) {
  camin.nrLocuriLibere -= nrLocuriOcupate;
  return camin;
}
Camin operator-(int nrLocuriOcupate, Camin camin) {
  camin.nrLocuriLibere -= nrLocuriOcupate;
  return camin;
}
Camin::operator int() {
  return this->nrLocuri;
}
bool Camin::operator<(const Camin& camin) {
  return this->nrLocuri < camin.nrLocuri;
}
bool Camin::operator==(const Camin& camin) {
  if (this->nume != camin.nume) return false;
  if (this->nrLocuri != camin.nrLocuri) return false;
  if (this->nrLocuriLibere != camin.nrLocuriLibere) return false;
  if (this->nrFacultati != camin.nrFacultati) return false;
  return true;
}
bool Camin::operator!=(const Camin& camin) {
  if (this->nume != camin.nume || this->nrLocuri != camin.nrLocuri || this->nrLocuriLibere != camin.nrLocuriLibere || this->nrFacultati != camin.nrFacultati)
    return true;
  return false;
}
//methods
void Camin::elibereazaLoc() {
  this->nrLocuriLibere++;
}

class Student {
  string nume;
  string prenume;
  Facultate* facultate;
  Camin* camin;
  float punctajClasificareCamin;
public:
  //constructors
  Student(string nume, string prenume, Facultate* facultate, float _punctajClasificareCamin, Camin* camin);
  Student(string nume, string prenume, Facultate* facultate, float _punctajClasificareCamin);
  Student(const Student& student);
  Student();
  //setters
  void setNume(string nume) { this->nume = nume; }
  void setPrenume(string prenume) { this->prenume = prenume; }
  void setFacultate(Facultate* facultate) { this->facultate = facultate; }
  void setCamin(Camin* camin) { this->camin = camin; }
  //getters
  string getNume() { return this->nume; }
  string getPrenume() { return this->prenume; }
  Facultate* getFacultate() { return this->facultate; }
  Camin* getCamin() { return this->camin; }
  float getPunctajClasificareCamin() { return this->punctajClasificareCamin; }
  //supraincarcarea operatorilor
  Student& operator=(const Student& student);
  friend istream& operator>>(istream& in, Student& student);
  friend ostream& operator<<(ostream& out, const Student& student);
  Student& operator--();
  Student operator--(int);
  friend Student operator+(Student student, float punctaj);
  friend Student operator+(float punctaj, Student student);
  friend Student operator-(Student student, float punctaj);
  friend Student operator-(float punctaj, Student student);
  explicit operator int();
  bool operator<(const Student& student);
  bool operator==(const Student& student);
  //methods
  void solicitaCazare(vector<Camin*> camine);
  void solicitaDecazare();
};
//constructors
Student::Student(string nume, string prenume, Facultate* facultate, float _punctajClasificareCamin, Camin* camin):punctajClasificareCamin(_punctajClasificareCamin) {
  this->nume = nume;
  this->prenume = prenume;
  this->facultate = facultate;
  this->camin = camin;
}
Student::Student(string nume, string prenume, Facultate* facultate, float _punctajClasificareCamin):punctajClasificareCamin(_punctajClasificareCamin) {
  this->nume = nume;
  this->prenume = prenume;
  this->facultate = facultate;
}
Student::Student():punctajClasificareCamin(0) {
  this->nume = "";
  this->prenume = "";  
  this->facultate = NULL;
  this->camin = NULL;
}
Student::Student(const Student& student):punctajClasificareCamin(student.punctajClasificareCamin) {
  this->nume = student.nume;
  this->prenume = student.prenume;
  this->facultate = student.facultate;
  this->camin = student.camin;
}
//supraincarcarea operatorilor
Student& Student::operator=(const Student& student) {
  if (this != &student) {
    this->nume = student.nume;
    this->prenume = student.prenume;
    this->camin = student.camin;
    this->facultate = student.facultate;
    this->punctajClasificareCamin = student.punctajClasificareCamin;
  }
  return *this;
}
istream& operator>>(istream& in, Student& student) {
  cout << "Nume: ";
  getline(in >> ws, student.nume);
  cout << "Prenume: ";
  getline(in >> ws, student.prenume);
  cout << "Punctaj: ";
  in >> student.punctajClasificareCamin;
  while (student.punctajClasificareCamin > 100) {
    cout << "Punctajul maxim este 100! Introduceti din nou punctajul: ";
    cin >> student.punctajClasificareCamin;
  }
  return in;
}
ostream& operator<<(ostream& out, const Student& student) {
  cout << student.nume << ' ' << student.prenume;
  return out;
}
Student& Student::operator--() {
  if (this->camin)
    this->camin = NULL;
  return *this;
}
Student Student::operator--(int) {
  Student aux = *this;
  if (this->camin)
    this->camin = NULL;
  return aux;
}
Student operator+(Student student, float punctaj) {
  student.punctajClasificareCamin += punctaj;
  return student;
}
Student operator+(float punctaj, Student student) {
  student.punctajClasificareCamin += punctaj;
  return student;
}
Student operator-(Student student, float punctaj) {
  student.punctajClasificareCamin -= punctaj;
  return student;
}
Student operator-(float punctaj, Student student) {
  student.punctajClasificareCamin -= punctaj;
  return student;
}
Student::operator int() {
  return this->punctajClasificareCamin;
}
bool Student::operator<(const Student& student) {
  return this->punctajClasificareCamin < student.punctajClasificareCamin;
}
bool Student::operator==(const Student& student) {
  if (this->nume != student.nume) return false;
  if (this->prenume != student.prenume) return false;
  if (this->facultate != student.facultate) return false;
  if (this->camin != student.camin) return false;
  if (this->punctajClasificareCamin != student.punctajClasificareCamin) return false;
  return true;
}
//methods
void Student::solicitaCazare(vector<Camin*> camine) {
  SolicitareCazare* solicitareCazare = new SolicitareCazare(this, camine);
  this->facultate->inregistrareSolicitareCazare(solicitareCazare);
}
void Student::solicitaDecazare() {
  if (!this->camin) return;
    this->camin->elibereazaLoc();
  this->camin = NULL;
}

//===============================================================================================
//OPERATORI SOLICITARE CAZARE
bool SolicitareCazare::operator>(SolicitareCazare solicitareCazare) {
  return this->student->getPunctajClasificareCamin() > solicitareCazare.student->getPunctajClasificareCamin();
}
bool SolicitareCazare::operator==(SolicitareCazare solicitareCazare) {
  return this->student->getPunctajClasificareCamin() == solicitareCazare.student->getPunctajClasificareCamin();
}
SolicitareCazare& SolicitareCazare::operator=(const SolicitareCazare& solicitareCazare) {
  if (this != &solicitareCazare) {
    this->student = solicitareCazare.student;
    this->caminePrioritare = solicitareCazare.caminePrioritare;
  }
  return *this;
}

SolicitareCazare operator+(SolicitareCazare solicitareCazare, Camin* camin) {
  solicitareCazare.caminePrioritare.push_back(camin);
  return solicitareCazare;
}
SolicitareCazare operator+(Camin* camin, SolicitareCazare solicitareCazare) {
  solicitareCazare.caminePrioritare.push_back(camin);
  return solicitareCazare;
}
ostream& operator<<(ostream& out, const SolicitareCazare& solicitareCazare) {
  out << "Student: " << solicitareCazare.student << '\n';
  out << "Camine:\n";
  for (int i = 0; i < solicitareCazare.caminePrioritare.size(); i++ ) {
    out << solicitareCazare.caminePrioritare[i]->getNume() << '\n';
  }
  return out;
}
istream& operator>>(istream& in, SolicitareCazare& solicitareCazare) {
  // cout << "Student: ";
  // in >> solicitareCazare.student;
  // cout << "Nr camine: ";
  // in >> solicitareCazare.nrCaminePrioritare;
  // cout << "Camine:\n";
  // for (int i = 0; i < solicitareCazare.nrCaminePrioritare; i++) {
  //   in >> solicitareCazare.caminePrioritare[i];
  // }
  return in;
}
SolicitareCazare operator-(SolicitareCazare solicitareCazare, Camin* camin) {
  int index = solicitareCazare.getIndexCamin(camin);
  if (index >= 0 )
    solicitareCazare.caminePrioritare.erase(solicitareCazare.caminePrioritare.begin() + index);
  else
    cout << "camin invalid";
  return solicitareCazare;
}
SolicitareCazare operator-(Camin* camin, SolicitareCazare solicitareCazare) {
   int index = solicitareCazare.getIndexCamin(camin);
  if (index >= 0 )
    solicitareCazare.caminePrioritare.erase(solicitareCazare.caminePrioritare.begin() + index);
  else
    cout << "camin invalid";
  return solicitareCazare;
}
SolicitareCazare& SolicitareCazare::operator--() {  
  if (this->caminePrioritare.size() > 0) {
    this->caminePrioritare.erase(this->caminePrioritare.end());
  }
  return *this;
}
SolicitareCazare SolicitareCazare::operator--(int) {
  SolicitareCazare aux(*this);
  if (this->caminePrioritare.size() > 0) {
    this->caminePrioritare.erase(this->caminePrioritare.end());
  }
  return aux;
}
Camin* SolicitareCazare::operator[](int index) {
  return this->caminePrioritare[index];
}
SolicitareCazare::operator string() {
  return "Solicitarea studentului " + this->student->getNume();
}
//METODE SOLICITARE CAZARE
Camin* SolicitareCazare::getCamin(int index) { return this->caminePrioritare[index]; }
int SolicitareCazare::getIndexCamin(Camin* element) {
  for (int i = 0; i < this->caminePrioritare.size(); i++)
    if (this->caminePrioritare[i] == element)
      return i;
  return -1;
}

void SolicitareCazare::repartizareStudent(int indexCamin) {
  this->caminePrioritare[indexCamin]->ocupaLoc();
  this->student->setCamin(this->caminePrioritare[indexCamin]);
}

//===============================================================================================

class Universitate {
  string nume;
  int nrStudenti;
  int nrFacultati;
  int nrCamine;
  int* nrLocuriCaminPerFacultate;
  Camin* camine;
  Facultate* facultati;

public:
  //constructors
  Universitate(string nume, int nrStudenti, int nrFacultati, int nrCamine, Camin* camine, Facultate* facultati, int* nrLocuriCaminPerFacultate);
  Universitate(string nume, int nrStudenti, int nrFacultati, int nrCamine, Camin* camine, Facultate* facultati);
  Universitate(const Universitate& universitate);
  Universitate();
  //setters
  void setNume(string nume) {this->nume = nume; }
  void setNrStudenti(int nrStudenti) { this->nrStudenti = nrStudenti; }
  void setNrFacultati(int nrFacultati) { this->nrFacultati = nrFacultati; }
  void setNrCamine(int nrCamine) { this->nrCamine = nrCamine; }
  void setNrLocuriCaminPerFacultate(int* nrLocuriCaminPerFacultate) { this->nrLocuriCaminPerFacultate = nrLocuriCaminPerFacultate; }
  void setCamin(Camin camin, int index) {this->camine[index] = camin; }
  void setFacultate(Facultate facultate, int index) {this->facultati[index] = facultate; }
  //getters
  string getNume() { return this->nume; }
  int getNrStudenti() { return this->nrStudenti; }
  int getNrFacultati() { return this->nrFacultati; }
  int getNrCamine() { return this->nrCamine; }
  int getNrLocuriCaminPerFacultate(int index) {return this->nrLocuriCaminPerFacultate[index]; }
  Camin& getCamin(int index) { return this->camine[index]; }
  Facultate& getFacultate(int index) { return this->facultati[index]; }
  //supraincarcarea operatorilor
  Universitate& operator=(const Universitate& universitate);
  friend istream& operator>>(istream& in, Universitate& universitate);
  friend ostream& operator<<(ostream& out, const Universitate& universitate);
  Universitate& operator++();
  Universitate operator++(int);
  friend Universitate operator+(Universitate universitate, int nrStudenti);
  friend Universitate operator+(int nrStudenti, Universitate universitate);
  friend Universitate operator-(Universitate universitate, int nrStudenti);
  friend Universitate operator-(int nrStudenti, Universitate universitate);
  explicit operator int();
  bool operator<(const Universitate& universitate);
  bool operator==(const Universitate& universitate);
  //methods
  int getTotalSolicitariCazare();
  int getTotalLocuriCamine();
  void calculeazaNrLocuriCaminPerFacultate();
  void repartizeazaStudentiiLaCamine();
};
//constructors
Universitate::Universitate() {
  this->nume = "";
  this->nrStudenti = 0;
  this->nrFacultati = 0;
  this->nrCamine = 0;
  this->camine = NULL;
  this->facultati = NULL;
  this->nrLocuriCaminPerFacultate = NULL;
}
Universitate::Universitate(string nume, int nrStudenti, int nrFacultati, int nrCamine, Camin* camine, Facultate* facultati) {
  this->nume = nume;
  this->nrStudenti = nrStudenti;
  this->nrFacultati = nrFacultati;
  this->nrCamine = nrCamine;
  this->facultati = facultati;    
  this->camine = camine;
}
Universitate::Universitate(string nume, int nrStudenti, int nrFacultati, int nrCamine, Camin* camine, Facultate* facultati, int* nrLocuriCaminPerFacultate) {
  this->nume = nume;
  this->nrStudenti = nrStudenti;
  this->nrFacultati = nrFacultati;
  this->nrCamine = nrCamine;
  this->facultati = facultati;    
  this->camine = camine;
  this->nrLocuriCaminPerFacultate = nrLocuriCaminPerFacultate;
}
Universitate::Universitate(const Universitate& universitate) {
  this->nume = universitate.nume;
  this->nrStudenti = universitate.nrStudenti;
  this->nrFacultati = universitate.nrFacultati;
  this->nrCamine = universitate.nrCamine;
  this->facultati = universitate.facultati;    
  this->camine = universitate.camine;
  this->nrLocuriCaminPerFacultate = universitate.nrLocuriCaminPerFacultate;
}
//supraincarcarea operatorilor
Universitate& Universitate::operator=(const Universitate& universitate) {
  if (this != &universitate) {
    this->nume = universitate.nume;
    this->nrStudenti = universitate.nrStudenti;
    this->nrFacultati = universitate.nrFacultati;
    this->nrCamine = universitate.nrCamine;
    //realocare nrLocuriCaminPerFacultate
    if (this->nrLocuriCaminPerFacultate) {
      delete[] this->nrLocuriCaminPerFacultate;
    }
    this->nrLocuriCaminPerFacultate = new int[this->nrFacultati];
    for (int i = 0; i < this->nrFacultati; i++) {
      this->nrLocuriCaminPerFacultate[i] = universitate.nrLocuriCaminPerFacultate[i];
    }
    //realocare camine
    if (this->camine) {
      delete[] this->camine;
    }
    this->camine = new Camin[this->nrCamine];
    for (int i = 0; i < this->nrCamine; i++) {
      this->camine[i] = universitate.camine[i];
    }
    //realocare facultati
    if (this->facultati) {
      delete[] this->facultati;
    }
    this->facultati = new Facultate[this->nrFacultati];
    for (int i = 0; i < this->nrFacultati; i++) {
      this->facultati[i] = universitate.facultati[i];
    }
  }
  return *this;
}
istream& operator>>(istream& in, Universitate& universitate) {
  cout << "Nume: ";
  getline(in >> ws, universitate.nume);
  cout << "Numar studenti: ";
  in >> universitate.nrStudenti;
  cout << "Numar facultati: ";
  in >> universitate.nrFacultati;
  cout << "Numar camine: ";
  in >> universitate.nrCamine;
  //Alocam vectorul, il citim dupa in main
  if (universitate.facultati)
    delete[] universitate.facultati;
  universitate.facultati = new Facultate[universitate.nrFacultati];
  if (universitate.camine) {
    delete[] universitate.camine;
  }
  universitate.camine = new Camin[universitate.nrCamine];
  return in;
}
ostream& operator<<(ostream& out, const Universitate& universitate) {
  cout << universitate.nume;
  return out;
}
Universitate& Universitate::operator++() {
  this->nrStudenti++;
  return *this;
}
Universitate Universitate::operator++(int) {
  Universitate aux = *this;
  this->nrStudenti++;
  return aux;
}
Universitate operator+(Universitate universitate, int nrStudenti) {
  universitate.nrStudenti += nrStudenti;
  return universitate;
}
Universitate operator+(int nrStudenti, Universitate universitate) {
  universitate.nrStudenti += nrStudenti;
  return universitate;
}
Universitate operator-(Universitate universitate, int nrStudenti) {
  universitate.nrStudenti -= nrStudenti;
  return universitate;
}
Universitate operator-(int nrStudenti, Universitate universitate) {
  universitate.nrStudenti -= nrStudenti;
  return universitate;
}
Universitate::operator int() {
  return this->nrStudenti;
}
bool Universitate::operator<(const Universitate& universitate) {
  return this->nrStudenti < universitate.nrStudenti;
}
bool Universitate::operator==(const Universitate& universitate) {
  if (this->nume != universitate.nume) return false;
  if (this->nrStudenti != universitate.nrStudenti) return false;
  if (this->nrCamine != universitate.nrCamine) return false;
  if (this->nrFacultati != universitate.nrFacultati) return false;
  for (int i = 0; i < this->nrFacultati; i++) {
    if (this->nrLocuriCaminPerFacultate[i] != universitate.nrLocuriCaminPerFacultate[i]) 
      return false;
    if (!(this->facultati[i] == universitate.facultati[i]))
      return false;
  }
  for (int i = 0; i < this->nrCamine; i++) {
    if (this->camine[i] != universitate.camine[i]) 
      return false;
  }
  return true;
}
//methods

int Universitate::getTotalSolicitariCazare() {
    int totalSolicitariCazare = 0;
    for (int i = 0; i < this->nrFacultati; i++) {
      totalSolicitariCazare += this->facultati[i].getNrSolicitariCazare(); 
    }
    return totalSolicitariCazare;
  }
int Universitate::getTotalLocuriCamine() {
  int totalLocuriCamine = 0;
  for (int i = 0; i < this->nrCamine; i++) {
    totalLocuriCamine += this->camine[i].getNrLocuriLibere();
  }
  return totalLocuriCamine;
}
void Universitate::calculeazaNrLocuriCaminPerFacultate() {
  if (this->nrLocuriCaminPerFacultate != NULL)
    delete[] this->nrLocuriCaminPerFacultate;

  this->nrLocuriCaminPerFacultate = new int[this->nrFacultati];
  int totalLocuriDistribuite = 0;
  int totalNrSolicitari = this->getTotalSolicitariCazare();
  int locuriCamine = this->getTotalLocuriCamine();
  for (int i = 0; i < this->nrFacultati - 1; i++) {
    int nrSolicitariFacultate = this->facultati[i].getNrSolicitariCazare();
    float nrLocuri = ((float)nrSolicitariFacultate / (float)totalNrSolicitari) * (float)locuriCamine;
    this->nrLocuriCaminPerFacultate[i] = (int)nrLocuri;
    totalLocuriDistribuite += (int)nrLocuri;
  }
  this->nrLocuriCaminPerFacultate[facultati[this->nrFacultati-1].getId()] = locuriCamine - totalLocuriDistribuite;
}
void Universitate::repartizeazaStudentiiLaCamine() {
  this->calculeazaNrLocuriCaminPerFacultate();
  for (int i = 0; i < this->nrFacultati; i++) {
    this->facultati[i].ordoneazaSolicitarileDupaPunctaj();
    for (int j = 0; j < this->facultati[i].getNrSolicitariCazare() && j < this->getNrLocuriCaminPerFacultate(i); j++) {
      bool cazat = false;
      SolicitareCazare* solicitareCazare = this->facultati[i].getSolicitareCazare(j);
      for (int k = 0; k < solicitareCazare->getNrCaminePrioritare() && !cazat; k++) {
        if (solicitareCazare->getCamin(k)->getNrLocuriLibere() > 0) {
          solicitareCazare->repartizareStudent(k);
          cazat = true;
        }
      }
    }
  }
}

char yesOrNo() {
  char input;
  cin >> input;
  while (tolower(input) != 'y' && tolower(input) != 'n') {
    cout << "'y' pentru DA si 'n' pentru NU: ";
    cin >> input;
  }
  return input;
}

char alegeOperatiune() {
  cout << "\nAlege operatiunea urmatoare: \n";
  cout << "(1) Adauga inca o universitate \n";
  cout << "(2) Afiseaza Studentii din fiecare facultate si caminele la care sunt repartizati\n";
  cout << "(3) Afiseaza toate facultatile si caminele din fiecare universitate \n";
  cout << "(4) Decazeaza student \n";
  cout << "(5) Redistribuie locurile la camin \n";
  cout << "(6) Incheie sesiunea \n";
  cout << "-> ";
  char input;
  cin >> input;
  return input;
}

int main() {
  vector<Universitate> universitati;
  vector<Student*> studenti;

  while(true) {
    char input;
    cout << "Adauga universitate:\n";
    Universitate universitate;
    cin >> universitate;
    universitati.push_back(universitate);
    system("CLS");
    //citesc facultatile din universitate
    for (int i = 0; i < universitati.back().getNrFacultati(); i++) {
      cout << "Adauga facultatatea nr. " << i + 1 << " pentru " << universitate << ":\n";
      Facultate facultate;
      cin >> facultate;
      universitati.back().setFacultate(facultate, i);
      system("CLS");
    }
    //citesc caminele din facultate
    for (int i = 0; i < universitati.back().getNrCamine(); i++) {
      cout << "Adauga caminul nr. " << i + 1 << " pentru " << universitate << ":\n";
      Camin camin;
      cin >> camin;
      universitati.back().setCamin(camin, i);
      system("CLS");
    }
    //adaug studentii care urmeaza sa solicite camin pt fiecare facultate
    for (int i = 0; i < universitati.back().getNrFacultati(); i++) {
      while (true) {
        cout << "Vrei sa adaugi un student la " << universitati.back().getFacultate(i) << " care va solicita camin? (y/n) ";
        input = yesOrNo();
        if (tolower(input) == 'y') {
          Student* student = new Student();
          cin >> *student;
          studenti.push_back(student);
          student->setFacultate(&universitati.back().getFacultate(i));

          cout << "Alege caminele in ordinea preferintelor de la 1 la " << universitati.back().getNrCamine() << ":\n";
          vector<Camin*> camineAlese;
          camineAlese.resize(universitati.back().getNrCamine());
          int prioritateCamin;
          for (int i = 0; i < universitati.back().getNrCamine(); i++) {
            cout << "(" << i + 1 << ") " << universitati.back().getCamin(i) << ": ";
            cin >> prioritateCamin;
            camineAlese[prioritateCamin - 1]= &universitati.back().getCamin(i);
          }
          student->solicitaCazare(camineAlese);
          system("CLS");
        }
        else
          break;
      }
    }
    cout << "Vrei sa repartizezi studentii din " << universitati.back() << " la camin? (y/n) ";
    input = yesOrNo();
    if (tolower(input) == 'y')
      universitati.back().repartizeazaStudentiiLaCamine();
    system("CLS");
    while (true) {
      input = alegeOperatiune();
      if (input == '1'){
        break;
      }
      else if (input == '2') {
        system("CLS");
        for (unsigned i = 0; i < studenti.size(); i++) {
        cout << *studenti[i] << " - " << *studenti[i]->getFacultate() << ": ";
        if (studenti[i]->getCamin())
          cout << studenti[i]->getCamin()->getNume() << endl;
        else
          cout << "Nerepartizat" << endl;
      }
      }
      else if (input == '3') {
        system("CLS");
        for (int i = 0; i < universitati.size(); i++) {
          cout << universitati[i] << ":\n";
          cout << "-> Facultati:\n";
          for (int j = 0; j < universitati[i].getNrFacultati(); j++) {
            cout << "  -> " << universitati[i].getFacultate(j) << endl;
          }
          cout << "-> Camine:\n";
          for (int j = 0; j < universitati[i].getNrCamine(); j++) {
            cout << "   -> " << universitati[i].getCamin(j) << endl;
          }
        }
      }
      else if (input == '4') {
        system("CLS");
        cout << "Alege studentul: \n";
        for (int i = 0; i < studenti.size(); i++) {
          if (studenti[i]->getCamin())
            cout << "(" << i << ") " << *studenti[i]<<endl;
        }
        cout << "->";
        int indexStudent;
        cin >> indexStudent;
        Camin* caminStudent = studenti[indexStudent]->getCamin();
        studenti[indexStudent]->solicitaDecazare();
        cout << "Studentul " << *studenti[indexStudent] << " a fost decazat\n";
        cout << "Caminul " << caminStudent->getNume() << " are "
             << caminStudent->getNrLocuriLibere() << " locuri libere\n";
      }
      else if (input == '5') {
        system("CLS");
        cout << "Alege universitate unde se vor redistribui locurile: \n";
        for (int i = 0; i < universitati.size(); i++) {
          cout << "(" << i << ") " << universitati[i] << endl;
        }
        cout << "-> ";
        int indexUniversitate;
        cin >> indexUniversitate;
        universitati[indexUniversitate].repartizeazaStudentiiLaCamine();
        cout << "Locurile au fost redistribuite.\n";
      }
      else if (input == '6') {
        break;
      }
    }
    if (input == '6') break;
  }
  return 0;
}
