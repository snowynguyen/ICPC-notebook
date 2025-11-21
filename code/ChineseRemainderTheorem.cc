// Official version: https://cp-algorithms.com/math/chinese-remainder-theorem.html

#define ll long long
struct Congruence {
    ll a, m;
};

// CRT = Chinese Remainder Theorem
ll CRT(vector<Congruence> const& congruences) {
    long long M = 1;
    for (auto const& congruence : congruences) {
        M *= congruence.m;
    }

    long long solution = 0;
    for (auto const& congruence : congruences) {
        long long a_i = congruence.a;
        long long M_i = M / congruence.m;
        long long N_i = mod_inv(M_i, congruence.m);
        solution = (solution + a_i * M_i % M * N_i) % M;
    }
    return solution;
}
// CRT({{2,3},{3,5},{2,7}}) = 23 mod 105
// CRT({{3,4},{5,6}}) = 11 mod 12