#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cstdbool>
#include <cstring>
#include <cmath>
#include <iostream>
#include <iterator>
#include <map>
#include <gmpxx.h>

void bsgs(const mpz_class &g, const mpz_class &p, const mpz_class &Q)
{
    int m = (int) ceil(sqrt(INT32_MAX));
    auto table = new std::map<mpz_class, int>();
    mpz_class t(1);

    for (int i = 0; i < m; i++) {
        table->insert(std::pair<mpz_class, int>(t, i));
        t *= g;
        t %= p;
    }

    mpz_class gi, factor;
    mpz_class e(Q);
    mpz_invert(gi.get_mpz_t(), g.get_mpz_t(), p.get_mpz_t());
    mpz_pow_ui(factor.get_mpz_t(), gi.get_mpz_t(), m);
    factor %= p;

    for (int i = 0; i < m; i++) {
        if (table->find(e) != table->end()) {
            // found
            int a = i * m + (int)table->at(e);
            printf("Solution found, a = %d\n", a);
            break;
        }
        e *= factor;
        e %= p;
    }
    delete table;
}

int main()
{
    // Programs solving the discrete logarithm problem.
    // Problem statement: find value a such that g^a mod p = q
    // a is 31 bit unsigned integer; g, p and q are specified in hex format like this:

    const char *g = "A4D1CBD5C3FD34126765A442EFB99905F8104DD258AC507FD6406CFF14266D31266FEA1E5C41564B777E690F5504F213160217B4B01B886A5E91547F9E2749F4D7FBD7D3B9A92EE1909D0D2263F80A76A6A24C087A091F531DBF0A0169B6A28AD662A4D18E73AFA32D779D5918D08BC8858F4DCEF97C2A24855E6EEB22B3B2E5";
    const char *p = "B10B8F96A080E01DDE92DE5EAE5D54EC52C99FBCFB06A3C69A6A9DCA52D23B616073E28675A23D189838EF1E2EE652C013ECB4AEA906112324975C3CD49B83BFACCBDD7D90C4BD7098488E9C219A73724EFFD6FAE5644738FAA31A4FF55BCCC0A151AF5F0DC8B4BD45BF37DF365C1A65E68CFDA76D4DA708DF1FB2BC2E4A4371";
    const char *q = "4FB7FC5543219711B7144FDA72E4A25DDCBC79DB02D51C742602FB3D0D40E04C46CD22EC33B43DBEB5C05217A9135904DD8B7915335C9337D6CF07464E6E4D762B2C8B3A2F84313D0014C74D4EFE1FB00147B3D8498A755D6E2E6729A13B0F086BFEAB83E37B6401FEA9884AC1E493D7F91A065CD25E22EE5A66433F8C308DED";

    mpz_class G(g, 16);
    mpz_class P(p, 16);
    mpz_class Q(q, 16);

    printf("\nSolving g^a mod p = q using Baby-step Giant-step algorithm\n");

    bsgs(G, P, Q);

    return 0;
}
