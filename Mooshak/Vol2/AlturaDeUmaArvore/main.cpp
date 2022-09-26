#include <iostream>
#include <vector>

int findProfundidade();

using namespace std;

struct No{
    int valor;
    int filho1 = 0;
    int filho2 = 0;
};

int main() {
    int numArvores;
    cin >> numArvores;
    for(int i = 0; i < numArvores; i++) {
        int numNos;
        cin >> numNos;
        vector <int> pais;
        for (int j = 0; j < numNos - 1; j++) {
            int pai;
            cin >> pai;
            pais.push_back(pai);
        }
        int profundidade = findProfundidade()
    }
}

int findProfundidade(vector <int> pais) {
    vector <No> nos;
    No root;
    root.valor = 1;
    nos.push_back(root);
    for(int i = 0; i < pais.size(); i++){
        for(auto & no : nos){
            if(no.valor == pais.at(i)){
                no.filho2 = i+2;
            }
        }
        No no;
        no.valor = pais.at(i);
        no.filho1 = i+2;
        nos.push_back(no)
    }
}

int altura(No no){

}



