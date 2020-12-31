

#ifndef SHAMIR_SHAMIR_H
#define SHAMIR_SHAMIR_H
#include "galois256.h"
#include <vector>

class Shamir {
private:
    Galois256 secrets[32];
    static const Galois256 x_coors[];
    Galois256 slopes[32];
public:
    Shamir(std::vector<uint8_t> &secret_array);
    std::vector<std::vector<Galois256>> createShares();
    std::vector<Galois256> createSecret(std::vector<std::vector<Galois256>> shares);
    bool verifyShares(std::vector<std::vector<Galois256>> shares);
};


#endif //SHAMIR_SHAMIR_H
