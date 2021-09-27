#pragma once
#include <iostream>
#include <string>
using namespace std;


template <class Type>
class List {
public:
	Type* values;
	int capacity;
	int counter;

	List(int cap) {
		counter = 0;
		values = new Type[cap];
		for (int i = 0; i < cap; i++) {
			values[i] = NULL;
		}
		capacity = cap; //default
	}
	bool insert(Type item);
	bool isFull();
	void print();
	bool isEmpty();
	bool insertAt(Type value, int index);
	bool insertAfter(Type itemTobeInserted, Type item);
	bool insertBefore(Type itemTobeInserted, Type item);
	bool remove(Type item);
	bool removeAfter(Type item);
	bool removeBefore(Type item);
	bool reverse();
	bool operator==(const List<Type>& right) const;
};

template<class Type>
bool List<Type>::insert(Type item) {
	if (counter >= capacity)
		return false;
	values[counter++] = item;
	return true;
}
template<class Type>
void List<Type>::print() {
	int i=0;
	std::cout << std::endl;
	while (i<counter) {
		std::cout << values[i++] << " ";
	}
}

template<class Type>
bool List<Type>::isFull() {
	if (counter >= capacity)
		return true;
	return false;
}
template<class Type>
bool List<Type>::isEmpty() {
	if (counter == 0)
		return true;
	return false;
}

template <class Type>
bool List<Type>::insertAt(Type value, int index) {
	if (!isEmpty()) {
		values[index] = value;
		return true;
	}
	return false;

}
template <class Type>
bool List<Type>::insertAfter(Type itemTobeInserted, Type item) {
	int i = 0;
	while (!isEmpty()) {
		if (values[i]==item) {
			values[i+1] = itemTobeInserted;
			return true;
		}
		i ++ ;
	}
	return false;
}

template <class Type>
bool List<Type>::insertBefore(Type itemTobeInserted, Type item) {
	int i = 0;
	while (!isEmpty()) {
		if (values[i] == item) {
			values[i - 1] = itemTobeInserted;
			return true;
		}
		i++;
	}
	return false;
}

template <class Type>
bool List<Type>::remove(Type item) {

	int i = 0;
	while (!isEmpty()) {
		if (values[i] == item) {
			for (int j = i; j < counter; j++) {
				values[j] = values[j +1];
			}
			counter--;
			return true;
		}
		i++;
	}
	print();
	return false;


}
template <class Type>
bool List<Type>::removeAfter(Type item) {
	int i = 0;
	while (!isEmpty()) {
		if (values[i] == item) {
			for (int j = i-1; j < counter; j++) {
				values[j] = values[j + 1];
			}
			counter--;
			return true;
		}
		i++;
	}
	return false;


}

template <class Type>
bool List<Type>::removeBefore(Type item) {
	int i = 0;
	while (!isEmpty()) {
		if (values[i] == item) {
			for (int j = i -1 ; j < counter; j++) {
				values[j] = values[j + 1];
			}
			counter--;
			return true;
		}
		i++;
	}
	return false;
}

template<class Type>
bool List<Type>::reverse() {

	int *reverse;
	reverse = new int[capacity];
	for (int i = 0; i < capacity; i++) {
		reverse[i] = NULL;
	}

	int j = 0;
	cout << endl;
	for (int i = capacity-1; i > 0; i--) {
		reverse[j++] = values[i];
		cout << reverse[i] << " ";
	}
	j = counter-1;
	for (int i = 0; i <capacity ; i++) {
		//values[i] = reverse[j--];
	}

	return true;
    
}
template<class Type>
bool  List<Type>::operator==(const List<Type>& right) const {
	int i = 0;
	while (i<counter) {
		if (values[i] != right.values[i]) {
			return false;
		}
		i++;
	}
	return true;
}



//Q2

//template <class Type>
bool EmailValidation(string str) {
	string str2 = str;
	
	return false;
}

bool PasswordValidation(string password) {
	int i = 0;
	return false;

}
