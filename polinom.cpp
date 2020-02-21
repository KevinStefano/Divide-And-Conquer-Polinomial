#include <iostream>
#include<stdlib.h>
#include<time.h> 

#include <algorithm> 
#include <chrono> 
using namespace std::chrono; 

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

    void BacaPolinom();
    void TulisPolinom();
    void ResetPolinom();
    
    friend polinom KaliBruteForce (polinom pol1, polinom pol);  //Kali bruteforce
    friend polinom KalikanDenganXPangkat(polinom pol,int pangkat);
    friend polinom TambahPolinom(polinom pol1, polinom pol2);
    friend void KaliDAC (polinom pol1, polinom pol2, polinom *poltot, int pangkat); //Kali Divide and Conquer
};

//Fungsi tambahan
polinom KaliBruteForce (polinom pol1, polinom pol); //Kali bruteforce
polinom KalikanDenganXPangkat(polinom pol,int pangkat);
polinom TambahPolinom(polinom pol1, polinom pol2);
void KaliDAC (polinom pol1, polinom pol2, polinom *poltot, int pangkat); //Kali Divide and Conquer
void Merge (polinom pol1, polinom pol2, polinom poltot3, int idx1, int idx2, int cap, polinom *poltot);


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



polinom::polinom(const polinom& pol, int idxstart, int cap) {
    this->cap = cap;
    this->data = new int[this->cap+1];
    for (int i=0; i<=this->cap; i++) {
        this->data[i] =pol.data[idxstart];
        idxstart++;
    }
}


polinom TambahPolinom(polinom pol1, polinom pol2) {
    int cap;
    if (pol1.cap>pol2.cap) {
        cap = pol1.cap;
    }
    else {
        cap = pol2.cap;
    }
    polinom p(cap);
    for (int i=0;i<=p.cap;i++) {
        if (i>pol1.cap) {
            p.data[i]=pol2.data[i];
        }
        else if (i>pol2.cap) {
            p.data[i]=pol1.data[i];
        }
        else {   
            p.data[i] = pol1.data[i]+pol2.data[i];
        }
    }
    return p;
}

void KaliDAC (polinom pol1, polinom pol2, polinom *poltot, int pangkat) {
    if (pol1.cap== 1  && pol2.cap==1) { //Basis
        polinom p0(pol1,0,(pol1.cap+1)/2-1);
        polinom p1(pol1,(pol1.cap+1)/2,pol1.cap-((pol1.cap+1)/2));
        polinom q0(pol2,0,(pol2.cap+1)/2-1);
        polinom q1(pol2,(pol2.cap+1)/2,pol2.cap-((pol2.cap+1)/2));

        // polinom p0(pol1,0,0);
        // polinom p1(pol1,1,1);
        // polinom q0(pol2,0,0);
        // polinom q1(pol2,1,1);

       *poltot = KalikanDenganXPangkat(p1*q1,pol1.cap+1) + KalikanDenganXPangkat((p0+p1)*(q0+q1)-p0*q0-p1*q1,(pol1.cap+1)/2) + p0*q0;


    }
    
    else if (pol1.cap==0 && pol2.cap==0) {
        (*poltot) = pol1*pol2;
        // cout << "HAAsil : ";
        // (*poltot).TulisPolinom();
    }
    else if (pol1.cap> 1  && pol2.cap>1) {
        polinom p0(pol1,0,(pol1.cap+1)/2-1);
        polinom p1(pol1,(pol1.cap+1)/2,pol1.cap-((pol1.cap+1)/2));
        polinom q0(pol2,0,(pol2.cap+1)/2-1);
        polinom q1(pol2,(pol2.cap+1)/2,pol2.cap-((pol2.cap+1)/2));
        // cout << pol1.cap<<endl;
        // cout<< "p0 : ";
        // p0.TulisPolinom();
        // cout<< "p1 : ";
        // p1.TulisPolinom();
        // cout<< "q0 : ";
        // q0.TulisPolinom();
        // cout<< "q1 : ";
        // q1.TulisPolinom();
        polinom p0q0,p1q1,r;
        KaliDAC(p0,q0,&p0q0, pol1.cap);
        KaliDAC(p1,q1,&p1q1,pol1.cap);
    //    (p0+p1).TulisPolinom();
    //     (q0+q1).TulisPolinom();
        KaliDAC((p0+p1),(q0+q1),&r, pol1.cap);
            //  (r).TulisPolinom();
        //bit.ly/2240202002
        // cout << pol1.cap<<endl;
        // cout << "Hasil : "; 
         //KalikanDenganXPangkat(r,pol1.cap).TulisPolinom();
        //KalikanDenganXPangkat(p1q1,pol1.cap) + KalikanDenganXPangkat((p0+p1)*(q0+q1)-p0*q0-p1*q1,(pol1.cap+1)/2) + p0*q0;
        //*poltot = TambahPolinom(TambahPolinom(KalikanDenganXPangkat(p1q1,pol1.cap),KalikanDenganXPangkat((r-p0q0-p1q1),(pol1.cap+1)/2)),p0q0);
        
        if (pol1.cap%2==0 ) {
            *poltot = KalikanDenganXPangkat(p1q1,pol1.cap) + KalikanDenganXPangkat(r-p0q0-p1q1,(pol1.cap+1)/2) + p0q0;
        }
        else {
            *poltot = KalikanDenganXPangkat(p1q1,pol1.cap+1) + KalikanDenganXPangkat(r-p0q0-p1q1,(pol1.cap+1)/2) + p0q0;

        }
        // (*poltot).TulisPolinom();
         }
}

void Merge (polinom poltot1, polinom poltot2, polinom poltot3, int idx1, int idx2, int cap, polinom *poltot){
   // poltot1 = poltot3.KalikanDenganXPangkat(poltot1.cap)+(poltot2)
   
}
    
polinom KalikanDenganXPangkat(polinom pol, int pangkat) {
    polinom p(pol.cap+pangkat);
    p.ResetPolinom();
    for (int i=0;i<=pol.cap;i++) {
        p.data[i+pangkat]=pol.data[i];
    }
    return p;
}

void polinom::BacaPolinom() {
    srand(time(0)); 

    for (int i=0;i<=this->cap;i++) {
        int n;
        // cout<< "Masukkan nilai dari pangkat ke-"<<i<<" : ";
        // cin>> n;
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


int main() {

    int cap1;
    cout << "Masukkan pangkat tertinggi : " ;
    cin >> cap1;
    polinom pol1(cap1);
    pol1.BacaPolinom();
    //pol1.TulisPolinom();
    polinom pol2(cap1);
    pol2.BacaPolinom();
    //pol2.TulisPolinom();
    polinom pol3;
    // pol3 = pol1+pol2;
    // pol3.TulisPolinom();
    //(TambahPolinom(pol1,pol2)).TulisPolinom();
    
    auto start = high_resolution_clock::now(); 
    pol3 = KaliBruteForce(pol1,pol2);
    auto stop = high_resolution_clock::now(); 

    auto duration = duration_cast<microseconds>(stop - start); 
    //pol3.TulisPolinom();
    cout << "Time taken by Brute Force: "
         << duration.count() << " microseconds" << endl; 

    polinom poltot;

    
    auto start2 = high_resolution_clock::now(); 
    KaliDAC(pol1,pol2,&poltot, cap1);
    auto stop2 = high_resolution_clock::now(); 
    //poltot.TulisPolinom();
       auto duration2 = duration_cast<microseconds>(stop2 - start2); 
  
    cout << "Time taken by Divide and Conquer: "
         << duration2.count() << " microseconds" << endl; 

    return 0;
}
