#include <cstddef>
#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>
#include <string>
#include "persona.h"
#include "lista.h"
using namespace std;

//Marco Iván Pacheco Martinez
//Andrew Steven Williams Ponce 

LinkedList<Persona> readFile(string filename){
    LinkedList<Persona> lista;
    ifstream archivo(filename); //O(1)
    string linea; //O(1)
    char delimitador = ','; //O(1)
    getline(archivo ,linea); //O(1)
    cout<<"Archivo Leido"<<endl; //O(1)
    while(getline(archivo,linea)){
      stringstream stream(linea);
      string id,first_name,last_name,ZIP,city;//O(1)
      getline(stream, id,delimitador);//O(1)
      getline(stream, first_name, delimitador);//O(1)
      getline(stream, last_name, delimitador);//O(1)
      getline(stream, ZIP, delimitador);//O(1)
      getline(stream, city, delimitador);//O(1)
      Persona person(stoi(id),stoi(ZIP),first_name,last_name,city);
      lista.addLast(person);
    }
  return lista;
}

void mergeAscendente(LinkedList<Persona> list, int p, int q, int n) {
  
  int n1 = q - p + 1;
  int n2 = n - q;

  //int L[n1], M[n2];
  LinkedList <Persona> L,M;
  for (int i = 0; i < n1; i++)  //O(N)
    //L[i] = arr[p + i];
    L.addLast(list.get(p+i)); //O(N)
  for (int j = 0; j < n2; j++) //O(N)
    //M[j] = arr[q + 1 + j];
    M.addLast(list.get(q+1+j)); //O(N)

  int i, j, k;
  i = 0;
  j = 0;
  k = p;
  while (i < n1 && j < n2) { //O(N)
    if (L.get(i).getLastName() < M.get(j).getLastName()) {
      //arr[k] = L[i];
      list.replace(L.get(i),k); //O(N)
      i++;
    } else {
      //arr[k] = M[j];
      list.replace(M.get(j),k); //O(N)
      j++;
    }
    k++;
  }//O(N^2)
  while (i < n1) { //O(N)
    //arr[k] = L[i];
    list.replace(L.get(i),k); //O(N)
    i++;
    k++;
  }//O(N^2)

  while (j < n2) {  //O(N)
    //arr[k] = M[j];
    list.replace(M.get(j),k); //O(N)
    j++;
    k++;
  }//O(N^2)
}

void mergeSortAscendente(LinkedList<Persona> list, int l, int n) {
  if (l < n) {
    int m = l + (n - l) / 2;

    mergeSortAscendente(list, l, m);
    mergeSortAscendente(list, m + 1, n);

    mergeAscendente(list, l, m, n);
  }
}

void mergeDescendente(string array[], int low, int high, int mid){

  int i=low,j=mid+1,k=0;
  string temp[high-low+1];
  
  while(i<=mid && j<= high){
    if(array[i]>array[j])            //comparison step
      temp[k++]=array[i++];
    else
      temp[k++]=array[j++];
  }
  while(i<=mid){
    temp[k++]=array[i++];
  }
  while(j<=high){
    temp[k++]=array[j++];
  }
  
  for(i=low;i<=high;i++){
  
      array[i]=temp[i-low];
  
  }
}

void mergeSortDescendente(string array[],int low, int high){
  int mid;
  if(low<high){
      mid=(low+high)/2;
  
      mergeSortDescendente(array,low,mid);
      mergeSortDescendente(array,mid+1,high);
      mergeDescendente(array,low,high,mid);
  }
}

void biggestCitys(LinkedList<Persona> lista, int firstN){
  LinkedList<Persona> copyLista;
  for(int i = 0;i<lista.size();i++){
    copyLista.addLast(lista.get(i)); //O(1)
  }  //O(N)
  for(int i = 0;i<firstN;i++){ //O(N)
    string listaCiudad[copyLista.size()];
    for(int i = 0; i < copyLista.size();i++){ //O(N)
      listaCiudad[i] = copyLista.get(i).getCity(); //O(N)
    }//O(N^3)
    mergeSortDescendente(listaCiudad,0,copyLista.size()-1); //O(n log n)
    int countAct = 1;
    int maxcount = 0;
    string biggestCity;
    for(int i = 0; i<copyLista.size();i++){ //O(N)
      if(listaCiudad[i] == listaCiudad[i+1]){
        countAct++;
      }else{
        if(countAct > maxcount){
          maxcount = countAct;
          biggestCity = listaCiudad[i];
        }
        countAct = 1;
      }
    }
    cout<<"Ciudad: "<<biggestCity<<" ,Habitantes registrados: "<<maxcount<<endl;
    for(int i = 0;i<copyLista.size();i++){//O(N)
      if(copyLista.get(i).getCity() == biggestCity){//O(N)
        copyLista.remove(i);//O(N)
      }  
    }
  }
}//O(N^3)

void frecFirstName(LinkedList<Persona> lista, string res){
  int frec = 0;
  for(int i = 0;i <lista.size();i++){ //O(N)
    if(lista.get(i).getFirstName() == res){ //O(N)
      frec++;
    }
  }
  cout<<"El nombre "<<res<<" se repite en la lista: "<<frec<<" veces"<<endl;
} //O(N^2)

