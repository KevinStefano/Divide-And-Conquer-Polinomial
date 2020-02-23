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

     srand(time(0)); 
    
    cout << "Polinom 1" <<endl; 
    polinom pol1(cap1);
    pol1.BacaPolinomRandom();
    pol1.TulisPolinom();
    cout<<endl;

    cout << "Polinom 2" <<endl;
    polinom pol2(cap1);
    pol2.BacaPolinomRandom();
    pol2.TulisPolinom();
    cout <<endl;
    int kali=0; int tambah=0;

    polinom pol3;
    
    //BruteForce
    cout << "Hasil Perkalian dengan Algoritma Brute Force"<<endl;
    auto start = high_resolution_clock::now(); 
    pol3 = KaliBruteForce(pol1,pol2,&tambah, &kali);
    auto stop = high_resolution_clock::now(); 
     
    auto duration = duration_cast<microseconds>(stop - start); 
    pol3.TulisPolinom();
    cout << "Banyaknya operasi perkalian : " <<kali<<endl;
    cout << "Banyaknya operasi penjumlahan : "<<tambah<<endl;
    cout << "Time taken by Brute Force: "
         << duration.count() << " microseconds" << endl; 
    cout<<endl;

    //Divide And Conquer
    polinom poltot;
    kali=0; tambah=0;
    cout << "Hasil Perkalian dengan Algoritma Divide And Conquer"<<endl;
    auto start2 = high_resolution_clock::now(); 
    KaliDAC(pol1,pol2,&poltot,&tambah, &kali);
    auto stop2 = high_resolution_clock::now(); 
    poltot.TulisPolinom();
       auto duration2 = duration_cast<microseconds>(stop2 - start2); 
       
     cout << "Banyaknya operasi perkalian : " <<kali<<endl;
    cout << "Banyaknya operasi penjumlahan : "<<tambah<<endl;
    cout << "Time taken by Divide and Conquer: "
         << duration2.count() << " microseconds" << endl; 

    return 0;
}