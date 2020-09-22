#include <iostream>
#include <cmath>
using namespace std;

string decode(string message);
string encode(string message);

int main()
{
    string message;
    cout << "Enter the message received: ";
    getline(cin, message);

    string decoded_message = decode(message);

    if (decoded_message != "")
        cout << "Decoded message is " << decoded_message << endl;
    else 
        cout << "Message recieved is incorrect" << endl;

    return 0;
}

string decode(string message)
{
    string data_message = "";  
    int totalbits = message.length();
    // extract data from message
    for (int i = 0; i < totalbits; i++)
        if (!(log2(i+1) == int(log2(i+1))))
            data_message += message[i];

    // re-encode the message
    string correct_encoded_msg = encode(data_message);

    // check if correct encoded message is same as recieved message
    for (int i = 0; i < totalbits; i++)
    {
        if (correct_encoded_msg[i] != message[i])
            return "";
    }

    return data_message;
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

