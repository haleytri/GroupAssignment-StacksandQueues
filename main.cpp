#include "ArgumentManager.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <stack>
using namespace std;

bool validity(string &);

int main(int argc, char *argv[]) {
  ArgumentManager am(argc, argv);
   ifstream input(am.get("input"));
   ofstream output(am.get("output"));

  //ifstream input("input1.txt");
  //ofstream output("");

  queue<string> valid;
  queue<string> invalid;
  string data = "";
  while (getline(input, data)) {
    data.erase(remove(data.begin(), data.end(), '\n'), data.end());
    data.erase(remove(data.begin(), data.end(), '\r'), data.end());

    if (validity(data)) {
      valid.push(data);
    } else {
      invalid.push(data);
    }
  }

  if (!invalid.empty()) {
    cout << "Invalid" << endl;
    output << "Invalid" << endl;
    while (invalid.size() > 0) {
      cout << invalid.front() << endl;
      output << invalid.front() << endl;
      invalid.pop();
    }
  }

  if (!valid.empty()) {
    cout << "Valid" << endl;
    output << "Valid" << endl;
    while (valid.size() > 0) {
      cout << valid.front() << endl;
      output << valid.front() << endl;
      valid.pop();
    }
  }
}

bool validity(string &b) {
  stack<char> s;
  for (int i = 0; i < b.length(); i++) {
    if (b[i] == '(') // can be enclosed in any
    {
      s.push(b[i]);
    } else if (b[i] == '[') // must be enclosed in curly or square
    {
      if (s.empty() || s.top() == '(') {

        if (s.empty()) {
          s.push(b[i]);
          continue;
        }
        return false;
      }
      s.push(b[i]);
    } else if (b[i] == '{') // must be enclosed in other curly brackets
    {
      if (s.empty() || s.top() == '(' || s.top() == '[') {
        if (s.empty()) {
          s.push(b[i]);
          continue;
        }
        return false;
      }
      s.push(b[i]);
    } else if (b[i] == ')' || b[i] == ']' || b[i] == '}') {
      if (s.empty()) {
        return false;
      }
      char t = s.top();
      if ((b[i] == '}' && t != '{') || (b[i] == ']' && t != '[') ||
          (b[i] == ')' && t != '('))
        return false;
      else
        s.pop();
    }
  }

  if (!s.empty()) {
    return false;
  }
  
  return true;
}
