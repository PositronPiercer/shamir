#include "shamir.h"
#include "Point.h"
const Galois256 Shamir::x_coors[] = {Galois256(1), Galois256(2), Galois256(3), Galois256(4)};

Shamir::Shamir(std::vector<uint8_t> &secret_array){
    if (secret_array.size() != 32){
        throw "invalid_length_secret_array";
    }
    for (int i = 0; i < 32; i++){
        secrets[i] = Galois256(secret_array[i]);
    }
}

std::vector<std::vector<Galois256>> Shamir::createShares(){
    std::vector<std::vector<Galois256>> shares;

    //create 32 random slopes
    for (int i = 0; i < 32; i++){
        slopes[i] = Galois256::randGen();
    }

    for (int i = 0; i < 4; i++){
        std::vector<Galois256> share;
        Galois256 x_coor = x_coors[i];
        for (int j = 0; j < 32; j++){
            //create y coordinates for all 32 secrets corresponding to current x coordinate
            Galois256 y = slopes[j] * x_coor + secrets[j]; // y = mx + c
            share.push_back(y);
        }
        shares.push_back(share);
    }
    return shares;
}
std::vector<Galois256> Shamir::createSecret(std::vector<std::vector<Galois256>> shares){
    if (shares.size() < 2){
        throw "insufficient_number_of_shares";
    }
    std::vector<Galois256> sec;
    for (int i = 0; i < 32; i++){
        Point p1(x_coors[0], shares[0][i]);
        Point p2(x_coors[1], shares[1][i]);

        Galois256 slope_num = (p2.y + p1.y);
        Galois256 slope_dem_inv = (p2.x + p1.x).inv();

        Galois256 slope = slope_num * slope_dem_inv;

        Galois256 secret_t = (slope * p1.x);
        Galois256 secret = p1.y + secret_t;
        sec.push_back(secret);
    }
    return sec;
}
bool Shamir::verifyShares(std::vector<std::vector<Galois256>> shares){
    std::vector<Galois256> generated_secret = createSecret(shares);
    for (int i = 0; i < 32; i++){
        if (secrets[i] != generated_secret[i]){
            return false;
        }
    }
    return true;
}