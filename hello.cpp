#include <iostream>
#include <map>
#include <algorithm>
#include <iterator>
using namespace std;

/* int* parseCommand(string str)
{
    map<string,int> dict = {{"a",0},{"b",1},{"c",2},{"d",3},{"e",4},{"f",5},{"g",6},{"h",7}};
    int* ar = new int[4];
    ar[0] = dict[str.substr(0,1)], ar[1] = stoi(str.substr(1,1));
    ar[2] = dict[str.substr(3,1)], ar[3] = stoi(str.substr(4,1));
    return ar;
} */
bool checkInput(string input)
{
    string letters[8] = {"a","b","c","d","e","f","h"};
    string digits[8] = {"1","2","3","4","5","6","7","8"};
    if (find(begin(letters),end(letters),input.substr(0,1))!=end(letters) && find(begin(digits),end(digits),input.substr(1,1))!=end(digits) &&
    find(begin(letters),end(letters),input.substr(3,1))!=end(letters) && find(begin(digits),end(digits),input.substr(4,1))!=end(digits) &&
    input.substr(2,1)=="-")
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int main()
{
    string letters[8] = {"a","b","c","d","e","f","g","h"};

    string rawinput;
    cout << "Input your move using pattern #0-#0" << endl;
    cin >> rawinput;
    string input = rawinput;
    cout << input << " " << checkInput(input) << endl;

/*     int x1 = parseCommand(input)[0]; int y1 = parseCommand(input)[1];
    int x2 = parseCommand(input)[2]; int y2 = parseCommand(input)[3];
    cout << parseCommand(input)[0] << " " <<parseCommand(input)[1] << endl;
    cout << parseCommand(input)[2] << " " <<parseCommand(input)[3] << endl;
    
    for (int i = 0; i<4; i++)
    {
        cout << parseString("e2-g4")[0] << " " <<parseString("e2-g4")[1] << endl;
        cout << parseString("e2-g4")[3] << " " <<parseString("e2-g4")[4] << endl;
    } */

    return 0;
}
/* int main() {
    string myarray[6] = {"a", "b", "c", "d", "e", "f"};
    string input = "fsgs";
    if (find(begin(myarray), end(myarray), input.substr(0,1)) != end(myarray))
        cout << "It exists";
    else
        cout << "It does not exist";
    return 0;
} */