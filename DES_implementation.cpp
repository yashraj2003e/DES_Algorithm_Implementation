#include<bits/stdc++.h>
using namespace std;

string plainText;
string key;
string L0;
string R0;

vector<vector<string>> keyRotations;
vector<vector<string>> permutedChoiceValues;
vector<vector<string>> rightInputKeys;
vector<vector<string>> expandedRightInputKeys;
vector<vector<string>> XOROutput;
vector<vector<string>> permutedChoice2Values;
vector<vector<string>> sboxOutput;
vector<vector<string>> newRvalues;
vector<vector<string>> newLvalues;

unordered_map<char,string> myMap = {
        {'0',"0000"},{'1',"0001"},{'2',"0010"},
        {'3',"0011"},{'4',"0100"},{'5',"0101"},
        {'6',"0110"},{'7',"0111"},{'8',"1000"},
        {'9',"1001"},{'A',"1010"},{'B',"1011"},{'C',"1100"},
        {'D',"1101"},{'E',"1110"},{'F',"1111"}};

int initialInputPermutation[8][8] = {
        {58,50,42,34,26,18,10,2},
        {60,52,44,36,28,20,12,4},
        {62,54,46,38,30,22,14,6},
        {64,56,48,40,32,24,16,8},
        {57,49,41,33,25,17,9,1},
        {59,51,43,35,27,19,11,3},
        {61,53,45,37,29,21,13,5},
        {63,55,47,39,31,23,15,7}};

int finalInputPermutation[8][8] = {
        {40,8,48,16,56,24,64,32},
        {39,7,47,15,55,23,63,31},
        {38,6,46,14,54,22,62,30},
        {37,5,45,13,53,21,61,29},
        {36,4,44,12,52,20,60,28},
        {35,3,43,11,51,19,59,27},
        {34,2,42,10,50,18,58,26},
        {33,1,41,9,49,17,57,25}};

//int finalInputPermutation[8][8] = {{}};

int permutedChoice1C[4][7] = {
        {57,49,41,33,25,17,9},
        {1,58,50,32,34,26,18},
        {10,2,59,51,43,35,27},
        {19,11,3,60,52,44,36}};

int permutedChoice1D[4][7] = {
        {63,55,47,39,31,23,15},
        {7,62,54,46,38,30,22},
        {14,6,61,53,45,37,29},
        {21,13,5,28,20,12,4}};

int permutedChoice2[8][6] = {
        {14,17,11,24,1,5},
        {3,28,15,6,21,10},
        {23,19,12,4,26,8},
        {16,7,27,20,13,2},
        {41,52,31,37,47,55},
        {30,40,51,45,33,48},
        {44,49,39,56,34,53},
        {46,42,50,36,29,32}
};


int S1[4][16] = {
        {14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
        {0,15,7,3,14,2,13,1,10,6,12,11,9,5,3,8},
        {4,1,14,8,13,6,2,11,15,12,9,7,13,10,5,0},
        {15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13},
};

int S2[4][16] = {
        {15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},
        {3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},
        {0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},
        {13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}
};

int S3[4][16] = {
        {10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},
        {13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},
        {13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},
        {1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}
};

int S4[4][16] = {
        {7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},
        {13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},
        {10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},
        {3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}
};

int S5[4][16] = {
        {2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},
        {14,11,2,12,4,7,14,1,5,0,15,10,3,9,8,6},
        {4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},
        {11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}
};

int S6[4][16] = {
        {12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},
        {10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},
        {9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},
        {4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}
};

int S7[4][16] = {
        {4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},
        {13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},
        {1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},
        {6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}
};

int S8[4][16] = {
        {13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},
        {1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},
        {7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},
        {2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}
};

vector<pair<int,int>> expansionBoxBits = {{32,5},{4,9},{8,13},
                                          {12,17},{16,21},{20,25},
                                          {24,29},{28,1}};

int dBox[4][8] = {
        {16,7,20,21,29,12,28,17},
        {1,15,23,26,5,18,31,10},
        {2,8,24,14,32,27,3,9},
        {19,13,30,6,22,11,4,25}
};


// DES IMPLEMENTATION

string process(string& plainText1) {
    string res;
    int i = 0;
    while(i<plainText1.size()) {
        res+=myMap[plainText1[i]];
        i++;
    }
    return res;
}

string decimalToBinary(string inputText) {
    string BinaryValue;
    int val = stoi(inputText);
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
    for(int i=0;i<4-BinaryValue.size();i++) {
        f+='0';
    }
    reverse(BinaryValue.begin(),BinaryValue.end());
    return f+BinaryValue;
}

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
    for(char i : plainText1) {
        result+=decimalToBinaryASCII((int)i);
    }
    return result;
}

