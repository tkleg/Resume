#include <bitset>
#include <iostream>
using namespace std;
const int numColors = 6;
enum Color {red, yellow, green, blue, white, black};
int main()
{
bitset<50> flags;
flags.set(44);
flags[42] = true;
cout << flags << endl; // operator << and >> both defined
flags[42].flip();
cout << flags << endl;
flags[10] = ~flags[10];
cout << flags << endl;
bitset<numColors> usedColors;
usedColors.set(red);
usedColors.set(blue);
cout << "bitfield of used colors: " << usedColors << endl;
cout <<"number of used colors: "<< usedColors.count()<< endl;
cout << "bitfield of unused colors: " << ~usedColors << endl;
if (usedColors.any()) // if any color is used
for (int c = 0; c < numColors; c++)
if (usedColors[c])
cout << "bit " << c << " in use!" << endl;
return 0;
}
