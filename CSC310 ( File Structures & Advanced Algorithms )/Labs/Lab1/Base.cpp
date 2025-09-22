#include<iostream>
using namespace std;

class Base{
    public:
        virtual void iam();
};

void Base::iam(){
    cout << "base" << endl;
}

class One : public Base{
    public:
        void iam2(){
        	Base::iam();
        }
	void iam(){
		cout << "one" << endl;
	}
};

class Two : public Base{
    public:
        void iam2(){
            Base::iam();
        }
	void iam(){
		cout << "two" << endl;
	}
};

int main(){
    One derived1;
    derived1.iam2();
    derived1.iam();
    Base *d1Ptr = &derived1;
    d1Ptr -> iam();

    Two derived2;
    derived2.iam2();
    derived2.iam();
    Base *d2Ptr = &derived2;
    d2Ptr -> iam();
    return 0;
}

