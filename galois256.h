
#ifndef SHAMIR_GALOIS256_H
#define SHAMIR_GALOIS256_H
#include <cstdint>
#include <random>
class Galois256{
private:
    uint8_t ele;
    static uint8_t inverse[256];
    uint8_t mul(uint8_t val1, uint8_t val2);
public:
    explicit Galois256(uint8_t init_val);
    explicit Galois256();
    Galois256 operator+(Galois256 &b);
    Galois256 operator*(Galois256 &b);
    bool operator==(Galois256 &b);
    [[nodiscard]] uint8_t getElement() const;
    Galois256 inv();
    static Galois256 randGen();
};
#endif
