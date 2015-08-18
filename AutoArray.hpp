template <class T>
class AutoArray{
private:
	T *Array;
	int size;
	int head;
	int tail;
	void make_space(int n);
public:
	AutoArray();
	AutoArray(AutoArray<T> &copy);
	~AutoArray();

	bool isEmpty();
	int _size();
	T pop();
	T pop_back();
	void push(T val);
	void push_back(T val);
	void insert(int i, T val);
	T retrieve(int i);
	T retrieveHead();
	T retrieveTail();
	AutoArray<T> &operator=(AutoArray<T> &copy);
	
};

/*------------------------------------------------------------/
Default Constuctor
Initializes values for data members:
size, Array, head, tail
/------------------------------------------------------------*/
 
template <class T>
AutoArray<T>::AutoArray(){
	size = 2;
	Array = new T[size];
	head = 0;
	tail = 0;
}

/*------------------------------------------------------------/
Copy constuctor
Creates a copy of the existing list
/------------------------------------------------------------*/

template <class T>
AutoArray<T>::AutoArray(AutoArray<T>& copy){
	size = copy.size;
	Array = new T[size];
	head = 0;
	tail = 0;
	for (int i = 0; i < copy._size(); i++)
		push(copy.retrieve(i));
}

/*------------------------------------------------------------/
Destructor
Frees allocated memory
Sets all datamember values to zero
/------------------------------------------------------------*/

template <class T>
AutoArray<T>::~AutoArray(){
	delete[] Array;
	size = 0;
	head = 0;
	tail = 0;
	Array = (T*)0;
}

/*------------------------------------------------------------/
Checks if the list is emty
Returns a boolean type
/------------------------------------------------------------*/

template <class T>
bool AutoArray<T>::isEmpty(){
	return head == tail;
}

/*------------------------------------------------------------/
Finds the size of the list
Returns a int type
/------------------------------------------------------------*/

template <class T>
int AutoArray<T>::_size(){
	return (head - tail + size) % size;
}

/*------------------------------------------------------------/
Returns the Element of [index] of your choice
/------------------------------------------------------------*/

template <class T>
T AutoArray<T>::retrieve(int i){
	if (i<0)
		return Array[(head + size + i) % size];
	return Array[(tail + i) % size];

}

/*------------------------------------------------------------/
Returns the value for the datamember head
(used for debugging)
/------------------------------------------------------------*/

template <class T>
T AutoArray<T>::retrieveHead(){
	return head;
}

/*------------------------------------------------------------/
Returns the value for the datamember tail
(used for debugging)
/------------------------------------------------------------*/

template <class T>
T AutoArray<T>::retrieveTail(){
	return tail;
}

/*------------------------------------------------------------/
Inserts an element to the [index] of your choosing
/------------------------------------------------------------*/

template <class T>
void AutoArray<T>::insert(int i, T val){
	if (i<0)
		Array[(head + size + i) *size] = val;
	else
		Array[(tail + i) % size] = val;
}

/*------------------------------------------------------------/
Calls the function make_space to ensure that there will
be space for the next element to be stored in the list.
Sets the place for an element incrementally from the start
/------------------------------------------------------------*/

template <class T>
void AutoArray<T>::push(T val){
	make_space(_size() + 1);
	Array[head] = val;
	head = (head + 1) % size;
}

/*------------------------------------------------------------/
Calls the function make_space to ensure that there will
be space for the next element to be stored in the list.
Sets the place for an element incrementally from the end
/------------------------------------------------------------*/

template <class T>
void AutoArray<T>::push_back(T val){
	make_space(_size() + 1);
	tail = (tail + size - 1) % size;
	Array[tail] = val;
}

/*------------------------------------------------------------/
Returns the element that was placed starting from the head
/------------------------------------------------------------*/

template <class T>
T AutoArray<T>::pop(){
	if (_size() <= 0)
		return Array[0];
	head = (head + size - 1) % size;
	return Array[head];
}

/*------------------------------------------------------------/
Returns the element that was placed starting from the tail
/------------------------------------------------------------*/

template <class T>
T AutoArray<T>::pop_back(){
	T val = Array[tail];
	tail = (tail + 1) % size;
	return val;
}

/*------------------------------------------------------------/
Checks the size the of list.
Depending on the condition, if the list is smaller 
than the argument, the list size will be double,
space will be allocated for the list
/------------------------------------------------------------*/

template <class T>
void AutoArray<T>::make_space(int n){
	if (size > n)
		return;
	int Size = size;
	while (Size <= n)
		Size *= 2;
	T *newArray = new T[Size];
	for (int i = 0; i < _size(); i++)
		newArray[i] = retrieve(i);

	delete[] Array;
	Array = newArray;
	head = _size();
	tail = 0;
	size = Size;
}

/*------------------------------------------------------------/
Operator overload= 
Inorder to set the list to be equal to each other
Uses a copy
/------------------------------------------------------------*/

template <class T>
AutoArray<T> &AutoArray<T>::operator=(AutoArray &copy){
	delete[] Array;
	size = copy.size;
	Array = new T[size];
	head = 0;
	tail = 0;
	for (int i = 0; i < copy._size(); i++)
		push(copy.retrieve(i));
}
