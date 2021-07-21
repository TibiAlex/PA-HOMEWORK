//
// Created by Buzera Tiberiu on 4/3/21.
//

#include <bits/stdc++.h>
using namespace std;

/*
 * functie ce calculeaza maximul intre 2 numere long long
 */
long long max_long(long long a, long long b) {
    if (a > b)
        return a;
    return b;
}

int main() {
    /*
     * citim din fisierul valley.in datele de intrare
     * n - numarul de elemente din vector
     * e - inaltimea unui varf din respectivul munte
     */
    ifstream in("valley.in");
    int n;
    in >> n;
    vector<int> v;
    int e;
    for (int i = 0; i < n; i++) {
        in >> e;
        v.push_back(e);
    }
    /*
     * calculam printr-o singura parcurgere
     * costurile excavarii pentru a obtine
     * un munte crescator, respectiv descrescator
     * apoi calculam rezultatul
     * trebuie luate in considerare si cazurile
     * cand minimul este la inceput sa la finalul
     * vectorului
     */
    int minim = v[0];
    int index = 0;
    vector<int> st;
    vector<long long> st_c;
    vector<int> dr;
    dr.reserve(1000001);
    vector<long long> dr_c;
    dr_c.reserve(1000001);
    st.push_back(v[0]);
    st_c.push_back(0);
    dr[n - 1] = v[n - 1];
    dr_c[n - 1] = 0;
    for (int i = 1; i < n; i++) {
        if (minim > v[i]) {
            minim = v[i];
            index = i;
        }
        if (v[i] < st[i - 1]) {
            st.push_back(v[i]);
        } else {
            st.push_back(st[i - 1]);
        }
        if (v[i] > st[i]) {
            st_c.push_back(st_c[i - 1] + v[i] - st[i]);
        } else {
            st_c.push_back(st_c[i - 1]);
        }
        if (v[n - i - 1] < dr[n - i]) {
            dr[n - i - 1] = v[n - i - 1];
        } else {
            dr[n - i - 1] = dr[n - i];
        }
        if (v[n - i - 1] > dr[n - i]) {
            dr_c[n - i - 1] = dr_c[n - i] + v[n - i - 1] - dr[n - i - 1];
        } else {
            dr_c[n - i - 1] = dr_c[n - i];
        }
    }
    if (index == 0 && minim == v[index]) {
        index++;
    }
    if (index == n - 1 && minim == v[index]) {
        index--;
    }
    long long rez = st_c[index - 1] + dr_c[index + 1] +
            max_long(st_c[index] - st_c[index - 1],
                     dr_c[index] - dr_c[index + 1]);
    /*
     * scriem rezultatul in fisierul valley.out
     */
    ofstream out("valley.out");
    out << rez;
    in.close();
    out.close();
}
