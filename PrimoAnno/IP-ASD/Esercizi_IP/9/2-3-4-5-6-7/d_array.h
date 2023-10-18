struct dynamic_array {
    int* store;
    unsigned int size;
};

//Crea un array leggendo valori da input
void read_d_array(dynamic_array& d);

//Stampa tutti gli elementi dell'array
void print_d_array(const dynamic_array& d);

//Svuota un array: array.size verrà impostata su 0 e verrà cancellato il riferimento in memoria
void delete_d_array(dynamic_array& d);

//int s = size dell'array;
//int v = valore
//
//inizializza d in modo che la sua size sia == s e tutti gli elementi siano v;
void create_d_array(dynamic_array& d, int s, int v);

//Assegna value al index del array dinamico d;
void set(dynamic_array& d, int index, int value);

//Ritorna il valore di un elemento dell'array d in posizione index
int get(const dynamic_array& d, int index);

//Ordina l’array secondo l’algoritmo SelectionSort
void SelectionSort(dynamic_array& d);