string binaryToHex(string inputText) {
    string text;
    string result;
    for(char i : inputText) {
        text+=i;
        if(text.size()==4) {
            for(auto& it:myMap) {
                if(it.second == text) {
                  result+=string(1,it.first);
                  break;
                }
            }
            text="";
        }
    }
    return result;
}

string permute(string& inputText) {
    string permutedString;
    for(auto & i : initialInputPermutation) {
        for(int j : i) {
            permutedString+=inputText[j-1];
        }
    }
    return permutedString;
}

string keypermute1(string& inputKey,int side) {
    string permutedKey;
    for(auto& i:side== 0 ? permutedChoice1C : permutedChoice1D) {
        for(auto& j:i) {
            permutedKey+=inputKey[j-1];
        }
    }
    return permutedKey;
}

string keypermute2(string& inputKey) {
    string permutedKey;
    for(auto & i : permutedChoice2) {
        for(int j : i) {
            permutedKey+=string(1,inputKey[j - 1]);
        }
    }
    return permutedKey;
}

string shiftLeftByOne(string& inputText) {
    return inputText.substr(1,28)+string(1,inputText[0]);;
}

string shiftLeftByTwo(string& inputText) {
    return inputText.substr(2,27)+string(1,inputText[0])+string(1,inputText[1]);
}

string expand(string& r0) {
    string result;
    int x = 0;
    for(int i=0;i<8;i++) {
        int first = expansionBoxBits[i].first;
        int second = expansionBoxBits[i].second;
        result+=string(1, r0[first - 1]);
        result+=r0.substr(x, 4);
        x+=4;
        result+=string(1, r0[second - 1]);
    }
    return result;
}

int binaryToDecimal(string inputText) {
    int result = 0,multiply=1;
    int i = (int)inputText.size()-1;
    while(i>-1) {
        result+=((inputText[i]-'0') * multiply);
        multiply*=2;
        i--;
    }
    return result;
}

