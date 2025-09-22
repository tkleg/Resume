#include <iostream>
#include <sstream>
#include <string>
using namespace std;

int main() {
  string inputLine = "our_program 0.01";
  char ch;
  string s;
  istringstream ss(inputLine);

  ss >> s >> ch;
  cout << "ss= \"" << ss.str() << "\"\ns=\"" << s << "\"\nch= \"" << ch << "\"" << endl  ;


  return 0;
}
