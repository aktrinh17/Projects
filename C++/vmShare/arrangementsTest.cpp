// Copyright 2018 Alexander Trinh aktrinh@bu.edu
#include <algorithm>
#include <array>
#include <cmath>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "timer.h"

using std::vector;
using std::string;
using std::cout;
using std::sort;
using std::unordered_map;

string thenames = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
//string thenames = "123456789";

unordered_map<int, vector<string>> refMap;

vector<string> panel_shuffles(int n) {
    vector<string> v;
    string str1, str2, str3;
    // checks for previously generated panels
    if (refMap.find(0) == refMap.end() && refMap.find(1) == refMap.end() ||
    	refMap.find(0) == refMap.begin() && refMap.find(1) == refMap.begin()) {
	    str1 = thenames.at(0);

	    vector<string> first;
	    first.push_back(str1);

	    refMap.emplace(0, first);

	    str2 += thenames.at(0); 
	    str2 += thenames.at(1);

	    str3 += thenames.at(1);
	    str3 += thenames.at(0);

	    vector<string> second;
	    second.push_back(str2);
	    second.push_back(str3);

	    refMap.emplace(1, second);
	}

	// checks for if the previous 2 panels are already generated
	if (refMap.find(n-2) != refMap.end() || refMap.find(n-3) != refMap.end()) {
	    vector<string> xi;
	    for (int j = 0; j < refMap.at((n-1)-1).size(); j++)
	    {	
	    	str1 = "";
	    	str1 = refMap.at((n-1)-1).at(j) + thenames.at((n-1));
	    	xi.push_back(str1);
	    }
		for (int k = 0; k < refMap.at((n-1)-2).size(); k++)
	    {
	    	str2 = "";
	    	str2 = refMap.at((n-1)-2).at(k) + thenames.at((n-1)) + thenames.at((n-1)-1);
	    xi.push_back(str2);
	    }
	    refMap.emplace(n-1, xi);
	} else {
	    for (int i = 2; i < n; i++)
	    {
	    	vector<string> xi;
	    	for (int j = 0; j < refMap.at(i-1).size(); j++)
	    	{	
	    		str1 = "";
	    		str1 = refMap.at(i-1).at(j) + thenames.at(i);
	    		xi.push_back(str1);
	    	}

	    	for (int k = 0; k < refMap.at(i-2).size(); k++)
	    	{
	    		str2 = "";
	    		str2 = refMap.at(i-2).at(k) + thenames.at(i) + thenames.at(i-1);
	    		xi.push_back(str2);
	    	}
	    	refMap.emplace(i, xi);
	    }
	}
    v = refMap.at(n-1);
    for (int i = 0; i < v.size(); i++)
	{
	    std::cout << v[i] << ' ';
	}
    return v;
  }

  // add the panel things and if a and d are the last, 
  // add the same thing but with them switched 
  //then you have to do all of them left and all of them right
  vector<string> dinner_shuffles(int n) {
    vector<string> v = panel_shuffles(n);
    string str; 

    if (n > 2) {
	    for (int i = 0; i < v.size(); i++) {
	    	if (v.at(i).at(0) == thenames.at(0)) {
	    		if (v.at(i).at(n-1) == thenames.at(n-1)) {
	    		str = "";
	    		str += v.at(i);
	    		std::swap(str.at(0), str.at(n-1));
	    		v.push_back(str);
	    		}
	    	}	
	    }
	    str = "";
	    // original shifted to the left one
	    str += thenames.substr(1, n-1) + thenames.at(0);
	    v.push_back(str);

	    str = "";
	    // original shifted to the right one
	    str += thenames.at(n-1) + thenames.substr(0,n-1);
	    v.push_back(str);
	}
	for (int i = 0; i < v.size(); i++)
	{
	    std::cout << v[i] << ' ';
	}
 	return v;
  } 

double panel_count(int n) {
  cout.precision(15);
  vector<double> seats;
  seats.push_back(1);
  seats.push_back(2);
  for (int i = 2; i <= n; i ++)
  {
  	seats.push_back(seats.at(i-1) + seats.at(i-2));
  }
   return seats.at(n-1);
}

double dinner_count(int n) {
	cout.precision(15);
	vector<double> seats;
	seats.push_back(1);
	seats.push_back(2);
	seats.push_back(6);
	seats.push_back(9);
	for (int i = 4; i <= n; i++)
	{
	  seats.push_back(seats.at(i-1) + seats.at(i-2) -2);
	}
    return seats.at(n-1);
  }

int main() {
	panel_shuffles(0);
	//panel_shuffles(1);
	/*panel_shuffles(2);
	panel_shuffles(3);
	panel_shuffles(4);*/
	return 0;
}
