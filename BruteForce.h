//Nama : Kevin Austin Stefano
//NIM  : 13518104

#ifndef BRUTEFORCE_H
#define BRUTEFORCE_H

#include "Polinom.h"
#include <iostream>

using namespace std;

polinom KaliBruteForce (polinom pol1,polinom pol, int *tambah, int *kali) {
    polinom poltotal(pol1.cap+pol.cap);
    poltotal.ResetPolinom();
    for (int i =0;i<=pol1.cap;i++) {
        for (int j=0;j<=pol.cap;j++) {
            poltotal.data[i+j]=poltotal.data[i+j]+(pol1.data[i]*pol.data[j]);
        }
    }
    int captot = (pol1.cap+1);
    *kali = captot*captot;
    *tambah = 3*captot*captot+1;
    return poltotal;
}
#endif
