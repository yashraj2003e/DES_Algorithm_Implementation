#include<bits/stdc++.h>
using namespace std;

string decimalToBinaryASCII(int val) {
    string BinaryValue;
    while(val>0) {
        if(val & 1) {
            BinaryValue+=string(1,'1');
        }
        else {
            BinaryValue+=string(1,'0');
        }
        val=val>>1;
    }
    string f;
    for(int i=0;i<8-BinaryValue.size();i++) {
        f+='0';
    }
    reverse(BinaryValue.begin(),BinaryValue.end());
    return f+BinaryValue;
}

string processASCII(string& plainText1) {
    string result;
    for(char & i : plainText1) {
        result+=decimalToBinaryASCII((int)i);
    }
    return result;
}


int main() {
    string f = "AMBARISH";
    string f1;
//    cout<<((int)f[0]);
    cout<<processASCII(f);
//    cout<<f<<" "<<f.size();

}