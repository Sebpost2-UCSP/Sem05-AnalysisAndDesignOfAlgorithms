#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <string>

//MISC-----------------------------------------------------------------------------

//simple print de matrices 2d
std::vector<std::vector<int>> print(std::vector<std::vector<int>> array) {
	for (int i = 0; i < array.size(); i++) {
		for (int j = 0; j < array[0].size(); j++) {
			std::cout<<"|"<<array[i][j];
		}
		std::cout << "\n";
	}
	std::cout << "\n";
	return array;
}

//potencias de 2
int potencia_cuadrada(int x) {
	int r = 1;
	for (int i = 0; i < x; i++) {
		r = r * 2;
	}
	return r;
}

//suma vectores 2d
std::vector<std::vector<int>> suma_vectores(std::vector<std::vector<int>> a, std::vector<std::vector<int>> b) {
	std::vector<std::vector<int>> c;
	for (int i = 0; i < a.size(); i++) {
		c.push_back(std::vector<int>());
		for (int j = 0; j < a[0].size(); j++) {
			c[i].push_back(a[i][j] + b[i][j]);
		}
	}
	return c;
}

//numeros aleatorios
void randgen(int row, int col, std::vector<std::vector<int>> &array) {
	for (int i = 0; i < row; i++) {
		array.push_back(std::vector<int>());
		for (int j = 0; j < col; j++) {
			array[i].push_back(rand()%100);
		}
	}
}

//LECTOR Y GENERADOR DE TEXTO -----------------------------------------------------------------------------

std::vector<std::vector<std::vector<int>>> read() {
	int b1, b2,num1;
	std::string M, M1,M2,M3,M4,MI1,MI2;
	std::vector<std::vector<std::vector<int>>> T;
	std::ifstream O;
	O.open("C:/Users/sebpost/Documents/ADA/PRACTICA2/Matrices.txt");
	if (!O.is_open()) {
		std::cout << "No se puedo abrir el archivo";
		return T;
	}
	std::vector < std::vector<int >> a, b;
	while (!O.eof()) {
		O >> M >> M1 >> M2 >> M3 >> M4;
		std::cout << M << M1 << M2 << M3 << M4;
		MI1 = M3.erase(0, 1);
		MI2 = M4.substr(0, M4.size() - 1);
		b1 = std::stoi(MI1);
		b2 = std::stoi(MI2);
		for (int i = 0; i < b1; i++) {
			a.push_back(std::vector<int>());
			for (int j = 0; j < b2; j++) {
				O >> num1;
				a[i].push_back(num1);
			}
		}
		T.push_back(a);
		a = b;
	}
	return T;
}

void generate(std::vector<std::vector<int>> a) {
	std::ofstream O("array.txt");
	for (int i = 0; i < a.size(); i++) {
		for (int j = 0; j < a[0].size(); j++) {
			O << a[i][j] << " ";
		}
		O << "\n";
	}
	O << "\n\n\n";
}

//Multiplicacion standard---------------------------------------------------------------------------
std::vector<std::vector<int>> Multi_array(std::vector<std::vector<int>> a, std::vector<std::vector<int>> b)
{
	std::vector<std::vector<int>> c;
	int fil1 = a.size(), col1 = a[0].size(), fil2 = b.size(), col2=b[0].size();

	if (col1 != fil2) {
		std::cout << "\nNo se puede, col1 no es igual a fil2\n";
		return c;
	}

	//multiplicacion
	for (int i = 0; i < fil1; i++)
	{
		c.push_back(std::vector<int>());
		for (int j = 0; j < col2; j++)
		{
			c[i].push_back(0);
			for (int k = 0; k < col1; k++)
			{
				c[i][j] = c[i][j] + a[i][k] * b[k][j]; 
			}
		}
	}
	return c;
}

//Strassen----------------------------------------------------------------------------------------------
//llena la matriz de ceros (si es necesario)
std::vector<std::vector<int>> fillwith0(int pot, std::vector<std::vector<int>> a)
{
	while (pot != a.size())
		a.push_back(std::vector<int>());
	int i = 0;
	while (pot != a[a.size()-1].size()) {
		for (int j = a[i].size(); j < pot; j++) {
			a[i].push_back(0);
		}
		i++;
	}
	return a;
}

//quita los 0s extra de la matriz
void takeout0(std::vector<std::vector<int>>& a, int filA, int colB)
{
	std::vector < std::vector<int>> c;
	for (int i = 0; i < filA; i++){
		c.push_back(std::vector<int>());
		for (int j = 0; j < colB; j++) {
			c[i].push_back(a[i][j]);
		}
	}
	a = c;
}

