/*
 * Buzera Tiberiu 323 CA
 */
#include <bits/stdc++.h>

using namespace std;

/*
 * funtie ce returneaza numarul minim de poduri ce trebuie parcurse folosind
 * o coada in care avem in permanenta nodurile carora urmeaza sa le fie testati
 * vecinii care nu au fost deja testati
 */

int poduri(int n, int m, pair<int, int> poz,
           vector<vector<pair < char, int >>> &matrix) {
    int min = 1000000;
    queue<pair<int, int>> queue;
    queue.push(poz);
    matrix[poz.first][poz.second].second = 1;
    while (!queue.empty()) {
        int s = queue.size();
        pair<int, int> poz_tmp;
        for (int i = 0; i < s; i++) {
            poz_tmp = queue.front();
            queue.pop();
            /*
             * in cazul in care nodul este la margine verificam daca are costul
             * mai mic decat min
             */
            if (matrix[poz_tmp.first][poz_tmp.second].first == 'V' &&
               (poz_tmp.first == 0 || poz_tmp.first == n - 1) &&
               matrix[poz_tmp.first][poz_tmp.second].second < min) {
                            min = matrix[poz_tmp.first][poz_tmp.second].second;
            }
            if (matrix[poz_tmp.first][poz_tmp.second].first == 'O' &&
               (poz_tmp.second == 0 || poz_tmp.second == m-1) &&
               matrix[poz_tmp.first][poz_tmp.second].second < min) {
                            min = matrix[poz_tmp.first][poz_tmp.second].second;
            }
            if (matrix[poz_tmp.first][poz_tmp.second].first == 'D' &&
              (poz_tmp.second == 0 || poz_tmp.second == m-1 ||
              poz_tmp.first == 0 || poz_tmp.first == n-1) &&
              matrix[poz_tmp.first][poz_tmp.second].second < min) {
                            min = matrix[poz_tmp.first][poz_tmp.second].second;
            }
            /*
             * verificam daca nodul actual este vertical pt a lua doar vecinii
             * de sus si de jos
             */
            if (matrix[poz_tmp.first][poz_tmp.second].first == 'V') {
                if (poz_tmp.first-1 >= 0 &&
                    matrix[poz_tmp.first-1][poz_tmp.second].second == 0 &&
                    matrix[poz_tmp.first-1][poz_tmp.second].first != '.') {
                    queue.push(make_pair(poz_tmp.first-1, poz_tmp.second));
                    matrix[poz_tmp.first-1][poz_tmp.second].second =
                            matrix[poz_tmp.first][poz_tmp.second].second + 1;
                }
                if (poz_tmp.first+1 <= n-1 &&
                    matrix[poz_tmp.first+1][poz_tmp.second].second == 0 &&
                    matrix[poz_tmp.first+1][poz_tmp.second].first != '.') {
                    queue.push(make_pair(poz_tmp.first+1, poz_tmp.second));
                    matrix[poz_tmp.first+1][poz_tmp.second].second =
                            matrix[poz_tmp.first][poz_tmp.second].second + 1;
                }
                /*
                 * verif daca nodul actual este pod orizontal caz in care luam
                 * doar vecinii din stanga si dreapta
                 */
            } else if (matrix[poz_tmp.first][poz_tmp.second].first == 'O') {
                if (poz_tmp.second-1 >= 0 &&
                    matrix[poz_tmp.first][poz_tmp.second-1].second == 0 &&
                    poz_tmp.second-1 >= 0 &&
                    matrix[poz_tmp.first][poz_tmp.second-1].first != '.') {
                    queue.push(make_pair(poz_tmp.first, poz_tmp.second-1));
                    matrix[poz_tmp.first][poz_tmp.second-1].second =
                            matrix[poz_tmp.first][poz_tmp.second].second + 1;
                }
                if (poz_tmp.second+1 <= m-1 &&
                    matrix[poz_tmp.first][poz_tmp.second+1].second == 0 &&
                    matrix[poz_tmp.first][poz_tmp.second+1].first != '.') {
                    queue.push(make_pair(poz_tmp.first, poz_tmp.second+1));
                    matrix[poz_tmp.first][poz_tmp.second+1].second =
                            matrix[poz_tmp.first][poz_tmp.second].second + 1;
                }
                /*
                 * verif daca nodul actual este dublu caz in care luam toti cei
                 * 4 vecini
                 */
            } else if (matrix[poz_tmp.first][poz_tmp.second].first == 'D') {
                if (poz_tmp.first-1 >= 0 &&
                matrix[poz_tmp.first-1][poz_tmp.second].second == 0 &&
                matrix[poz_tmp.first-1][poz_tmp.second].first != '.') {
                    queue.push(make_pair(poz_tmp.first-1, poz_tmp.second));
                    matrix[poz_tmp.first-1][poz_tmp.second].second =
                            matrix[poz_tmp.first][poz_tmp.second].second + 1;
                }
                if (poz_tmp.first+1 <= n-1 &&
                matrix[poz_tmp.first+1][poz_tmp.second].second == 0 &&
                matrix[poz_tmp.first+1][poz_tmp.second].first != '.') {
                    queue.push(make_pair(poz_tmp.first+1, poz_tmp.second));
                    matrix[poz_tmp.first+1][poz_tmp.second].second =
                            matrix[poz_tmp.first][poz_tmp.second].second + 1;
                }
                if (poz_tmp.second-1 >= 0 &&
                matrix[poz_tmp.first][poz_tmp.second-1].second == 0 &&
                matrix[poz_tmp.first][poz_tmp.second-1].first != '.') {
                    queue.push(make_pair(poz_tmp.first, poz_tmp.second-1));
                    matrix[poz_tmp.first][poz_tmp.second-1].second =
                            matrix[poz_tmp.first][poz_tmp.second].second + 1;
                }
                if (poz_tmp.second+1 <= m-1 &&
                matrix[poz_tmp.first][poz_tmp.second+1].second == 0 &&
                matrix[poz_tmp.first][poz_tmp.second+1].first != '.') {
                    queue.push(make_pair(poz_tmp.first, poz_tmp.second+1));
                    matrix[poz_tmp.first][poz_tmp.second+1].second =
                            matrix[poz_tmp.first][poz_tmp.second].second + 1;
                }
            }
        }
    }
    /*
     * verificam daca min s-a schimbat sau nu
     * daca nu este schimbat returnam -1 altfel returnam min
     */
    if (min == 1000000) {
        return -1;
    }
    return min;
}

int main() {
    /*
     * Se citesc datele de intrare sub forma unei matrici in care fiecare
     * element contine un char care reprezinta un pod sau un gol si un
     * cost care reprezinta distanta de la nodul initial
     */
    ifstream in("poduri.in");
    int n, m, e1, e2;
    pair<int, int> poz;
    vector<vector<pair <char, int>>>
            matrix(2050, vector< pair < char, int > >(2050));
    in >> n >> m;
    in >> e1 >> e2;
    poz = make_pair(e1 - 1, e2 - 1);
    for (int i = 0 ; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char c;
            in >> c;
            if (c == 'V') {
                matrix[i][j] = make_pair('V', 0);
            } else if (c == 'O') {
                matrix[i][j] = make_pair('O', 0);
            } else if (c == '.') {
                matrix[i][j] = make_pair('.', 0);
            } else {
                matrix[i][j] = make_pair('D', 0);
            }
        }
    }
    in.close();

    ofstream out("poduri.out");
    out << poduri(n, m, poz, matrix);
    out.close();
    return 0;
}
