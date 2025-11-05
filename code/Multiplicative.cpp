const int MN = 1e6 + 11;
int sieve[MN]; 
pair<int,int> pk[MN];  // If i has the form of p^k, pk[i] = {p, k}. Otherwise, pk[i] = {-1, 0}
int ndiv[MN];          // ndiv[i] = Number of divisors of i.
int main() {
    // Sieve of Eratosthenes
    for (int i = 2; i <= 1000; i++)  // Non-prime numbers have at least 1 divisor <= 10^3.
        if (!sieve[i]) {
            for (int j = i*i; j <= 1000000; j += i)
                sieve[j] = i;
        }
    ndiv[1] = 1;
    for (int i = 2; i <= 1000000; i++) {
        if (!sieve[i]) {
            // i is a prime number.
            pk[i] = make_pair(i, 1);
            ndiv[i] = 2;
        }
        else {
            int p = sieve[i];  // p is any divisor of i.
            if (pk[i/p].first == p) {  // i = p^k
                pk[i] = make_pair(p, pk[i/p].second + 1);
                ndiv[i] = pk[i].second + 1;  // ndiv[p^k] = k+1.
            }
            else {
                pk[i] = make_pair(-1, 0);
                // Factor i = u*v, with gcd(u, v) = 1.
                int u = i, v = 1;
                while (u % p == 0) {
                    u /= p;
                    v = v * p;
                }
                ndiv[i] = ndiv[u] * ndiv[v];
            }
        }
    }
}