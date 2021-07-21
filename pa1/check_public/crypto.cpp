//
// Created by Buzera Tiberiu on 4/3/21.
//

#include <bits/stdc++.h>
using namespace std;

int main() {
    /*
     * citim datele din fisierul crypto.in
     * n - numarul de calculatoare
     * b - bugetul pentru update-ul procesoarelor
     * e1 - numarul de monede pe care poate un calculator sa le proceseze
     * intr-o ora
     * e2 - banii necesari pt un update
     */
    ifstream in("crypto.in");
    int n, b;
    vector< pair <int, int > > v;
    in >> n >> b;
    for (int i = 0; i < n; i++) {
        int e1, e2;
        in >> e1 >> e2;
        v.push_back(make_pair(e1, e2));
    }
    /*
     * sortam vectorul crescator in functie de numarul de criptomonede pe ora
     */
    sort(v.begin(), v.end());
    int s = 0, spartial = 0, index = 0, min = v[0].first;
    /*
     * cat timp s este mai mic decat bugetul total
     * updatam toate calculatoarele cu nivelul cel mai mic
     * retinem o suma partiala, apoi o adaugam la suma totala
     * dupa care parcurgem calculatoarele din punctul in care am
     * ramas
     * la final scadem 1 din min si il trimitem spre a fi scris
     * in fisier
     */
    while (s < b) {
        int i;
        for (i = index; i < n; i++) {
            if (min < v[i].first) {
                break;
            } else {
                spartial+=v[i].second;
            }
        }
        s += spartial;
        index = i;
        min++;
        while (v[index].first - min >= 2 && s <= b) {
            s+=spartial;
            min++;
        }
    }
    min--;
    /*
     * Scriem rezuktatul in fisierul crypto.out
     */
    ofstream out("crypto.out");
    out << min;
    in.close();
    out.close();
    return 0;
}
