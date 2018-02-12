#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <functional>
#include <algorithm>
#include <bitset>
#include <math.h>

#define INF 2000000000

using namespace std;

typedef pair<int, int> ii;

int n, m;

int gcd(int a, int b){
    if(a < b){
        int temp = a;
        a = b;
        b = temp;
    }
    return (b == 0) ? a : gcd(b, a%b);
}

void findSegments(vector<int>& sgs, vector<int>& st, int l, int r, int rl, int rr, int cur){
    if(l == rl && r == rr){
        sgs.push_back(cur);
        return;
    }
    int middle = (rl + rr) / 2;
    if(r <= middle){
        findSegments(sgs, st, l, r, rl, middle, 2 * cur);
    }
    else if(l > middle){
        findSegments(sgs, st, l, r, middle + 1, rr, 2 * cur + 1);
    }
    else{
        findSegments(sgs, st, l, middle, rl, middle, 2 * cur);
        findSegments(sgs, st, middle + 1, r, middle + 1, rr, 2 * cur + 1);
    }
}

bool validate(vector<int>& st, int mySegment, int x){
    int i = mySegment;
    while(i < m){
        if(st[2*i] % x == 0){
            i = 2*i + 1;
        }
        else if(st[2*i + 1] % x == 0){
            i = 2*i;
        }
        else{
            return false;
        }
    }
    return true;
}

bool query(vector<int>& st, int l, int r, int x){
    vector<int> segments;
    findSegments(segments, st, l, r, 1, m, 1);

    int S = segments.size();
    int i;
    int badSegments = 0;
    int mySegment;
    for(i = 0; i < S; i++){
        if(st[segments[i]] % x != 0){
            mySegment = segments[i];
            badSegments++;
        }
    }

    if(badSegments == 0) return true;
    if(badSegments > 1) return false;
    /// Now let's work with my segment, let's break it down
    return validate(st, mySegment, x);
}

int padding(int n){
    int i = 1;
    while(i < n){
        i <<= 1;
    }
    return i;
}

int main(){
    int i;
    scanf("%d", &n);
    m = padding(n);
    vector<int> st(2*m, 1);
    for(i = m; i < m + n - 1; i++){
        scanf("%d ", &st[i]);
    }
    scanf("%d", &st[m + n - 1]);
    for(i = m - 1; i >= 1; i--){
        st[i] = gcd(st[i*2], st[i*2 + 1]);
    }
    /// Segment Tree ready - CHECK
    int Q;
    int q_type, l, r, x;
    scanf("%d", &Q);
    for(i = 0; i < Q; i++){
        scanf("%d %d %d", &q_type, &l, &r);
        //cin >> q_type >> l >> r;
        if(q_type == 1){
            scanf(" %d", &x);
            //cin >> x;
            bool ans = query(st, l, r, x);
            if(ans){
                printf("YES\n");
            }
            else{
                printf("NO\n");
            }
        }
        else{
            /// Update the segment tree - CHECK
            int index = l + m - 1;
            st[index] = r;
            index /= 2;
            while(index){
                st[index] = gcd(st[index*2], st[index*2 + 1]);
                index /= 2;
            }
        }
    }
    return 0;
}