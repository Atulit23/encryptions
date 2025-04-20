#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

vector<vector<string>> stringToColumnMatrix(string text, int n) {
    vector<vector<string>> matrix(n);
    string curr = "";
    int index = 0;

    for(int i = 0; i < text.size(); i++)  {
        curr += text[i];
        
        if(i%2 == 1) {
            matrix[index].push_back(curr);
            if(index == 3) {
                index = 0;
            } else {
                index++;
            }
            curr = "";
        }
    }

    return matrix;
}

vector<string> getAColumn(vector<vector<string>>& matrix, int column) {
    vector<string> ans;

    for(int i = 0; i < matrix.size(); i++)  {
        ans.push_back(matrix[i][column]);
    }

    return ans;
}

vector<string> shiftLeftByN(vector<string> row, int n, int size){
    vector<string> ans(size, "");
    n = n%size;
    for(int i = 0; i < row.size(); i++) {
        if(i - n < 0) {
            ans[size + (i-n)] = row[i];
        } else {
            ans[i-n] = row[i];
        }
    }

    return ans;
}

vector<string> generateG(vector<string>& row, int n) { // n--> shift by "n"
    vector<string> ans;
    // shift by n
    ans = shiftLeftByN(row, n, row.size());

    return ans;
}


void AES() {
    string plaintext = "00112233445566778899aabbccddeeff";
    string key = "000102030405060708090a0b0c0d0e0f";

    // generate column matrices
    vector<vector<string>> textMatrix = stringToColumnMatrix(plaintext, 4);
    vector<vector<string>> keyMatrix = stringToColumnMatrix(key, 4);
    
    vector<string> w0 = getAColumn(textMatrix, 0);
    vector<string> w1 = getAColumn(textMatrix, 1);
    vector<string> w2 = getAColumn(textMatrix, 2);
    vector<string> w3 = getAColumn(textMatrix, 3);

    vector<string> w4 = generateG(w3, 3);

    for(int i = 0; i < 4; i++) {
        cout << w4[i] << endl;
    }
    
}

int main () {
    AES();
    return 0;
}