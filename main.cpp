#include <iostream>
#include <cstring>
#include <ctype.h>

using namespace std;

void Swap(int*, int*);

int StringLength(const char * str);

char GetCharacter(const char * prompt, const char * error);

char GetCharacter(const char* prompt, const char * error, const char validInput[], const int validInputLength);

int * Func();

void Use(int * noptrInt);

const int IGNORE_CHARS = 256;

void TestChar() {
	char validInput[] = {'y', 'n'};

	char input = GetCharacter("Please enter a character: ", "Input Error! Please Try Again.", validInput, 2);

	cout << input << endl;
}

char * ReverseCopy(char * a, int n) {
	char * buffer = new char[n + 1];

	for (int i = 0, j = n - 1; i < n && i <= j; ++i, --j) {
		buffer[i] = a[j];
		buffer[j] = a[i];
	}

	buffer[n] = '\0';

	return buffer;
}


int * CreateDynamicArray(int capacity, int& size);
void DeleteDynamicArray(int * dynamicArray, int& size);
void InsertElement(int ** dynamicArray, int element, int& size, int& capacity);
void DeleteElement(int ** dynamicArray, int elementIndex, int& size);
void ResizeDynamicArray(int ** dynamicArray, int size, int newCapacity);


int main() {

	int size = 0, capacity = 3;
	int * arr = CreateDynamicArray(capacity, size);

	InsertElement(&arr, 1, size, capacity);
	InsertElement(&arr, 2, size, capacity);
	InsertElement(&arr, 3, size, capacity);
	InsertElement(&arr, 4, size, capacity);

	for (int i = 0; i < size; ++i)
		cout << arr[i] << ' ';

	cout << endl;
	DeleteElement(&arr, 0, size);
	DeleteElement(&arr, 0, size);
	DeleteElement(&arr, 0, size);
	DeleteElement(&arr, 0, size);

	for (int i = 0; i < size; ++i)
		cout << arr[i] << ' ';


	DeleteDynamicArray(arr, size);

	delete arr;
	arr = nullptr;

	return 0;
}

int * CreateDynamicArray(const int capacity, int& size) {
	size = 0;
	return new int[capacity];
}

void DeleteDynamicArray(int * dynamicArray, int& size) {
	size = 0;
}

void InsertElement(int ** dynamicArray, const int element, int& size, int& capacity) {
	if (size > capacity) {
		capacity *= 2;
		ResizeDynamicArray(dynamicArray, size, capacity);
	}

	(*dynamicArray)[size] = element;
	++size; 
}

void DeleteElement(int ** dynamicArray, const int elementIndex, int& size) {
	if (size != 0) {
		if (elementIndex != size - 1) {
			for (int i  = elementIndex + 1; i < size; ++i) {
				(*dynamicArray)[i - 1] = (*dynamicArray)[i];
			}
		} 
	}
	--size;
	ResizeDynamicArray(dynamicArray, size, size);
}

void ResizeDynamicArray(int ** dynamicArray, int size, int newCapacity) {
	int * newDynamicArray = new int[newCapacity];

	for (int i = 0; i < size; ++i) {
		newDynamicArray[i] = (*dynamicArray)[i];
	}

	delete (*dynamicArray);

	(*dynamicArray) = nullptr;

	(*dynamicArray) = newDynamicArray;
}


int * Func() {
	return new int;	
}

void Use(int * noptrInt) {

}

char GetCharacter(const char * prompt, const char * error) {
	char input;
	bool failure;


	do {
		failure = false;

		cout << prompt;
		cin >> input;

		if (cin.fail()) {
			cin.clear();
			cin.ignore(IGNORE_CHARS, '\n');
			failure = true;
			cout << error << endl;
		} else {
			cin.ignore(IGNORE_CHARS, '\n');

			if (isalpha(input)) {
				input = tolower(input);
			} else {
				cout << error << endl;
				failure = true;
			}

		}

	} while (failure);

	return input;
}

char GetCharacter(const char* prompt, const char * error, const char validInput[], const int validInputLength) {
	char input;
	bool failure;

	do {
		failure = false;

		cout << prompt;
		cin >> input;

		if (cin.fail()) {
			cin.clear();
			cin.ignore(IGNORE_CHARS, '\n');
			failure = true;
			cout << error << endl;
		} else  {
			cin.ignore(IGNORE_CHARS, '\n');

			if (isalpha(input)) {
				for (int i = 0; i < validInputLength; ++i) {
					if (validInput[i] == input) {
						return input;
					}
				}
			} 

			cout << error << endl;
			failure = true;
		}

	} while(failure);

	return input;
}

void Swap(int* x, int* y) {
	int tmp = *y;

	*y = *x;
	*x = tmp;
}


int StringLength(const char * str) {

	const char * pStr = str;

	int n = 0;

	if (pStr != nullptr) {
		while (*pStr != '\0') {
			++n;
			++pStr;
		}

	}

	return n;

}