// Receiver for hamming code, correct only 1 bit error

#include <iostream>
#include <cmath>
using namespace std;

string decode(string message, int &error_bit);
string encode(string message);

int main()
{
    string message;
    cout << "Enter the message received: ";
    getline(cin, message);

    int error_bit = 0;
    string decoded_message = decode(message, error_bit);

    if (error_bit == 0)
        cout << "No error in the message received\n";
    else 
        cout << "Error in bit " << error_bit << "\nCorrecting Message...\n";

    cout << "Decoded message is " << decoded_message << endl;

    return 0;
}

string decode(string message, int &error_bit)
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
    int counter = 0;
    for (int i = 0; i < totalbits; i++)
    {
        if (correct_encoded_msg[i] != message[i])
            counter += i+1;
    }

    if (counter != 0)
    {
        message[counter-1] = message[counter-1] == '1' ? '0' : '1';
        data_message = "";
        // extract data from message
        for (int i = 0; i < totalbits; i++)
            if (!(log2(i+1) == int(log2(i+1))))
                data_message += message[i];
    }

    error_bit = counter;
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

/*
Enter the message received: 101001001111
No error in the message received
Decoded message is 10101111
----------------------
Enter the message received: 101001101111    
Error in bit 7
Correcting Message...
Decoded message is 10101111
*/