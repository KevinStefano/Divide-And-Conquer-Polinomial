//Nama : Kevin Austin Stefano
//NIM  : 13518104

#ifndef BRUTEFORCE_H
#define BRUTEFORCE_H

#include "Polinom.h"
#include <iostream>

using namespace std;

polinom KaliBruteForce (polinom pol1,polinom pol) {
    polinom poltotal(pol1.cap+pol.cap);
    poltotal.ResetPolinom();
    for (int i =0;i<=pol1.cap;i++) {
        for (int j=0;j<=pol.cap;j++) {
            poltotal.data[i+j]=poltotal.data[i+j]+(pol1.data[i]*pol.data[j]);
        }
    }
    return poltotal;
}

#endif
