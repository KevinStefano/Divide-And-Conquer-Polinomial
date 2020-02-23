//Nama : Kevin Austin Stefano
//NIM : 13518104


#ifndef DIVIDEANDCONQUER_H
#define DIVIDEANDCONQUER_H

#include "Polinom.h"
#include <iostream>

using namespace std;


void KaliDAC (polinom pol1, polinom pol2, polinom *poltot, int *tambah, int *kali) {
    
    //BASIS 1
    if (pol1.cap== 1  && pol2.cap==1) { //Basis
        int capplusone = pol1.cap+1;
        int idx1  = capplusone/2-1;
        int idx2  = capplusone/2;
        polinom p0(pol1,0,idx1);
        polinom p1(pol1,idx2,pol1.cap-idx2);
        polinom q0(pol2,0,idx1);
        polinom q1(pol2,idx2,pol2.cap-idx2);

        polinom p1q1 = p1*q1;
        polinom r = (p0+p1)*(q0+q1);
        polinom p0q0 = p0*q0;
       *poltot = KalikanDenganXPangkat(p1q1,capplusone) + KalikanDenganXPangkat(r-p0q0-p1q1,idx2) + p0q0;
        *kali = *kali+5; 
       *tambah = *tambah+14; //tanpa overloading 6, overloading 1 ambil pangkat terkecil = 1, overloading 2 apt = idx2+1, capplusone=3+2 

    }
    
    //BASIS 2
    else if (pol1.cap==0 && pol2.cap==0) {
        (*poltot) = pol1*pol2;
        *kali = *kali+1;
    }

    //BUKAN BASIS
    else if (pol1.cap> 1  && pol2.cap>1) {
    //DIVIDE
       int capplusone = pol1.cap+1;
        int idx1  = capplusone/2-1;
        int idx2  = capplusone/2;
        polinom p0(pol1,0,idx1);
        polinom p1(pol1,idx2,pol1.cap-idx2);
        polinom q0(pol2,0,idx1);
        polinom q1(pol2,idx2,pol2.cap-idx2);
        polinom p0q0,p1q1,r;

    //CONQUER
        KaliDAC(p0,q0,&p0q0,tambah,kali);
        KaliDAC(p1,q1,&p1q1,tambah,kali);
        KaliDAC((p0+p1),(q0+q1),&r,tambah,kali);


    //MERGE
        //Jika derajat genap
        if (pol1.cap%2==0 ) {
            *poltot = KalikanDenganXPangkat(p1q1,pol1.cap) + KalikanDenganXPangkat(r-p0q0-p1q1,idx2) + p0q0;
            *kali = *kali +2;
            *tambah = *tambah+11+p0q0.cap+r.cap+idx2+pol1.cap+idx2;  //Yang terlihat tanpa overloading 6, overloading 1 = p0q0.cap+1, overloading- = r.cap+1, overloading+ 2 = idx2+1, , kalikandenganXPangkat = pol1.cap+1, idx2+1
        }
        //Jika derajat ganjil
        else {
            *poltot = KalikanDenganXPangkat(p1q1,capplusone) + KalikanDenganXPangkat(r-p0q0-p1q1,idx2) + p0q0;
            *kali = *kali +2;
            *tambah = *tambah+11+p0q0.cap+r.cap+idx2+pol1.cap+idx2;  //Yang terlihat tanpa overloading 6, overloading 1 = p0q0.cap+1, overloading- = r.cap+1, overloading+ 2 = idx2+1, , kalikandenganXPangkat = pol1.cap+1, idx2+1
        
        }
    }
}

#endif
