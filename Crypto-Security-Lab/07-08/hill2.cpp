

#include <iostream>
using namespace std;


void inverseMatrix(int (&matrix)[2][2]){
    int a = matrix[0][0];
    int b = matrix[0][1];
    int c = matrix[1][0];
    int d = matrix[1][1];
    int det = (a*d) - (b*c);
    matrix[0][0] = (((d+26)%26)*3)%26;
    matrix[0][1] = (((-b+26)%26)*3)%26;
    matrix[1][0] = (((-c+26)%26)*3)%26;
    matrix[1][1] = (((a+26)%26)*3)%26;
}

int main(){
    string key, plainText, encryptedText;
    plainText = "";

    cout << endl << "NOTE: KINDLY USE UPPERCASE THROUGHOUT THE PROGRAM !!!" << endl << endl;
    int shift=65;

    cout << "Enter 4 letter keyword : ";
    cin >> key;
    while(key.length()!=4){
        cout << "Enter 4 letter keyword : ";
        cin >> key;
    }

    cout << "Enter Encrypted Text: ";
    cin >> encryptedText;

    for(int i=0; i<key.length(); i++){
        key[i]-=shift;
    }
    for(int i=0; i<encryptedText.length(); i++){
        encryptedText[i]-=shift;
    }

    int keyMatrix[2][2] = {{0,0},{0,0}};
    int ptr = 0;
    for(int i=0; i<2; i++){
        for(int j=0; j<2; j++){
            keyMatrix[j][i] = key[ptr++];
        }
    }

    inverseMatrix(keyMatrix);

    if(encryptedText.length()%2==1) encryptedText = encryptedText+"X";
    for(int i=0; i<encryptedText.length(); i+=2){
        int temp[] = {encryptedText[i], encryptedText[i+1]};
        for(int i=0; i<2; i++){
            int sum = 0;
            for(int j=0; j<2; j++){
                sum+=keyMatrix[i][j]*temp[j];
            }
            sum = sum%26;
            sum+=shift;
            plainText+=sum;
        }
    }
    cout << "Plain Text : " << plainText << endl;
    return 0;
}