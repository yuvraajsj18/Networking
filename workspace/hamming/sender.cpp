// sender for hamming code

#include <iostream>
#include <string>
#include <cmath>
using namespace std;

string encode(string message);

int main()
{
    string message;
    cout<< "Enter message to send: ";
    getline(cin, message);

    string codeword = encode(message);

    cout << "Encoded message to send: " << codeword << endl;

    return 0;
}


string encode(string message)
{
    int databits = message.length();
    // calculate number of check bits
    int checkbits = 0;
    for (; !(databits + checkbits + 1 <= pow(2, checkbits)); checkbits++);

    string codeword = "";
    int totalbits = databits + checkbits;
    for (int i = 1, j = 0; i <= totalbits; i++)
    {
        if (log2(i) == int(log2(i)))    // if checkbit
            codeword += '?';
        else 
            codeword += message[j++];
    }

    // set checkbits
    for (int i = 0, k = 0; i < totalbits; i++)
    {
        if (codeword[i] == '?')
        {
            int sum = 0;
            for (int j = 0; j < totalbits; j++)
            {
                if ((((j+1)>>k)&1 && i != j))
                {
                    sum += codeword[j] - '0';
                }
            }
            if (sum % 2 == 0)
                codeword[i] = '0';
            else 
                codeword[i] = '1';
            k++;
        }
    }

    return codeword;
}

/*
Enter message to send: 10101111
Encoded message to send: 101001001111
*/

