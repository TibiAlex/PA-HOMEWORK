//
// Created by Buzera Tiberiu on 4/3/21.
//

#include <bits/stdc++.h>
using namespace std;

/*
 * functie ce calculeza costul minim pentru a nu exista 2 varfuri
 * egale adiacente pe munte
 * n - numarul de varfuri
 * v - vectorul ce contine inaltimea varfului si costul pentru a fi excavat
 */
long long calculate_cost(int n, vector< pair <long long, long long> > &v) {
    // matrice care sa retina costurile partiale de pe parcurs
    vector<vector<long long> > dp(n + 1, vector<long long>(3));
    // cazul de baza
    dp[1][0] = 0;
    dp[1][1] = v[1].second;
    dp[1][2] = 2 * v[1].second;
    /*
     * cazul de baza
     * parcurgem vectorul si verificam daca este sau nu egal cu
     * valoarea precedenta si daca numarul de escavari necesare
     * nu este mai mare decat inaltimea crestei
     */
    long long minimum;
    for (int i = 2; i <= n; i++) {
        for (int j = 0; j < 3; j++) {
            minimum = LLONG_MAX;
            if (v[i].first - j != v[i - 1].first) {
                if (minimum > dp[i - 1][0]) {
                    minimum = dp[i - 1][0];
                }
            }
            if (v[i].first - 1 >= 0 && v[i].first - j != v[i - 1].first - 1) {
                if (minimum > dp[i - 1][1]) {
                    minimum = dp[i - 1][1];
                }
            }
            if (v[i].first - 2 >= 0 && v[i].first - j != v[i - 1].first - 2) {
                if (minimum > dp[i - 1][2]) {
                    minimum = dp[i - 1][2];
                }
            }
            dp[i][j] = j * v[i].second + minimum;
        }
    }
    /*
     * returnam costul minim dintre costurile finale
     * adica cele de pe ultima linie
     */
    minimum = dp[n][0];
    if (dp[n][1] < minimum) {
        minimum = dp[n][1];
    }
    if (dp[n][2] < minimum) {
        minimum = dp[n][2];
    }
    return minimum;
}

int main() {
    /*
     * citim datele de intrare din fisierul ridge.in
     */
    ifstream in("ridge.in");
    int n;
    in >> n;
    vector< pair <long long, long long> > v;
    v.emplace_back(0, 0);
    for (int i = 1; i <= n; i++) {
        long long e1, e2;
        in >> e1 >> e2;
        v.push_back(make_pair(e1, e2));
    }
    in.close();
    /*
     * scriem retultatul in fisierul ridge.out
     */
    ofstream out("ridge.out");
    out << calculate_cost(n, v);
    out.close();
}
