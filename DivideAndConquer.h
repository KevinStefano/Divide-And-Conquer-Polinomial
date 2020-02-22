//Nama : Kevin Austin Stefano
//NIM : 13518104


#ifndef DIVIDEANDCONQUER_H
#define DIVIDEANDCONQUER_H

#include "Polinom.h"
#include <iostream>

using namespace std;


void KaliDAC (polinom pol1, polinom pol2, polinom *poltot) {
    //BASIS
    if (pol1.cap== 1  && pol2.cap==1) { //Basis
        polinom p0(pol1,0,(pol1.cap+1)/2-1);
        polinom p1(pol1,(pol1.cap+1)/2,pol1.cap-((pol1.cap+1)/2));
        polinom q0(pol2,0,(pol2.cap+1)/2-1);
        polinom q1(pol2,(pol2.cap+1)/2,pol2.cap-((pol2.cap+1)/2));
       *poltot = KalikanDenganXPangkat(p1*q1,pol1.cap+1) + KalikanDenganXPangkat((p0+p1)*(q0+q1)-p0*q0-p1*q1,(pol1.cap+1)/2) + p0*q0;
    }
    
    else if (pol1.cap==0 && pol2.cap==0) {
        (*poltot) = pol1*pol2;
    }

    //BUKAN BASIS
    else if (pol1.cap> 1  && pol2.cap>1) {
    //Divide   
        polinom p0(pol1,0,(pol1.cap+1)/2-1);
        polinom p1(pol1,(pol1.cap+1)/2,pol1.cap-((pol1.cap+1)/2));
        polinom q0(pol2,0,(pol2.cap+1)/2-1);
        polinom q1(pol2,(pol2.cap+1)/2,pol2.cap-((pol2.cap+1)/2));
        polinom p0q0,p1q1,r;
    
    //Conquer
        KaliDAC(p0,q0,&p0q0);
        KaliDAC(p1,q1,&p1q1);
        KaliDAC((p0+p1),(q0+q1),&r);
    
    //Solve
        //Jika derajat genap
        if (pol1.cap%2==0 ) {
            *poltot = KalikanDenganXPangkat(p1q1,pol1.cap) + KalikanDenganXPangkat(r-p0q0-p1q1,(pol1.cap+1)/2) + p0q0;
        }
        //Jika derajat ganjil
        else {
            *poltot = KalikanDenganXPangkat(p1q1,pol1.cap+1) + KalikanDenganXPangkat(r-p0q0-p1q1,(pol1.cap+1)/2) + p0q0;

        }
    }
}
#endif
