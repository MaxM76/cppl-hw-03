#include <iostream>
#include <Windows.h>

class SmartArrayCreateException : public std::exception
{
public:
	const char* what() const override {
		return "SmartArray не может быть создан";
	}
};

class SmartArrayBadIndexException : public std::exception
{
public:
	const char* what() const override {
		return "Недопустимый индекс элемента";
	}
};

class SmartArrayEmptySpaceException : public std::exception
{
public:
	const char* what() const override {
		return "Недостаточный размер массива";
	}
};

class smart_array {
private:
	int* array = nullptr;
	int size = 0;
	int newIndex = 0;

public:
	smart_array(int size) {
		if (size > 0) {
			try {
				array = new int[size]();
				this->size = size;
			}
			catch (const std::exception& ex) {
				throw SmartArrayCreateException();
			}
		}
		else {
			throw SmartArrayCreateException();
		}

	}

	~smart_array() {
		delete[] array;
	}

	int add_element(int element) {
		if (newIndex < size) {
			array[newIndex] = element;
			newIndex++;
			return newIndex - 1;
		}
		else {
			throw SmartArrayEmptySpaceException();
		}
	}

	int get_element(int index) {
		if ((index >= 0) && (index < size)) {
			return array[index];
		}
		else {
			throw SmartArrayBadIndexException();
		}
	}

	int getSize() {
		return size;
	}

	smart_array& operator=(smart_array& other) {
		delete[] array;
		size = other.getSize();
		array = new int[size];
		for (int i = 0; i < size; i++) {
			array[i] = other.get_element(i);			
		}
		newIndex = size;
		return *this;
	}
};


int main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

    smart_array arr(5);
    arr.add_element(1);
    arr.add_element(4);
    arr.add_element(155);

    smart_array new_array(2);
    new_array.add_element(44);
    new_array.add_element(34);

	std::cout << "First array\n";
	for (int i = 0; i < arr.getSize(); i++) {
		std::cout << arr.get_element(i) << "\t";
	}
	std::cout << "\n";

	std::cout << "Second array\n";
	for (int i = 0; i < new_array.getSize(); i++) {
		std::cout << new_array.get_element(i) << "\t";
	}
	std::cout << "\n";

	
	arr = new_array;

	std::cout << "Result of =\n";
	for (int i = 0; i < arr.getSize(); i++) {
		std::cout << arr.get_element(i) << "\t";
	}
	std::cout << "\n";
	
	/*
	new_array = arr;

	std::cout << "Result of =\n";
	for (int i = 0; i < new_array.getSize(); i++) {
		std::cout << new_array.get_element(i) << "\t";
	}
	std::cout << "\n";
	*/
}