void DES(int round,string& KL0,string& KR0,string& L0,string& R0,int& rounds) {
    string XOR_value,newLeftVal,SBoxOutput,reducedXOR;
    vector<string> EachRoundRotation;

    if(round==1 || round==2 || round==9 || round==16) {
        cout<<"Left Shifting Left and Right Bits of Key by One: (28 bits)"<<endl;
        KL0 = shiftLeftByOne(KL0);
        KR0 = shiftLeftByOne(KR0);
        cout<<KL0<<endl<<KR0<<endl;
    }
    else {
        cout<<"Left Shifting Left and Right Bits of Key by Two: (28 bits)"<<endl;
        KL0 = shiftLeftByTwo(KL0);
        KR0 = shiftLeftByTwo(KR0);
        cout<<KL0<<endl<<KR0<<endl;
    }



    string K = KL0+KR0;
    cout<<"Adding both sides of Key: (56 bits)"<<endl;
    cout<<K<<endl;

    keyRotations.push_back({K});

    string prevR0 = R0;
    rightInputKeys.push_back({R0});
    K = keypermute2(K);
    permutedChoiceValues.push_back({K});
    cout<<"Permutation 2 of key: (48 bits)"<<endl;
    cout<<K<<endl;
    permutedChoice2Values.push_back({K});
    R0 = expand(R0);
    expandedRightInputKeys.push_back({R0});
    cout<<"Output of Right Side of Input Text after Expansion-P box: (48 bits)"<<endl;
    cout<<R0<<endl;

    for(int i=0;i<48;i++) {
        XOR_value+=to_string(R0[i]-'0' ^ K[i]-'0');
    }
    XOROutput.push_back({XOR_value});
    cout<<"Result of Cipher Function: "<<endl;
    cout<<XOR_value<<endl;

    for(int i=0;i<48;i+=6) {
        string first = string(1,XOR_value[i]);
        string second = string(1,XOR_value[i+5]);
        int curOutput = binaryToDecimal(XOR_value.substr(i+1,4));
        int val;
        int third = binaryToDecimal((first+second));

        if(i==0) {
            val = S1[third][curOutput];
        }
        else if(i==6) {
            val = S2[third][curOutput];
        }
        else if(i==12) {
            val = S3[third][curOutput];
        }
        else if(i==18) {
            val = S4[third][curOutput];
        }
        else if(i==24) {
            val = S5[third][curOutput];
        }
        else if(i==30) {
            val = S6[third][curOutput];
        }
        else if(i==36) {
            val = S7[third][curOutput];
        }
        else if(i==42) {
            val = S8[third][curOutput];
        }
        reducedXOR+=decimalToBinary(to_string(val));
    }

    cout<<"Output of S-box for Each of 6 bits result of Cipher Function: (32 bits)"<<endl;
    cout<<reducedXOR<<endl;
    sboxOutput.push_back({reducedXOR});

    string straightDBox;

    for(auto & i : dBox) {
        for(int j : i) {
            straightDBox+=reducedXOR[j-1];
        }
    }

    cout<<"Straight D-Box Output (32 bits)"<<endl;
    cout<<straightDBox<<endl;

    reducedXOR = straightDBox;

    for(int i=0;i<32;i++) {
        newLeftVal+=to_string(L0[i]-'0' ^ reducedXOR[i]-'0');
    }

    newRvalues.push_back({newLeftVal});

    cout<<"XOR of Left side and output of Cipher Function: (32 bits)"<<endl;
    cout<<newLeftVal<<endl;

    if(round==8 && rounds==8) {
        string encryptedText,finalText,output = newLeftVal+prevR0;
        for(auto & i : finalInputPermutation) {
            for(int j : i) {
                encryptedText += output[j - 1];
            }
        }
        cout<<endl;
        cout<<"******************************************************************************************************************************************************************************"<<endl;
        cout<<"Encrypted Text in Binary: (64 BITS)"<<endl;
        cout<<encryptedText<<" "<<encryptedText.size()<<endl;

        for(int i=0;i<encryptedText.size();i+=4) {
            finalText+=binaryToHex(encryptedText.substr(i,4));
        }
        cout<<"Encrypted Text in Hexadecimals: (16 LETTERS)"<<endl;
        cout<<finalText<<" "<<finalText.size()<<endl;
        cout<<"******************************************************************************************************************************************************************************"<<endl;
        return;
    }

    if(round==16 && rounds==16) {
        string encryptedText,finalText,output = newLeftVal+prevR0;
        for(auto & i : finalInputPermutation) {
            for(int j : i) {
                encryptedText += output[j - 1];
            }
        }
        cout<<endl;
        cout<<"******************************************************************************************************************************************************************************"<<endl;
        cout<<"Encrypted Text in Binary: (64 BITS)"<<endl;
        cout<<encryptedText<<" "<<encryptedText.size()<<endl;

        for(int i=0;i<encryptedText.size();i+=4) {
            finalText+=binaryToHex(encryptedText.substr(i,4));
        }
        cout<<"Encrypted Text in Hexadecimals: (16 LETTERS)"<<endl;
        cout<<finalText<<" "<<finalText.size()<<endl;
        cout<<"******************************************************************************************************************************************************************************"<<endl;
        return;
    }
    L0 = prevR0;
    newLvalues.push_back({L0});
    R0 = newLeftVal;
    cout<<"New Left Side: "<<endl;
    cout<<L0<<endl;
    cout<<"New Right Side: "<<endl;
    cout<<R0<<endl;
}

