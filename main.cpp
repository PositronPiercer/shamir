#include "Point.h"
#include <vector>
#include "shamir.h"
#include <cassert>
#include <iostream>
using namespace std;

int main(){
    int testCases = 10000;
    for (int i = 1; i <= testCases; i++){
            //genrate random 32 bytes of secret
            vector<uint8_t> test;
            for (int i = 0; i < 32; i++) {
                test.push_back(Galois256::randGen().getElement());
            }


            Shamir sham(test);

            //create 4 shares
            vector<vector<Galois256>> shares = sham.createShares();

            //verify shares
            assert(sham.verifyShares(shares));
    }
    cout << testCases << " test cases passed." << endl;
}