//Nama : Kevin Austin Stefano
//NIM  : 13518104

//Libray umum
#include <iostream>
#include <stdlib.h>

//Library untuk penghitungan waktu
#include <time.h> 
#include <algorithm> 
#include <chrono> 

//Library Polinom, Brute Force dan Divide and Conquer
#include "Polinom.h"
#include "BruteForce.h"
#include "DivideAndConquer.h"

using namespace std::chrono; 
using namespace std;


int main() {

    int cap1;
    cout << "Masukkan pangkat tertinggi : " ;
    cin >> cap1;
    polinom pol1(cap1);
    pol1.BacaPolinomRandom();
    //pol1.TulisPolinom();
    polinom pol2(cap1);
    pol2.BacaPolinomRandom();
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
    KaliDAC(pol1,pol2,&poltot);
    auto stop2 = high_resolution_clock::now(); 
    //poltot.TulisPolinom();
       auto duration2 = duration_cast<microseconds>(stop2 - start2); 
  
    cout << "Time taken by Divide and Conquer: "
         << duration2.count() << " microseconds" << endl; 

    return 0;
}