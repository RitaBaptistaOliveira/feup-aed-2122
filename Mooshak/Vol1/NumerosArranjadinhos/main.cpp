#include <iostream>
#include <cmath>

using namespace std;
int main() {
    long long int n, k, a, b;
    int t, soma;
    //cout << "t?";
    cin >> t;
    for (int i = 0; i < t; i++){
        //cout << "n?";
        cin >> n;
        //cout << "k?";
        cin >> k;
        do{
            n++;
            a = n;
            for (soma = 0; a > 0; soma += a % 10, a /= 10);
        } while (soma != k);
        cout << n << endl;
    }
    return 0;
}
