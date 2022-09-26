#include <iostream>
#include <string>

using namespace std;
int main() {
    int t, gen1, gen2;
    string m1, m2;
    cin >> t;
    for (int i = 0; i < t; i++){
        cin >> m1 >> m2;
        cout << m1 << endl << m2 << endl;
        gen1 = gen(m1);
        gen2 = gen(m2);
        m1 = m1.substr(0,2) + m1.substr(3,2) + m1.substr(6,2);
        cout << m1 << endl;
        m2 = m2.substr(0,2) + m2.substr(3,2) + m2.substr(6,2);
        cout << m2 << endl;
    }

    return 0;
}


