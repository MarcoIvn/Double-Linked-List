#include <iostream>
using namespace std;

class Persona;
ostream& operator<< (ostream&,const Persona &);

class Persona{
  private:
    string first_name,last_name,city;
    int id, zip;
  public:
    Persona(int id = 0, int zip = 0, string fname = "", string lname = "", string city = ""){
      this->id = id;
      this->zip = zip;
      this->first_name = fname;
      this->last_name = lname;
      this->city = city;
    }
    
    string getCity(){
      return this->city;
    }
    string getFirstName(){
      return this->first_name;
    }
    string getLastName(){
      return this->last_name;
    }
  //Agrega las sobre cargas de operadores necesarias en la clase Persona.
    friend ostream& operator<< (ostream&,const Persona &);
};

ostream& operator<< (ostream & salida, const Persona & persona){
  salida <<"id: "<<persona.id <<", ZIP: "<<persona.zip<<", First name: "<<persona.first_name<<", Last name: "<<persona.last_name<<", City: "<<persona.city;
  return salida;
}