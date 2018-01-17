
#ifdef ssu1
#define _GLIBCXX_DEBUG
#endif
#undef NDEBUG

#include <algorithm>
#include <functional>
#include <numeric>
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <cassert>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <bitset>
#include <sstream>

using namespace std;

#define fore(i, l, r) for(int i = (l); i < (r); ++i)
#define forn(i, n) fore(i, 0, n)
#define fori(i, l, r) fore(i, l, (r) + 1)
#define sz(v) int((v).size())
#define all(v) (v).begin(), (v).end()
#define pb push_back
#define mp make_pair
#define X first
#define Y second

typedef long long li;
typedef long double ld;
typedef pair<int, int> pt;

template<typename T> T abs(T a) { return a < 0 ? -a : a; }
template<typename T> T sqr(T a) { return a*a; }

const int INF = (int)1e9;
const ld EPS = 1e-9;
const ld PI = 3.1415926535897932384626433832795;

/*

    This is just to check correctness of input

*/
int readInt(int l, int r){
    int x;
    if(scanf("%d", &x) != 1){
        fprintf(stderr, "Expected int in range [%d, %d], but haven't found!", l, r);
        throw;
    }
    if(!(l <= x && x <= r)){
        fprintf(stderr, "Expected int in range [%d, %d], but found %d!", l, r, x);
        throw;
    }
    return x;
}
int readInt(int l, int r, string name){
    int x;
    if(scanf("%d", &x) != 1){
        fprintf(stderr, "Expected int %s in range [%d, %d], but haven't found!", name.c_str(), l, r);
        throw;
    }
    if(!(l <= x && x <= r)){
        fprintf(stderr, "Expected int %s in range [%d, %d], but found %d!", name.c_str(), l, r, x);
        throw;
    }
    return x;
}
li readLong(li l, li r){
    li x;
    if(scanf("%lld", &x) != 1){
        fprintf(stderr, "Expected long long in range [%lld, %lld], but haven't found!", l, r);
        throw;
    }
    if(!(l <= x && x <= r)){
        fprintf(stderr, "Expected long long in range [%lld, %lld], but found %lld!", l, r, x);
        throw;
    }
    return x;
}
li readLong(li l, li r, string name){
    li x;
    if(scanf("%lld", &x) != 1){
        fprintf(stderr, "Expected long long %s in range [%lld, %lld], but haven't found!", name.c_str(), l, r);
        throw;
    }
    if(!(l <= x && x <= r)){
        fprintf(stderr, "Expected long long %s in range [%lld, %lld], but found %lld!", name.c_str(), l, r, x);
        throw;
    }
    return x;
}
const ld __EPS__ = 1e-15;
ld readDouble(double l, double r){
    double x;
    if(scanf("%lf", &x) != 1){
        fprintf(stderr, "Expected double in range [%lf, %lf], but haven't found!", l, r);
        throw;
    }
    if(!(l <= x + __EPS__ && x <= r + __EPS__)){
        fprintf(stderr, "Expected double in range [%lf, %lf], but found %lf!", l, r, x);
        throw;
    }
    return x;
}
ld readDouble(double l, double r, string name){
    double x;
    if(scanf("%lf", &x) != 1){
        fprintf(stderr, "Expected double %s in range [%lf, %lf], but haven't found!", name.c_str(), l, r);
        throw;
    }
    if(!(l <= x + __EPS__ && x <= r + __EPS__)){
        fprintf(stderr, "Expected double %s in range [%lf, %lf], but found %lf!", name.c_str(), l, r, x);
        throw;
    }
    return x;
}

int main(){
#ifdef ssu1
    assert(freopen("input.txt", "rt", stdin));
    //assert(freopen("output.txt", "wt", stdout));
#endif
    char buf[2000];
    gets(buf);
    int szb = strlen(buf);

    assert(1 <= szb && szb <= 1000);

    set<char> s;
    forn(i, szb){
        if(!(isalpha(buf[i]) || buf[i] == ' ')){
            throw;
        }
        if(buf[i] != ' '){
            s.insert((char)tolower(buf[i]));
        }
    }

    puts(sz(s) == 26 ? "pangram" : "not pangram");
    return 0;
}
