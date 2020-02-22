//Nama : Kevin Austin Stefano
//NIM : 13518104


#ifndef POLINOMIAL_H
#define POLINOMIAL_H

#include <iostream>

using namespace std;

class polinom
{
private:
    int* data;
    int cap;
public:
    polinom(); //Default nya pangkat 2
    polinom(int cap);
    polinom(const polinom& pol);
    polinom(const polinom& pol, int idxstart, int cap);
    ~polinom();

    polinom operator+ (polinom pol);
    polinom operator- (polinom pol);
    polinom& operator= (polinom pol);
    polinom operator* (polinom pol);
    
    void BacaPolinomRandom();
    void TulisPolinom();
    void ResetPolinom();
    

    friend polinom KaliBruteForce (polinom pol1, polinom pol);  //Kali bruteforce
    friend polinom KalikanDenganXPangkat(polinom pol,int pangkat);
    friend void KaliDAC (polinom pol1, polinom pol2, polinom *poltot); //Kali Divide and Conquer
};

//Fungsi tambahan
polinom KalikanDenganXPangkat(polinom pol,int pangkat);

polinom::polinom(){
    this->cap=2;
    this->data = new int[3];
}

polinom::polinom(int cap) {
    this->cap = cap;
    this->data= new int[this->cap+1];
}

polinom::polinom(const polinom& pol) {
    this->cap = pol.cap;
    this->data = new int[this->cap+1];
    for (int i=0; i<=this->cap; i++) {
        this->data[i] =pol.data[i];
    }
}



polinom::polinom(const polinom& pol, int idxstart, int cap) {
    this->cap = cap;
    this->data = new int[this->cap+1];
    for (int i=0; i<=this->cap; i++) {
        this->data[i] =pol.data[idxstart];
        idxstart++;
    }
}

polinom::~polinom(){
    delete[] this->data;
}

polinom polinom::operator+ (polinom pol){
       int cap;
    if (this->cap>pol.cap) {
        cap = this->cap;
    }
    else {
        cap = pol.cap;
    }
    polinom p(cap);
    for (int i=0;i<=p.cap;i++) {
        if (i>this->cap) {
            p.data[i]=pol.data[i];
        }
        else if (i>pol.cap) {
            p.data[i]=this->data[i];
        }
        else {   
            p.data[i] = this->data[i]+pol.data[i];
        }
    }
    return (p);
}

polinom polinom::operator- (polinom pol){
      int cap;
    if (this->cap>pol.cap) {
        cap = this->cap;
    }
    else {
        cap = pol.cap;
    }
    polinom p(cap);
    for (int i=0;i<=p.cap;i++) {
        if (i>this->cap) {
            p.data[i]=pol.data[i];
        }
        else if (i>pol.cap) {
            p.data[i]=this->data[i];
        }
        else {   
            p.data[i] = this->data[i]-pol.data[i];
        }
    }
    return (p);
}

polinom& polinom::operator= (polinom pol) {
    delete[] this->data;
    this->cap = pol.cap;
    this->data = new int[this->cap+1];
    for (int i=0; i<=this->cap; i++) {
        this->data[i] =pol.data[i];
    }
    return *this;
}

polinom polinom::operator* (polinom pol) {
    polinom poltotal(this->cap+pol.cap);
    poltotal.ResetPolinom();
    for (int i =0;i<=this->cap;i++) {
        for (int j=0;j<=pol.cap;j++) {
            poltotal.data[i+j]=poltotal.data[i+j]+(this->data[i]*pol.data[j]);
        }
    }
    return poltotal;
}


    
polinom KalikanDenganXPangkat(polinom pol, int pangkat) {
    polinom p(pol.cap+pangkat);
    p.ResetPolinom();
    for (int i=0;i<=pol.cap;i++) {
        p.data[i+pangkat]=pol.data[i];
    }
    return p;
}

void polinom::BacaPolinomRandom() {
    srand(time(0)); 

    for (int i=0;i<=this->cap;i++) {
        int n;
        this->data[i] = rand()%50;
    }
}

void polinom::TulisPolinom() {
    for(int i=0;i<=this->cap;i++) {
        //Saat nilai pangkat nolnya bukan nol
        if (i==0 && this->data[i]!=0) {
            if (this->data[i] <0) {
                cout << "- "<<this->data[i]*-1 << " ";
            }
            else {
                cout << this->data[i] << " ";
            }
        }
        //Saat nilai pangkat apapun nol
        else if (this->data[i]==0) {
            //Do nothing
        }

        //Saat pangkat 1
        else if (i==1 && this->data[i] > 0) {
            cout <<"+ ";
            if (this->data[i]!=1) {
                cout << this->data[i] ;
            }
            cout << "X ";
        }
        else if (i==1 &&this->data[i] < 0) {
            cout <<"- ";
            if (this->data[i]!=-1) {
                cout << this->data[i]*-1 ;
            }
            cout << "X ";
        }
        //Saat pangkat selain pangkat 1
        else if (this->data[i] > 0) {
            cout <<"+ ";
            if (this->data[i]!=1) {
                cout << this->data[i] ;
            }
            cout << "X^" <<i<<" ";
        }
        else if (this->data[i] < 0) {
            cout <<"- ";
            if (this->data[i]!=-1) {
                cout << this->data[i]*-1 ;
            }
            cout << "X^" <<i<<" ";
        }
    }
    cout <<endl;
}

void polinom::ResetPolinom() {
    for (int i=0;i<=this->cap;i++) {
        this->data[i] = 0;
    }
}

#endif
