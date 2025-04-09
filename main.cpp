#include <iostream>
#include <vector>
#include <list>
#include <string>

using namespace std;

class HashTable {
private:
    int n;  // Número total de objetos esperados
    int m;  // Tamanho de cada tabela do segundo nível (n / 10)
    vector<vector<list<string>>*> primeiroNivel;

    // Função hash para o primeiro nível
    int h1(const string& chave) {
        int soma = 0;
        for (char c : chave) {
            soma += static_cast<int>(c);
        }
        return soma % 10;
    }

    // Função hash para o segundo nível
    int h2(const string& chave) {
        const int primo = 31;
        int hash = 0;
        for (char c : chave) {
            hash = (hash * primo + static_cast<int>(c)) % m;
        }
        return hash % m;
    }

public:
    HashTable(int totalObjetos) : n(totalObjetos), m(totalObjetos / 10) {
        for (int i = 0; i < 10; ++i) {
            vector<list<string>>* segundoNivel = new vector<list<string>>(m);
            primeiroNivel.push_back(segundoNivel);
        }
    }

    ~HashTable() {
        for (auto ptr : primeiroNivel) {
            delete ptr;
        }
    }

    void inserir(const string& chave, const string& objeto) {
        int indice1 = h1(chave);
        if (indice1 < 0 || indice1 >= 10) return;

        vector<list<string>>* tabelaSegundoNivel = primeiroNivel[indice1];
        int indice2 = h2(chave);

        if (indice2 < 0 || indice2 >= m) return;

        list<string>& lista = (*tabelaSegundoNivel)[indice2];

        for (const string& obj : lista) {
            if (obj == chave) return;
        }

        lista.push_back(objeto);
    }

    string recuperar(const string& chave) {
        int indice1 = h1(chave);
        if (indice1 < 0 || indice1 >= 10) return "";

        vector<list<string>>* tabelaSegundoNivel = primeiroNivel[indice1];
        int indice2 = h2(chave);

        if (indice2 < 0 || indice2 >= m) return "";

        list<string>& lista = (*tabelaSegundoNivel)[indice2];

        for (const string& obj : lista) {
            if (obj == chave) return obj;
        }

        return "";
    }
};

int main() {
    HashTable ht(100); // Exemplo com capacidade para 100 objetos

    ht.inserir("Marco", "Marco");
    ht.inserir("Julia", "Julia");
    ht.inserir("Antônio José", "Antônio José");

    cout << ht.recuperar("Marco") << endl;        // Saída: Marco
    cout << ht.recuperar("Julia") << endl;        // Saída: Julia
    cout << ht.recuperar("Antônio José") << endl; // Saída: Antônio José
    cout << ht.recuperar("Inexistente") << endl;  // Saída: (vazio)

    return 0;
}