//divide la matriz en 4 matrices
std::vector<std::vector<std::vector<int>>> div4(std::vector<std::vector<int>> a,int n) {
	std::vector<std::vector<int>> a1, a2, a3, a4;
	std::vector<std::vector<std::vector<int>>> partsX;
	for (int i = 0; i < n / 2; i++) {
		a1.push_back(std::vector<int>());
		for (int j = 0; j < n / 2; j++) {
			a1[i].push_back(a[i][j]);
		}
	}
	partsX.push_back(a1);
	for (int i = 0; i < n / 2; i++) {
		a2.push_back(std::vector<int>());
		for (int j = (n/2); j < n; j++) {
			a2[i].push_back(a[i][j]);
		}
	}
	partsX.push_back(a2);
	for (int i = (n / 2), i1=0; i < n; i++,i1++) {
		a3.push_back(std::vector<int>());
		for (int j = 0; j < n / 2; j++) {
			a3[i1].push_back(a[i][j]);
		}
	}
	partsX.push_back(a3);
	for (int i = (n / 2),i1=0; i < n; i++,i1++) {
		a4.push_back(std::vector<int>());
		for (int j = (n / 2); j < n; j++) {
			a4[i1].push_back(a[i][j]);
		}
	}
	partsX.push_back(a4);
	return partsX;
}

std::vector<std::vector<int>> unite4(std::vector<std::vector<int>> a, std::vector<std::vector<int>> b, std::vector<std::vector<int>> c, std::vector<std::vector<int>> d, int n) {
	std::vector<std::vector<int>> unite;
	for (int i = 0; i < n / 2; i++) {
		unite.push_back(std::vector<int>());
		for (int j = 0; j < n / 2; j++) {
			unite[i].push_back(a[i][j]);
		}
	}
	for (int i = 0; i < n / 2; i++) {
		for (int j = 0; j < n/2; j++) {
			unite[i].push_back(b[i][j]);
		}
	}
	for (int i = (n / 2),i1=0; i1 < n/2; i1++,i++) {
		unite.push_back(std::vector<int>());
		for (int j = 0; j < n / 2; j++) {
			unite[i].push_back(c[i1][j]);
		}
	}
	for (int i = (n / 2),i1=0; i1 < n/2; i++,i1++) {
		for (int j = 0; j < n/2; j++) {
			unite[i].push_back(d[i1][j]);
		}
	}
	return unite;
}

//multiplicacion strassen
std::vector<std::vector<int>> strassen(std::vector<std::vector<int>> a, std::vector<std::vector<int>> b, int n) {
	if (n <= 2) {
		return Multi_array(a, b);
	}
	else {
		//partX[0] = X[1][1], partX[1]=X[1][2], partX[2]=X[2][1], partX[3]=X[2][2]
		std::vector<std::vector<std::vector<int>>> partsA = div4(a, n);
		std::vector<std::vector<std::vector<int>>> partsB = div4(b, n);
		std::vector<std::vector<int>> sum1, sum2, sum3, sum4;
		sum1=suma_vectores(strassen(partsA[0], partsB[0], n / 2), strassen(partsA[1], partsB[2], n / 2));
		sum2=suma_vectores(strassen(partsA[0], partsB[1], n / 2), strassen(partsA[1], partsB[3], n / 2));
		sum3=suma_vectores(strassen(partsA[2], partsB[0], n / 2), strassen(partsA[3], partsB[2], n / 2));
		sum4=suma_vectores(strassen(partsA[2], partsB[1], n / 2), strassen(partsA[3], partsB[3], n / 2));
		return unite4(sum1, sum2, sum3, sum4, n);
	}
}

//se asegura de que las matrices sean potencia de 2
std::vector<std::vector<int>> strassen_ini(std::vector<std::vector<int>> a, std::vector<std::vector<int>> b) {
	int na = a.size() * a[0].size(), nb = b.size() * b[0].size(), max=0, max1=0, filA=a.size(), colB=b[0].size();
	std::vector<std::vector<int>> array1, array2, res;
	if (na > nb) {
		max = a.size();
		max1 = a[0].size();
	}
	else {
		max = b.size();
		max1 = b[0].size();
	}
	int i1 = 0,n=0;
	while (potencia_cuadrada(i1) < max || potencia_cuadrada(i1) < max1 ) {
		i1++;
	}
	n=potencia_cuadrada(i1);
	array1=fillwith0(n, a);
	array2=fillwith0(n, b);
	res=strassen(array1, array2, n);
	takeout0(res,filA,colB);
	return res;
}

//main-------------------------------------------------------
int main()
{
	std::vector<std::vector<std::vector<int>>> T;
	std::vector<std::vector<int>>array1, array2, array3,array4;
	randgen(6, 5, array1);
	srand(time(0));
	randgen(5,3, array2);
	print(array1);
	print(array2);
	std::cout << "\n MULTIPLICACION ESTANDAR \n";
	array3 = Multi_array(array1, array2);
	print(array3);
	std::cout << "\n MULTIPLICACION STRASSEN \n";
	array4 = strassen_ini(array1, array2);
	print(array4);
	//generate(array4);
	/*T=read();
	array1=Multi_array(T[0], T[1]);
	array2 = strassen_ini(T[2], T[3]);
	print(array1);
	print(array2);*/
}
