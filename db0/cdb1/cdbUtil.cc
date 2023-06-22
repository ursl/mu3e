#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <unistd.h>

#include "cdbUtil.hh"

using namespace std;

// ----------------------------------------------------------------------
void replaceAll(string &str, const string &from, const string &to) {
  if (from.empty()) return;
  size_t start_pos = 0;
  while((start_pos = str.find(from, start_pos)) != string::npos) {
    str.replace(start_pos, from.length(), to);
    start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
  }
}


// ----------------------------------------------------------------------
void cleanupString(string &s) {
  replaceAll(s, "\t", " ");
  string::size_type s1 = s.find("#");
  if (string::npos != s1) s.erase(s1);
  if (0 == s.length()) return;
  string::iterator new_end = unique(s.begin(), s.end(), bothAreSpaces);
  s.erase(new_end, s.end());
  if (s.substr(0, 1) == string(" ")) s.erase(0, 1);
  if (s.substr(s.length()-1, 1) == string(" ")) s.erase(s.length()-1, 1);
}


// ----------------------------------------------------------------------
bool bothAreSpaces(char lhs, char rhs) {
  return (lhs == rhs) && (lhs == ' ');
}


// ----------------------------------------------------------------------=
void rmSubString(string &sInput, const string &sub) {
  string::size_type foundpos = sInput.find(sub);
  if (foundpos != string::npos)  {
    sInput.erase(sInput.begin() + foundpos, sInput.begin() + foundpos + sub.length());
  }
}

// ----------------------------------------------------------------------=
void rmPath(string &sInput) {
  string::size_type foundpos = sInput.find("/");
  while(string::npos != foundpos) {
    sInput.erase(sInput.begin(), sInput.begin() + foundpos + 1);
    foundpos = sInput.find("/");
  }
}


// ----------------------------------------------------------------------
vector<string> split(const string &s, char delim) {
  vector<string> elems;
  split(s, delim, elems);
  return elems;
}


// ----------------------------------------------------------------------
void /*vector<string>&*/ split(const string &s, char delim, vector<string> &elems) {
  stringstream ss(s);
  string item;
  while (getline(ss, item, delim)) {
    elems.push_back(item);
  }
  //  return elems;
}


