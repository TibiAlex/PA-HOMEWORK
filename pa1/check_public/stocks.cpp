//
// Created by Buzera Tiberiu on 4/3/21.
//

#include <bits/stdc++.h>
using namespace std;

/*
 * functie ce returneaza maximul a 2 numere long long
 */
long long getmax(long long a, long long b) {
    if (a > b) {
        return a;
    }
    return b;
}

/*
 * fucntia rucsac are rolul de a calcula si returna profitul maxim
 * care se poate obtine din cele n actiuni, cu bugetul b, pierderea
 * maxima l si vertorii curr, min, max ce contin date despre
 * pretul actiunilor, scaderea si cresterea maxima.
 */
long long rucsac(long long n, long long b, long long l, vector<long long> curr,
                 vector<long long> min, vector<long long> max) {
    /*
     * dp este o matrice in 3 dimensiuni pentru a putea tine cont de cele 3
     * variabile in acelasi timp, sunt n actiuni, nu trebuie sa treaca peste
     * bugetul b si nu trebuie sa treaca peste pierderea l
     * marimea matricei este n + 1 pe b + 1 pe l + 1 pentru a putea procesa
     * cazul in care vectorii sunt vizi, bugetul sau pierderea sunt 0
    */
    vector< vector< vector<long long> > > dp(n + 1, vector< vector<long long> >
            (b + 1, vector<long long>(l + 1, -1)));
    /*
     * cazul de baza
     */
    dp[0][0][0] = 0;
    long long sol = 0;
    /*
     * cazul genereal
     * se parcurge matricea tridimensionala
     * incepand de la al 2 lea nivel al
     * paralelipipedului dreptunghic
     */
    for (long long i = 1; i <= n; ++i) {
        for (long long j = 0; j <= b; ++j) {
            for (long long k = 0; k <= l; ++k) {
                /*
                 * la fiecare pas punem initial rezultatul
                 * cu un nivel mai sus, pentru cazul in care
                 * nu folosim obiectul deoarece solutia este
                 * la pasul i - 1
                 */
                dp[i][j][k] = dp[i-1][j][k];
                /*
                 * daa folosim obiectul atunci rezervam o
                 * suma de bani in din buget si calculam
                 * pierderea de pana acum
                 */
                if (j - curr[i - 1] >= 0 &&
                    k - (curr[i - 1] - min[i - 1]) >= 0 &&
                    dp[i-1][j - curr[i - 1]]
                    [k - (curr[i - 1] - min[i - 1])] != -1) {
                    long long sol_aux =
                            dp[i-1][j - curr[i - 1]][k - curr[i - 1] +
                            min[i - 1]] + max[i - 1] - curr[i - 1];
                    dp[i][j][k] = getmax(dp[i][j][k], sol_aux);
                    sol = getmax(dp[i][j][k], sol);
                }
            }
        }
    }
    return sol;
}

int main() {
    /*
     * citim datele din fisierul de intrare stocks.in
     * n - numarul de actiuni
     * b - bugetul total
     * l - suma maxima pe care doreste sa o piarda
     * e1 - pretul curent al actiunii
     * e2 - pretul minim la care poate sa ajunga actiunea
     * e3 - pretul maxim la care poate sa ajunga actiunea
     */
    ifstream in("stocks.in");
    long long n, b, l;
    vector<long long> curr;
    vector<long long> min;
    vector<long long> max;
    in >> n >> b >> l;
    long long e1, e2, e3;
    for (long long i = 0; i < n; i++) {
        in >> e1 >> e2 >> e3;
        curr.push_back(e1);
        min.push_back(e2);
        max.push_back(e3);
    }
    /*
     * Scriem retultatul in fisierul stocks.out
     */
    ofstream out("stocks.out");
    out << rucsac(n, b, l, curr, min, max);
    in.close();
    out.close();
    return 0;
}