int charToDecimal(char it) {
    return (int)(it);
}

int main() {
    #ifndef DES
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    #endif

    string mode;
    cin>>mode;
    int rounds;
    cin>>rounds;


    cin>>plainText>>key;
    cout<<"******************************************************************************************************************************************************************************"<<endl;

    if(mode!="ascii" && (plainText.size()!=16 || key.size()!=16)) {
        cout<<"Please Enter 16 letter key/plain text !";
        return 0;
    }

    //Prepare input text for iteration

    cout<<"Input Text (16 letters): "<<plainText<<endl;
    string binaryText = mode=="ascii" ? processASCII(plainText) : process(plainText);
    cout<<"Binary Text (64 bits): "<<binaryText<<endl;
    string permutedInputText = permute(binaryText);
    cout<<"Result of PC1 (64 bits): "<<endl;
    cout<<permutedInputText<<endl;

    cout<<"Left Side of Input Text (32 bits):"<<endl;
    L0 = permutedInputText.substr(0,32);
    cout<<L0<<endl;
    R0 = permutedInputText.substr(32,32);
    cout<<"Right Side of Input Text (32 bits):"<<endl;
    cout<<R0<<endl;

    /*
      binaryToHex(L0);
      binaryToHex(R0);
    */

    //Prepare input key for iteration

    cout<<"Input key (16 letters): "<<key<<endl;
    string binaryKey = mode=="ascii" ? processASCII(key) : process(key);
    cout<<"Binary Key: (64 bits): "<<binaryKey<<endl;
    string KL0 = keypermute1(binaryKey,0);
    string KR0 = keypermute1(binaryKey,1);
    cout<<"Left Side of Key (28 bits): "<<endl;
    cout<<KL0<<endl;
    cout<<"Right Side of Key (28 bits): "<<endl;
    cout<<KR0<<endl;

    keyRotations.push_back({KL0+KR0});

    /*
        cout<<KL0<<" "<<KL0.size()<<" "<<binaryToHex(KL0)<<endl<<KR0<<" "<<KR0.size()<<" "<<binaryToHex(KR0);
    */


    for(int i=1;i<=rounds;i++) {
        cout<<endl<<"Round: "<<i<<endl;
        DES(i, KL0, KR0, L0, R0,rounds);
    }

    if(rounds!=8) return 0;

    cout<<"******************************************************************************************************************************************************************************"<<endl;
    cout<<endl<<"Message"<<endl;
    for(auto it:plainText) {
        cout<<it<<" "<<charToDecimal(it)<<" "<<decimalToBinaryASCII((charToDecimal(it)));
        cout<<endl;
    }
    cout<<endl;

    cout<<endl<<"Key"<<endl;
    for(auto it:key) {
        cout<<it<<" "<<charToDecimal(it)<<" "<<decimalToBinaryASCII((charToDecimal(it)));
        cout<<endl;
    }
    cout<<endl;

    string K = KL0 + KR0;

    cout<<"Key: ";
    for(int i=0;i<56;i+=7) {
        cout<<K.substr(i,7)<<" ";
    }
    cout<<endl;

    cout<<endl<<"Key Rotations:"<<endl;
    for(int it=0;it<keyRotations.size();it++) {
        for(int i=0;i<keyRotations[it].size();i++) {
            cout<<"K"<<it<<": ";
            for(int k=0;k<keyRotations[it][i].size();k+=7) {
                cout<<keyRotations[it][i].substr(k,7)<<" ";
            }
        }
        cout<<endl;
    }

    cout<<endl<<"Permuted Choice - 2"<<endl;
    for(int it=0;it<permutedChoiceValues.size();it++) {
        for(int i=0;i<permutedChoiceValues[it].size();i++) {
            cout<<"K"<<it+1<<": ";
            for(int k=0;k<permutedChoiceValues[it][i].size();k+=6) {
                cout<<permutedChoiceValues[it][i].substr(k,6)<<" ";
            }
        }
        cout<<endl;
    }

    cout<<endl<<"Message: "<<endl;

    for(int i=0;i<binaryText.size();i+=8) {
        cout<<binaryText.substr(i,8)<<" ";
    }

    cout<<endl;

    cout<<"Initial Permutation: "<<endl;
    for(int i=0;i<permutedInputText.size();i+=8) {
        cout<<permutedInputText.substr(i,8)<<" ";
    }
    cout<<endl;

    int size = (int)expandedRightInputKeys.size();
    cout<<endl;
    for(int i=0;i<size;i++) {

        cout<<endl<<i+1<<endl;

        cout<<"R"<<(i+1)<<":"<<endl;
        for(int j=0;j<rightInputKeys[i].size();j++) {
            for(int k=0;k<rightInputKeys[i][j].size();k+=8) {
                cout<<rightInputKeys[i][j].substr(k,8)<<" ";
            }
            cout<<endl;
        }

        cout<<"E(R"<<(i+1)<<"):"<<endl;
        for(int j=0;j<expandedRightInputKeys[i].size();j++) {
            for(int k=0;k<expandedRightInputKeys[i][j].size();k+=12) {
                cout<<expandedRightInputKeys[i][j].substr(k,12)<<" ";
            }
            cout<<endl;
        }
    }


    cout<<endl;
    for(int i=0;i<size;i++) {


        cout<<"E(R"<<(i+1)<<"):    ";
        for(int j=0;j<expandedRightInputKeys[i].size();j++) {
            for(int k=0;k<expandedRightInputKeys[i][j].size();k+=6) {
                cout<<expandedRightInputKeys[i][j].substr(k,6)<<" ";
            }
            cout<<endl;
        }


        for(int it=0;it<permutedChoice2Values[i].size();it++) {
            cout<<"K"<<i+1<<":       ";
            for(int k=0;k<permutedChoice2Values[i][it].size();k+=6) {
                cout<<permutedChoice2Values[i][it].substr(k,6)<<" ";
            }
            cout<<endl;
        }

        cout<<"K"<<(i+1)<<"+"<<"E(R"<<(i+1)<<"): ";
        for(int it=0;it<XOROutput[i].size();it++) {
            for(int k=0;k<XOROutput[i][it].size();k+=6) {
                cout<<XOROutput[i][it].substr(k,6)<<" ";
            }
            cout<<endl;
        }
        cout<<endl;
    }

    cout<<endl<<"S-box output: "<<endl;
    for(int i=0;i<sboxOutput.size();i++) {
        cout<<"Iteration "<<i+1<<": ";

        for(int j=0;j<sboxOutput[i].size();j++) {
            for(int k=0;k<sboxOutput[i][j].size();k+=4) {
                cout<<sboxOutput[i][j].substr(k,4)<<" ";
            }
            cout<<endl;
        }
    }

    cout<<endl<<"Swapping: "<<endl;
    for(int i=0;i<5;i++) {
        cout<<endl<<"Iteration "<<i+1<<endl;
        cout<<"L(R"<<i+1<<"):"<<endl;
        for(int j=0;j<newLvalues[i].size();j++) {
            for(int k=0;k<newLvalues[i][j].size();k+=8) {
                cout<<newLvalues[i][j].substr(k,8)<<" ";
            }
            cout<<endl;
        }
        cout<<"R(L"<<i+1<<"+f(R"<<i+1<<",K"<<i+2<<"))"<<endl;
        for(int j=0;j<newRvalues[i].size();j++) {
            for(int k=0;k<newRvalues[i][j].size();k+=8) {
                cout<<newRvalues[i][j].substr(k,8)<<" ";
            }
            cout<<endl;
        }
    }



}