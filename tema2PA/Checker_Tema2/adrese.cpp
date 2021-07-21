/*
 * Buzera Tiberiu 323 CA
 */
#include <bits/stdc++.h>

using namespace std;

//  functie ce sorteaza clientii dupa nr de email-uri
void sort_list(vector<pair<string, set<string>>> &result) {
    for (int i = 0; i < result.size() - 1; i++) {
        for (int j = i + 1; j < result.size(); j++) {
            if (result[i].second.size() > result[j].second.size()) {
                swap(result[i], result[j]);
            }
            if (result[i].second.size() == result[j].second.size() &&
                result[j].first.compare(result[i].first) < 0) {
                    swap(result[i], result[j]);
            }
        }
    }
}

//  functie dfs ce strabate clientii interconectati prin email-uri
void DFS(int v, map<int, bool> &visited, map<int, vector<int>> &adj,
         vector<pair<string, vector<string>>> &person, set<string> &set,
         string &name) {
    visited[v] = true;
    if (person[v].first.compare(name) < 0) {
        name = person[v].first;
    }
    for (int i = 0 ; i < person[v].second.size(); i++) {
        set.insert(person[v].second[i]);
    }
    for (int i = 0; i < adj[v].size(); i++) {
        if (!visited[adj[v][i]]) {
            DFS(adj[v][i], visited, adj, person, set, name);
        }
    }
}

int main() {
    ifstream in("adrese.in");
    int n, k;
    string name, m;
    in >> n;
    //  hashmap pt a verifica in O(0) daca exista deja un email
    unordered_map<string, int> mail_data;
    //  vectorul cu informatiile fiecarei persoane
    vector<pair<string, vector<string>>> person;
    //  lista adiacenta a grafului
    map<int, vector<int>> adj;


    for (int i = 0 ; i < n; i++) {
        vector<string> mail;
        in >> name >> k;
        for (int j = 0 ; j < k ; j++) {
            in >> m;
            //  verificam daca mail-ul exista deja in hashmap
            //  pentru a crea lista de adiacenta
            if (mail_data.find(m) != mail_data.end()) {
                  adj[mail_data[m]].push_back(person.size());
                  adj[person.size()].push_back(mail_data[m]);
            } else {
                mail_data.insert(make_pair(m, person.size()));
            }
            mail.push_back(m);
        }
        person.push_back(make_pair(name, mail));
    }

    in.close();

    ofstream out("adrese.out");

    //  vectorul care va avea clientii finali ordonati din cauza set-ului
    vector<pair<string, set<string>>> result;
    //  vector folosit la DFS pentru a tine evidenta nodurilor deja vizitate
    map<int, bool> visited;

    //  parcurgem fiecare nod si ii verificam toti vecinii
    for (int i = 0 ; i  < n; i++) {
        string name = person[i].first;
        if (!visited[i]) {
            set<string> set;
            DFS(i, visited, adj, person, set, name);
            result.push_back(make_pair(name, set));
        }
    }

    //  ordonam lista finala
    sort_list(result);

    //  afisam rezultatul in forma ceruta
    out << result.size() << endl;
    for (int i = 0 ; i < result.size(); i++) {
        out << result[i].first << " " << result[i].second.size() << endl;
        for (auto x : result[i].second) {
            out << x << endl;
        }
    }

    out.close();
    return 0;
}
