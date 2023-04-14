/*
 * WelcomeToRecursion.cpp
 *
 *  Created on: Apr 25, 2022
 *      Author: feelt
 */
#include "WelcomeToRecursion.h"
#include <iostream>
#include "simpio.h"
#include <string>
#include "error.h"
#include <ctype.h>
#include "grid.h"

using namespace std;

int nChooseKHelper(int n, int k, int row, int col, Grid<int>& sums){
 //n is row k is col
 if((col == 0) || (col == row)){
	 sums.set(row,col,1);
 } else {
	 sums.set(row,col, sums.get(row-1,col-1)+sums.get(row-1,col));}
 if((n == row) && (k == col)){
	 int j = sums.get(row,col);
	 cout << j << endl;
	 return j;
 }
 if(col == row){
	 nChooseKHelper(n,k,row+1,0,sums);
 } else {
	 nChooseKHelper(n,k,row,col+1,sums);
 }
}


int nChooseK(int n, int k) {
 // [TODO: fill in the code]
 Grid<int> sums(n+2,n+2);
 sums.set(0,0,1);
 sums.set(1,0,1);
 sums.set(1,1,1);
 if(n == 1){
	 return sums.get(n,k);
 }
 return nChooseKHelper(n, k, 2, 0, sums);
}
int stringToInt(string str) {
 if(str == ""){
	 return 0;
 }
 char ch = str[0];
 if(ch == '-'){
	 str.erase(0,1);
	 return stringToInt(str) * -1;
 }
 ch = str[str.size() - 1];
 int tmp = ch - '0';
 if((ch < '0') || (ch > '9')){ cout << "invalid character used" << endl;; return 0;}
 	 str.erase(str.size()-1, 1);
 	 return stringToInt(str) * 10 + tmp;
}
string intToStringHelper(int n) {
 if(n < 0){
	 n *= -1;
	 return "-" + intToStringHelper(n);
 }
 string str;
 if(n/1 == 0){
	 return "";
 }
 int tmp = n % 10;
 n = n/10;
 //
 char ch = char(tmp + '0');
 return intToStringHelper(n) + ch;
}
string intToString(int n){
 if(n == 0){
	 return "0";
 }
 return intToStringHelper(n);
}



