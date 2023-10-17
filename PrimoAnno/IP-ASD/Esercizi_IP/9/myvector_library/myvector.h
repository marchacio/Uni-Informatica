struct myvector {
  int size;
  int capacity;
  int* store;
};

void print(myvector& vector);

void create(myvector& v, int capacity);

void push_back(myvector& v, int x);

int pop_back(myvector& v);

void set(myvector& v, int value, int index);

void selectionSort(myvector& v);
