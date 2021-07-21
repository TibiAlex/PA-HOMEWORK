/*
 * Buzera Tiberiu 323 CA
 */
#include <bits/stdc++.h>

using namespace std;

//  generam toate sumele posibile cu domeniul respectiv
void printSubArrays(vector<int> arr, int index,
                    int t, set<int> &sumes, vector<int> subarr) {
    if (index == arr.size()) {
        int l = subarr.size();
        if (l != 0 && subarr.size() <= t) {
            int s = 0;
            for (int i = 0; i < subarr.size(); i++) {
                s += subarr[i];
            }
            sumes.insert(s);
        }
    } else {
        printSubArrays(arr, index + 1, t, sumes, subarr);
        subarr.push_back(arr[index]);
        printSubArrays(arr, index + 1, t, sumes, subarr);
    }
    return;
}

//  gasim cea mai lunga secventa consecutiva din set
int longest_cons(set<int> sumes) {
        vector<int> v;
        int d = 1, max = 0;
        for (auto x : sumes) {
               v.push_back(x);
        }
        for (int i = 1; i < v.size(); i++) {
            if (v[i]- v[i - 1] != 1) {
                if (max < d) {
                    max = d;
                }
                d = 0;
            } else {
                d++;
            }
        }
        if (max < d) {
            max = d;
        }
        return max;
}

// procesam toate combinatiile gasite pentru a forma
// seturi cu toate sumele posibile
void printSolution(vector<int> &solution, int t,
                   int &max, vector<int> &truesol) {
    vector<int> domain;
    for (auto s : solution) {
         for (int i = 0; i < t; i++) {
             domain.push_back(s);
         }
    }
    set<int> sumes;
    vector<int> b;
    printSubArrays(domain, 0, t, sumes, b);
    int d = longest_cons(sumes);

    if (max < d) {
        max = d;
        for (int i = 0; i < truesol.size(); i++) {
            truesol[i] = solution[i];
        }
    }
}

//  generam toate combinarile posibile cu numerele din domeniu
void back(int step, int stop, vector<int> &v, vector<int> &solution,
          int t, int &max, vector<int> &truesol)  {
    if (step == stop) {
        printSolution(solution, t, max, truesol);
        return;
    }
    for (int i = 0 ; i < v.size(); i++) {
        if (solution[step - 1] < i + 1 ||
        (solution[step - 1] == 1 && i + 1 != 1)) {
            solution[step] = i + 1;
            back(step + 1, stop, v, solution, t, max, truesol);
        }
    }
}

int main() {
    ifstream in("lego.in");
    int k, n, t, max = 0;
    in >> k >> n >> t;
    in.close();

    vector<int> domain(k), solution(n), truesol(n);
    for (int i = 0; i < k; i++) {
        domain[i] = i + 1;
    }

    back(0, n, domain, solution, t, max, truesol);

    ofstream out("lego.out");
    out << max << endl;
    for (int i = 0 ; i < truesol.size(); i++) {
        out << truesol[i] << " ";
    }
    out.close();

    return 0;
}