void personsPerCity(LinkedList<Persona> lista){
  string listaCiudades[lista.size()];
  for(int i = 0; i < lista.size();i++){ //O(N)
    listaCiudades[i] = lista.get(i).getCity(); //O(N)
  } //O(N^2)
  mergeSortDescendente(listaCiudades,0,lista.size()-1); //O(n log n)
  int count = 1;
  for(int i = 0; i<lista.size();i++){ //O(N)
    if(listaCiudades[i] == listaCiudades[i+1]){
      count++;
    }else{
      cout<<"Ciudad: "<<listaCiudades[i]<<" ,Habitantes registrados: "<<count<<endl;
      count = 1;
    }
  }
}//O(N^2)

void findLastName(LinkedList<Persona> lista, string res){
  int inf = 0, sup = lista.size() - 1;
  bool finded = false;
  while(inf <= sup && !finded){ //O(N)
    int med = (inf + sup)/2;
    if(lista.get(med).getLastName() == res){//O(N)
      cout<<"Persona encontrada: "<<endl<<lista.get(med)<<endl;
      finded = true;
    }else if(res < lista.get(med).getLastName()){//O(N)
     sup = med -1;
    }else{
      inf = med + 1;
    }
  }
  if(finded == false){
    cout<<"No se encontro la persona"<<endl;
  }
}//O(N^2)

int main() {
  string res;
  cout<<"Ingresa nombre del archivo: "<<endl;
  cin>>res;
  LinkedList<Persona> lista = readFile(res);
  int comp = 1;
  int resInt;
  bool binS = false;
  while(comp == 1){
    cout<<endl;
    cout<<"1- 5 ciudades con mas personas registradas"<<endl;
    cout<<"2- Imprimir la frecuencia de un first-name"<<endl;
    cout<<"3- ¿Cuantos habitantes existen por ciudad?"<<endl;
    cout<<"4- Mostrar ordenada la lista ordenada"<<endl;
    cout<<"5- Encontrar un last-name utilizando busqueda binaria"<<endl;
    cout<<"6- Salir"<<endl;
    cin>>resInt;
    switch (resInt){
    case 1:
      biggestCitys(lista,5);
      cout<<"Complejidad: O(N^3)"<<endl;
      cout<<"Mejor caso: Las ciudades mas grandes empiezan por letras de S-Z"<<endl;
      cout<<"Caso promedio: Las ciudades mas grandes empiezan por las letras: K-R"<<endl; 
      cout<<"Peor caso: Las ciudades mas grandes empiezan por las letras: A-J"<<endl;
      break;
    case 2:
      cout<<"Ingresa un first-name para encontrar con que frecuencia se repite: "<<endl;
      cin>>res;
      frecFirstName(lista,res);
      cout<<"Complejidad: O(N^2)"<<endl;
      cout<<"Mejor caso: Todos los first-names esta casi al principio de la lista"<<endl;
      cout<<"Caso promedio: La mayoria de first-names estan por la mitad de la lista"<<endl;
      cout<<"Peor caso: Casi todos los first-name estan por el final de la lista"<<endl;
      break;
    case 3:
      personsPerCity(lista);
      cout<<"Complejidad: O(N^2)"<<endl;
      cout<<"El peor, promedio y mejor caso dependen de que tan ordenado en orden alfbetico esten las ciudades"<<endl;
      break;
    case 4:
      if(binS == false){
        cout<<"Ordenando Lista Ligada...."<<endl;
        mergeSortAscendente(lista,0,lista.size()-1); 
        for(int i = 0; i<lista.size();i++){
          cout<<lista.get(i)<<endl;
        }
        cout<<"Lista ordenada"<<endl;
        cout<<"Complejidad: O(N^2)"<<endl;
        cout<<"Mejor caso: Casi todos los elementos estan en orden alfabetico"<<endl;
        cout<<"Caso promedio: La mitad de los elementos de la lista no estan ordenados"<<endl; 
        cout<<"Peor caso: Casi nunguno de las elementos estan en orden alfabetico"<<endl;
        binS = true;
      }else{
        for(int i = 0; i<lista.size();i++){
          cout<<lista.get(i)<<endl;
        }
        cout<<"La lista ya ha sido ordenada"<<endl;
      }
      break;
    case 5:
      if(binS == false){
        cout<<"No se puede realizar busqueda binaria, la lista aun no esta ordenada,"<<endl;
      }else{
        cout<<"Dame un last_name para encontrar a una persona: "<<endl;
        cin>>res;
        findLastName(lista,res);
        cout<<"Complejidad: O(N^2)"<<endl;
        cout<<"Al tener la lista ordenada, el mejor,promedio o el pero caso dependera de la posicion del last-name, ya sea al principio, al final o en medio de las mitades que se van dividiendo"<<endl;
        
      }
      break;
    case 6:
      comp = 0;
      break;
    default:
      break;
    }
  }
  cout << "finito" << endl;  
}
  