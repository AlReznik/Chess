#include <iostream>
#include <map>
using namespace std;

int* parseCommand(string str)
{
    map<string,int> dict = {{"a",0},{"b",1},{"c",2},{"d",3},{"e",4},{"f",5},{"g",6},{"h",7}};
    int* ar = new int[4];
    ar[0] = dict[str.substr(0,1)], ar[1] = stoi(str.substr(1,1));
    ar[2] = dict[str.substr(3,1)], ar[3] = stoi(str.substr(4,1));
    return ar;
};

int main(){
    string input;
    cout << "Input your move using pattern #0-#0" << endl;
    cin >> input;
    int x1 = parseCommand(input)[0]; int y1 = parseCommand(input)[1];
    int x2 = parseCommand(input)[2]; int y2 = parseCommand(input)[3];
    cout << parseCommand(input)[0] << " " <<parseCommand(input)[1] << endl;
    cout << parseCommand(input)[2] << " " <<parseCommand(input)[3] << endl;
    cout << x1 << " " << y1 << " " << x2 << " " << y2 << endl;
/*     for (int i = 0; i<4; i++)
    {
        cout << parseString("e2-g4")[0] << " " <<parseString("e2-g4")[1] << endl;
        cout << parseString("e2-g4")[3] << " " <<parseString("e2-g4")[4] << endl;
    } */

    return 0;
}