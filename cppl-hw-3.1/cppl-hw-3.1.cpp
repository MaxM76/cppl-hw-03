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
				this -> size = size;
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
			//return -1;
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
};

int main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	try {
		smart_array arr(5);
		arr.add_element(1);
		arr.add_element(4);
		arr.add_element(155);
		arr.add_element(14);
		arr.add_element(15);
		std::cout << arr.get_element(7) << std::endl;
	}
	catch (const std::exception& ex) {
		std::cout << ex.what() << std::endl;
	}
}