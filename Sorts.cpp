#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>

void print(std::vector<int> array) {
	int n = array.size();
	for (int i = 0; i < n; i++)
	{
		std::cout << " " << array[i];
	}
	std::cout << "\n";
}

std::vector<int> randgen(int n, std::vector<int> array) {
	srand(time(0));
	for (int i = 0; i < n; i++) {
		array.push_back(rand());
	}
	return array;
}

//Bubblesort------------------------------------

void bubblesort(std::vector<int> &array) {
	int n = array.size();
	int aux=0;
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 0; j < n - 1; j++)
		{
			if (array[j] > array[j + 1])
			{
				aux = array[j];
				array[j] = array[j + 1];
				array[j + 1] = aux;
			}
		}
	}
}

//insertsort------------------------------------

void insertsort(std::vector<int>& array) {
	int aux = 0, cont = 0, n = array.size();
	int* min = NULL;
	std::vector<int> array2;
	for (int i = 0; i != n; n--)
	{
		min = &array[0];
		for (int j = 0; j < n; j++)
		{
			if (*min > array[j])
			{
				min = &array[j];
				aux = j;
			}
		}
		array2.push_back(*min);
		array.erase(array.begin() + aux);
		aux = 0;
	}
	array = array2;
}

//selectsort------------------------------------

void selectsort(std::vector<int> &array) {
	int n = array.size();
	int aux = 0, cont = 0;
	int* min=NULL;
	for (int i = 0; i < n; i++)
	{
		min = &array[cont];
		for (int j = cont; j < n; j++)
		{
			if (*min > array[j])
			{
				min = &array[j];
			}
		}
		aux = *min;
		*min = array[cont];
		array[cont] = aux;
		cont++;
	}
}

//mergesort------------------------------------

void mergesort(std::vector<int>& array, std::vector<int>::iterator i, std::vector<int>::iterator d) {
	std::vector<int>::iterator ini = i, final = d, medio = ini + (final - ini) / 2, der = medio + 1;
	
	if (ini >= final)
		return;

	mergesort(array, i, medio);
	mergesort(array, medio + 1, d);

	std::vector<int>arr1, arr2;
	for (std::vector<int>::iterator i = ini; i <= medio; i++) {
		arr1.push_back(*i);
	}
	for (std::vector<int>::iterator i = medio + 1; i <= final; i++) {
		arr2.push_back(*i);
	}
	std::vector<int>::iterator arr1_ini = arr1.begin(), arr2_ini = arr2.begin();
	while (arr1_ini < arr1.end() && arr2_ini < arr2.end()) {
		if (*arr1_ini <= *arr2_ini) {
			*ini = *arr1_ini;
			ini++; arr1_ini++;
		}
		else {
			*ini = *arr2_ini;
			ini++; arr2_ini++;
		}
	}
	while (arr1_ini < arr1.end()) {
		*ini = *arr1_ini;
		ini++; arr1_ini++;
	}
	while (arr2_ini < arr2.end()) {
		*ini = *arr2_ini;
		ini++; arr2_ini++;
	}
}

//quicksort------------------------------------

void Qsort(std::vector<int>& array){
	if (array.size() <= 1)
		return;
	std::vector<int>::iterator piv = array.begin();
	std::vector<int> arr1, arr2;
	int aux = 0;
	for (std::vector<int>::iterator i = array.begin(); i < array.end(); i++)
	{
		if (*i < *piv){
			arr1.push_back(*i);
		}
		else if (*i > *piv){
			arr2.push_back(*i);
		}
	}
	Qsort(arr1);
	arr1.push_back(*piv);
	Qsort(arr2);
	arr1.insert(arr1.end(), arr2.begin(), arr2.end());
	array = arr1;
}

//heapsort ------------------------------------

void minheap(std::vector<int>& array, std::vector<int>::iterator i) {
	std::vector<int>::iterator iz, de, min = i;

	int count = 0;
	for (std::vector<int>::iterator it = array.begin(); it < i; it++){
		count++;
	}
	iz = (array.begin() + (count * 2) + 1); de = (array.begin() + (count * 2) + 2);

	int aux;
	if (iz < array.end() && *iz < *i)
		min = iz;
	if (de < array.end() && *de < *min)
		min = de;
	if (min != i) {
		aux = *i;
		*i = *min;
		*min = aux;
		minheap(array, min);
	}
}

void heapsort(std::vector<int>& array) {

	minheap(array, array.end() - 1);

	int size = array.size();
	for (std::vector<int>::iterator i = array.begin() + (size / 2) - 1; i == array.begin(); i--) {
		minheap(array, i);
	}
	std::vector<int> aux;
	for (int j = 0; j < size; j++) {
		std::vector<int>::iterator ini = array.begin();

		if (array.size() == 1) {
			aux.push_back(*ini);
			array = aux;
			return;
		}
		
		std::vector<int>::iterator temp = array.end()-1;

		int raiz = *ini;
		*ini = *temp;
		array.erase(temp);
		minheap(array,array.begin());
		aux.push_back(raiz);
	}
}

int main() {

	clock_t startTime = clock();

	std::vector<int> example;
	example = randgen(10000000, example);
	//JUST CHANGE THIS
	int n = 6;
	//JUST CHANGE THIS

	switch (n)
	{
	case 1:
		bubblesort(example);
		break;
	case 2:
		insertsort(example);
		break;
	case 3:
		selectsort(example);
		break;
	case 4:
		mergesort(example,example.begin(),example.end()-1);
		break;
	case 5:
		Qsort(example);
		break;
	case 6:
		heapsort(example);
		break;
	}

	std::cout << "\n SUCCESS\n"<< double(clock() - startTime) / (double)CLOCKS_PER_SEC << " seconds.";
}