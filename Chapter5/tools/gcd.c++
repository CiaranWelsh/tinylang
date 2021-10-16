//
// Created by Ciaran on 13/10/2021.
//
//unsigned gcd(unsigned a, unsigned b) {
//    if (b == 0)
//        return a;
//    while (b != 0) {
//        unsigned t = a % b;
//        a = b;
//        b = t;
//    }
//    return a;
//}

//void f(){
//    int a = 6;
//    int b = 4;
//    bool truth = a == b;
//    while (!truth){
//        b++;
//        truth = a == b;
//    }
//    int c = 5;
//}
int f(){
    int a = 6;
    int b = 20;
    while (a < b){
        a++;
        b += a;
    }
    return b;
}