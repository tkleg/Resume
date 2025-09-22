
#include <iostream>
using namespace std;
enum state {AL, AK, AZ, AR, AS, CA, CO, CT, DE, DC, FL, GA, HI, ID, IL, IN, IA,
KS, KY, LA, ME, MD, MA, MI, MN, MS, MO, MT, NE, NV, NH, NJ, NM, NY, NC, ND, MP,
OH, OK, OR, PA, RI, SC, SD, TN, TX, UT, VT, VA, WA, WV, WI, WY};

int main()
{
	state testS = WA;
	cout << (int) testS << ", " << (char) testS << endl;
	state home = GA; //4 bytes (int in disguise)
	char compressed_home = (char) home;
	state uncompressed_home = (state) compressed_home;

	cout << "home = " << home << endl;
	cout << "compressed_home = " << compressed_home << endl;
	cout << "uncompressed_home = " << uncompressed_home << endl;

	cout << "sizeof home = " << sizeof(home) << endl;
	cout << "sizeof compressed_home = " << sizeof(compressed_home) << endl;
	cout << "sizeof uncompressed_home = " << sizeof(uncompressed_home) << endl;

	switch (uncompressed_home)
	{
		case GA:  cout << "GA" << endl;
		break;
	}

	return 0;
}
