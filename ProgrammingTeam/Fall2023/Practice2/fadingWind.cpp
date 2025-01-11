#include <iostream>
using namespace std;

int main(){

int height;
int factor;
int velocity;
int strength;
int distance = 0;
cin >> height;
cin >> factor;
cin >> velocity;
cin >> strength;
while( height > 0 ){
	velocity += strength;
        velocity -= max( 1, (int)( (velocity/10.0) ) );
        if( velocity >= factor )
                height++;
        if( 0 < velocity < factor ){
                height--;
                if( height == 0 )
                        velocity = 0;
        }
        if( velocity <= 0 ){
                height = 0;
                velocity = 0;
        }
        distance += velocity;
        if( strength > 0 )
                strength--;

}
cout << distance << endl;

return 0;
}

