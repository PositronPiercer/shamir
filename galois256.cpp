#include "galois256.h"

uint8_t Galois256::inverse[256];
Galois256::Galois256(uint8_t init_val){
    ele = init_val;
}
Galois256::Galois256() {}
uint8_t Galois256::getElement() const{
    return ele;
}
Galois256 Galois256::operator+(Galois256 &b){
    Galois256 sum(ele ^ b.getElement());
    return sum;
}
Galois256 Galois256::operator*(Galois256 &b){
    uint8_t val2 = b.getElement();
    uint8_t val1 = ele;
    uint8_t res = mul(val1, val2);
    return Galois256(res);

}
bool Galois256::operator==(Galois256 &b){
    return (ele == b.getElement());
}
uint8_t Galois256::mul(uint8_t val1, uint8_t val2){
    uint8_t p = 0;
    while (val1 && val2) {
        if (val2 & 1)
            p ^= val1;

        if (val1 & 0x80)
            val1 = (val1 << 1) ^ 0x11b;
        else
            val1 <<= 1;
        val2 >>= 1;

    }
    return p;
}

Galois256 Galois256::inv(){
    if (ele == 0){
        //inverse doesn't exist
        throw "inverse_of_zero";
    }
    //if inverse has been already calculated return
    if (inverse[ele]){
        return Galois256(inverse[ele]);
    }
    else{
        //calculate inverse
        for(uint8_t start = 0x00; start <= 0xff; start++){
            if (mul(ele, start) == 1){
                inverse[ele] = start;
                return Galois256(start);
            }
        }
    }
    throw "inverse_does_not_exist";
}
Galois256 Galois256::randGen(){
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> distrib(0, 255);

    uint8_t ran_num = distrib(gen);
    return Galois256(ran_num);
}