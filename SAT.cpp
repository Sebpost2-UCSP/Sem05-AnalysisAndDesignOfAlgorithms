#include <iostream>
#include <string>
#include <vector>
#include <bitset>


using std::string;
using std::vector;
using std::cout;
using std::endl;

// el char a esta en el vector b? 
bool InVector(char a, vector<char>b) {
    for (char i : b) {
        if (i == a)
            return 1;
    }
} 

struct bool_conjunto {
    vector<bool> booleanos;
    vector<char> incognitas;
    vector<bool> suma;
    bool pare=0;
    int count_pare = 0;
    string eq, original_eq;


    bool_conjunto(){}

    /*con esto consigo los arrays de booleanos y las variables
    tambien quito todos los espacios al string input*/
    bool_conjunto(string eq) {
        for (char i : eq)
            if (i != '(' && i != ')' && i != '+' && i != '-' && i != '*' && i != ' ' && !InVector(i, incognitas)) {
                booleanos.push_back(0);
                incognitas.push_back(i);
                this->eq+=i;
            }
            else if (i != ' ' && i!='+') {
                this->eq+=i;
            }
        original_eq = this->eq;
    }

    //imprime la ecuacion
    void print() {
        for (char c : eq)
            cout << c;
        cout << endl;
    }

    /*encuentra el parentesis menos accesible del array
    Si ya no hay parentesis devuelve -1*/
    int find_pare() {
        int count=-1, res=-1;
        for (char i : eq) {
            count++;
            if (i == '(') {
                res = count;
            }
        }
        return res;
    }

    /*Me devuelve la posicion de la incognita que estoy
    leyendo en el string por ejemplo: x=incognitas[0],
    entonces devuelve 0*/
    int incog_count(char a) {
        int count = 0;
        for (char i : incognitas) {
            if (i == a)
                break;
            count++;
        }
        return count;
    }

    //convertimos booleano a char
    char bool_to_char(bool a) {
        if (a)
            return '1';
        return '0';
    }

    //convierte char a bool
    bool char_to_bool(char a) {
        if (a == '0')
            return 0;
        return 1;
    }

    //suma los contenidos del vector suma
    bool suma_vector() {
        bool res = suma[0];
        for (int i = 1; i < suma.size(); i++) {
            res = (res || suma[i]);
        }
        return res;
    }

    //hace la negacion
    char negacion(char a) {
        if (a=='1')
            return '0';
        return '1';
    }

    /*Le da valores a las incognitas de la ecuacion*/
    void eq_value() {
        string new_eq;
        for (char i : eq) {
            if (i != '(' && i != ')' && i != '+' && i != '-' && i != '*' && i != ' ') {
                new_eq += bool_to_char(booleanos[incog_count(i)]);
            }
            else {
                new_eq += i;
            }
        }
        eq = new_eq;
    }

    //resolver la operacion
    bool resolver() {
        int it = 0, count=0;
        char it1 = '0', it2 = '0';
        string eq2, temp;

        //ponemos los valores booleanos en la ecuacion
        eq_value();
        print();

        /*Luego, resolvemos las negaciones*/
        for (int i = 0; i < eq.size();i++) {
            //negacion a un parentesis
            if (eq[i] == '-' && eq[i+1] == '(') {
                i++;
                eq2 += eq[i];
                i++;
                while (eq[i] != ')' || count != 0) {
                    if (eq[i] == '(') {
                        eq2 += eq[i];
                        count++;
                    }
                    else if (eq[i] == ')') {
                        eq2 += eq[i];
                        count--;
                    }
                    else if (eq[i] == '-') {
                        i++;
                        eq2 += eq[i];
                    }
                    else {
                        eq2 += negacion(eq[i]);
                    }
                    i++;
                }
                eq2 += ')';
            }
            //negacion a una variable
            else if (eq[i] == '-') {
                i++;
                eq2 += negacion(eq[i]);
            }
            else
                eq2 += eq[i];
        }
        eq = eq2;
        eq2.clear();
        print();
    
        /*Luego resolvemos los parentesis*/
        while (find_pare() != -1) {
            for (int i = 0; i < eq.size(); i++) {
                if (i == find_pare()) {
                    i++;
                    while (eq[i] != ')') {
                        suma.push_back(char_to_bool(eq[i]));
                        i++;
                    }
                    eq2 += bool_to_char(suma_vector());
                }
                else {
                    eq2 += eq[i];
                }
            }
            eq = eq2;
            eq2.clear();
            print();
        }

        /*luego la multiplicacion*/
        cout << (char_to_bool(eq[0]) && char_to_bool(eq[2]));
        cout << endl << endl;
        return (char_to_bool(eq[0]) && char_to_bool(eq[2]));
    }
};

int main()
{
    bool_conjunto eq1("((x-y+z)+ z + y) * (x+z)");
    bool solucion = 0;

    //usa bits para conseguir todas las posibles combinaciones de los booleanos
    for (int i = 0; i < (eq1.booleanos.size() * eq1.booleanos.size()) - 1; i++) {
        //EL BITSET NO ES DINAMICO (cambiar manualmente)-----------------------
        std::bitset<3> bits(i);
        for (int j = 0; j < eq1.booleanos.size(); j++) {
            eq1.booleanos[j] = bits[j];
        }
        if (eq1.resolver()) {
            solucion = 1;
            break;
        }
        eq1.eq = eq1.original_eq;
    }
    if (solucion)
        cout << "\n\nSi existe una solucion\n\n" << endl;
    else
        cout << "\n\nNo hay solucion\n\n" << endl;
}
