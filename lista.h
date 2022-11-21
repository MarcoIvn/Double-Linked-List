template <typename T> class Node {
private:
  T data;
  Node<T> *next;
  Node<T> *previous;
  template <typename U> friend class LinkedList;

public:
  Node(T data, Node<T> *next, Node<T> *previous) {
    this->data = data;
    this->next = next;
    this->previous = previous;
  }
};

template <typename T> class LinkedList {
private:
  Node<T> *head;
  Node<T> *last;
  int _size;

public:
  LinkedList() {
    head = last = NULL;
    _size = 0;
  }

  /*~LinkedList(){
    while (head->next != head){
      Node<T>* aux = head->next;
      aux->next->previous = head;
      head->next = aux->next;
      delete aux;
	  }
	  delete head;
  }*/

  /*
  Método para agregar un nodo al inicio de la lista.
  */
  void addFirst(T dato) {
    _size++;
    // SORT the code:
    Node<T> *nuevo = new Node<T>(dato, NULL, NULL);
    if (head == NULL && last == NULL) { // si es vacía la lista
      head = last = nuevo;
    } else {
      nuevo->next = head;
      head->previous = nuevo;
      head = nuevo;
    }
  }
  /*
  Método imprime todos los nodos de la lista
  */
  void print() {
    Node<T> *aux = head;
    while (aux != NULL) {
      cout << aux->data << endl;
      aux = aux->next;
    }
  }
  /*
  Método imprime todos los nodos de la lista
  */
  void reverse() {
    Node<T> *aux = last;
    while (aux != NULL) {
      cout << aux->data << endl;
      aux = aux->previous;
    }
  }

  /*
  Método que regresa 1, si la lista no tiene elementos.
  */
  bool is_empty() { return (head == NULL) ? true : false; }
  /*
  Método para agregar un nodo al final de la lista.
  */
  void addLast(T dato) {
    _size++;
    Node<T> *nuevo = new Node<T>(dato, NULL, NULL);
    if (is_empty()) {
      head = last = nuevo; // addFirst(dato)
    } else {
      last->next = nuevo;
      nuevo->previous = last;
      last = nuevo;
    }
  }
  /*
  Método para calcular el tamaño de la lista, cuántos elementos tenemos.
  */
  int size() { return this->_size; }

  /*
  Método para revisar si existe un elemento, regresa 1 si existe o 0 sino
  existe.
  */
  bool contains(T data) {
    Node<T> *temp = head;
    bool exists = 0;
    while (temp != NULL && exists == 0) {
      if (data == temp->data) {
        exists = 1;
      }
      temp = temp->next;
    }
    return exists;
  }

  /*
  Método para obtener un elemento que se encuentra en una posición: "index".
  Si index es menor a 0 o mayor al tamaño se lanza exception.
  */
  T get(int index) {
    if (index < 0 || index > size())
      throw -1;
    Node<T> *temporal = head;
    for (int i = 0; i < index; i++) {
      temporal = temporal->next;
    }
    return temporal->data;
  }

  /*
  Método para remover de la lista el primer elemento, si la lista NO es vacía
  se puede realizar.  */
  T remove_front() {
    if (is_empty()) {
      throw -1;
    } else if (head == last) {
      // 1 nodo
      T dato = head->data; // sacar dato
      delete head;         // borrar nodo
      head = last = NULL;
      _size--;
      return dato;
    } else {
      // minimo 2 nodos
      T dato = head->data;
      head = head->next;
      delete head->previous;
      head->previous = NULL;
      _size--;
      return dato;
    }
  }

  /*
  Método para remover de la lista el último elemento, si la lista NO es vacía
  se puede realizar.  */
  T remove_last() {
    if (is_empty()) {
      throw -1;
    } else if (head == last) {
      // 1 nodo
      T dato = head->data; // sacar dato
      delete head;         // borrar nodo
      head = last = NULL;
      _size--;
      return dato;
    } else {
      // minimo 2 nodos
      T dato = last->data;
      last = last->previous;
      delete last->next;
      last->next = NULL;
      _size--;
      return dato;
    }
  }

  /*
  Obtiene el dato guardado en el último nodo
  */
  T getFirst() {
    if (is_empty()) {
      throw 1;
    }
    return head->data;
  }

  /*
  Obtiene el dato guardado en el último nodo
  */
  T getLast() {
    if (is_empty()) {
      throw 1;
    }
    return last->data;
  }

  /*
  Método para remover de la lista el último elemento, si la lista NO es vacía
  se puede realizar.  */
  T remove(int index) {
    if (is_empty()) {
      throw -1;
    } else if (index == 0) {
      return remove_front();
    } else if (index == _size) {
      return remove_last();
    } else {
      Node<T> *aux = head;
      for (int i = 0; i < index; i++)
        aux = aux->next;
      // minimo 2 nodos
      T dato = aux->data;
      aux->previous->next = aux->next;
      aux->next->previous = aux->previous;
      aux->next = NULL;
      aux->previous = NULL;
      delete aux;
      _size--;
      return dato;
    }
  }

  void insert(T dato, int index) {
    if (is_empty()) {
      throw -1;
    } else if (index < 0 && index > _size) {
      throw -1;
    } else {
      Node<T> *aux = head;
      for (int i = 0; i < index; i++)
        aux = aux->next;
      // minimo 2 nodos
      Node<T> *n = new Node<T>(dato, NULL, NULL);
      n->next = aux;
      n->previous = aux->previous;
      aux->previous = n;
      n->previous->next = n;
      _size++;
    }
  }

  //test
  T replace(T dato, int index){
    if(is_empty()){
      addFirst(dato);
    }else{
      Node<T> *aux = head;
      for (int i = 0; i < index; i++)
        aux = aux->next;
      T dator = aux->data;
      aux->data= dato;
      return dator;
    }
  }
};
