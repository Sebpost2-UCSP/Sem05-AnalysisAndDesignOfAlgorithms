#include <iostream>
#include <vector>

using std::vector;
using std::cout;
using std::endl;

struct BC {
    int n = 0, new_num = 0,size=0, it=0;
    int* res;
    int* numeros;

    BC(int n, int* numeros, int numeros_size) {
        this->n = n;
        this->res = new int[n+2];
        for (int i = 0; i < n; i++)
            res[i] = 0;
        this->size = numeros_size;
        this->numeros = new int[size];
        for (int i = 0; i < size; i++) {
            this->numeros[i] = numeros[i];
        }
    }

    void suma(int new_num) {
        it++;
        if (new_num < n) {
            for (int i = 0; i < size; i++) {
                if (new_num + numeros[i] <= n) {
                    res[it] = numeros[i];
                    suma(new_num + numeros[i]);
                }
            }
        }
        else if (new_num == n) {
            res[it] = new_num;
            for (int i = 1; i < it; i++) {
                if (i + 1 == it)
                    cout << res[i];
                else
                    cout <<res[i]<< " + ";
            }
            cout << endl;
            it--;
            res[it] = 0;
            return;
        }
        else {
            it--;
            res[it] = 0;
            return;
        }
        it--;
    }

    ~BC() {
        delete[] res;
        delete[] numeros;
    }
};

int main()
{
    int numeros[3] = { 4,3,1 };
    BC test(7, numeros, 3);
    test.suma(0);
}
