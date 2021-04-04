#include <iostream>
#include <map>
using namespace std;

int* parseString(string str)
{
    map<string,int> dict = {{"a",0},{"b",1},{"c",2},{"d",3},{"e",4},{"f",5},{"g",6},{"h",7}};
    int* ar = new int[4];
    ar[0] = dict[str.substr(0,1)], ar[1] = stoi(str.substr(1,1));
    ar[3] = dict[str.substr(3,1)], ar[4] = stoi(str.substr(4,1));
    return ar;
};

int main(){

    for (int i = 0; i<4; i++)
    {
        cout << parseString("e2-g4")[0] << " " <<parseString("e2-g4")[1] << endl;
        cout << parseString("e2-g4")[3] << " " <<parseString("e2-g4")[4] << endl;
    }
    return 0;
}