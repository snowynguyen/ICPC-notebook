# This program prints all hcn (highly composite numbers) <= MAXN (=10**18)
# The value of MAXN can be changed arbitrarily. When MAXN = 10**100, the
# program needs less than one second to generate the list of hcn.
from math import log
MAXN = 10**18

# TODO: Generates a list of the first primes (with product > MAXN).
primes = gen_primes() # primes = [2, 3, 5, 7, 11, ...]

# Generates a list of the hcn <= MAXN.
def gen_hcn():
    # List of (number, number of divisors, exponents of the factorization)
	hcn = [(1, 1, [])]
	for i in range(len(primes)):
		new_hcn = []
		for el in hcn:
			new_hcn.append(el)
			if len(el[2]) < i: continue
			e_max = el[2][i-1] if i >= 1 else int(log(MAXN, 2))
			n = el[0]
			for e in range(1, e_max+1):
				n *= primes[i]
				if n > MAXN: break
				div = el[1] * (e+1)
				exponents = el[2] + [e]
				new_hcn.append((n, div, exponents))
		new_hcn.sort()
		hcn = [(1, 1, [])]
		for el in new_hcn:
			if el[1] > hcn[-1][1]: hcn.append(el)
	return hcn

# Biggest HCN smaller than 10^9, 10^12, 10^18, and their number of divisors:
# 735134400             1344        2^6*3^3*5^2*7*11*13*17
# 963761198400          6720        2^6*3^4*5^2*7*11*13*17*19*23
# 897612484786617600    103680      2^8*3^4*5^2*7^2*11*13*17*19*23*29*31*37