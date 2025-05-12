/*
John loves apples and is determined to harvest them from his neighbor's garden. However, there's a time constraint- John must complete his apple-gathering mission before the neighbor returns, which will be after H hours.

There are n apple trees in the garden, each with a different yield of apples denoted by apples[i] John can pick m apples per hour if a tree has fewer than m apples, John will move on to the next tree.

Your task is to determine the smallest value of m that allows John to gather as many apples as possible under the given conditions without alerting the neighbor.
for eg
apples = 30, 22, 13, 4, 9 hours = 9 If we take m=7,
For apples[0]=30, we can gather (30/7)= 4 hours (28 apples taken).
For apples[1]=22, we can gather (22/7)- 3 hours (21 apples taken).
For apples[2]=13, we can gather (13/7)=1 hour (7 apples taken).
For apples[3]=4, we can't gather any apples from this tree since (4/7)=0, so we will skip this tree
For apples[4]=9, we can gather (9/7)=1 hour (7 apples taken).
So, within the allocated 9 hours, John managed to gather a maximum of 63 apples.
Hence, the smallest value of m that allows John to gather as many apples as possible is 7.
1 <= n <= 10^4
1 <= apples[i] <= 10^8
1 <= H <= 10^8

*/

#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// Compute how many "full hours" John can work at rate m
ll full_hours(const vector<ll>& apples, ll m) {
    ll sum = 0;
    for (ll a : apples) {
        sum += a / m;
    }
    return sum;
}

int main() {
    int n;
    ll H;
    // Input: n (number of trees) and H (available hours)
    cin >> n >> H;

    vector<ll> apples(n);
    ll maxA = 0;
    for (int i = 0; i < n; i++) {
        cin >> apples[i];
        maxA = max(maxA, apples[i]);
    }

    // Binary search for the largest m in [1, maxA]
    // such that full_hours(m) >= H
    ll s = 1, e = maxA, best = 0;
    while (s <= e) {
        ll mid = s + (e - s) / 2;
        if (full_hours(apples, mid) >= H) {
            best = mid;      // mid is feasible, try higher
            s = mid + 1;
        } else {
            e = mid - 1;    // mid too large, not enough hours
        }
    }

    // If no rate m>=1 ever satisfies full_hours(m)>=H,
    // best stays 0, so John picks at rate=1
    if (best == 0) best = 1;

    cout << best << "\n";
    return 0;
}
