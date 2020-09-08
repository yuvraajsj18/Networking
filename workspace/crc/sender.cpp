/*
 *  Calculate CRC message transmitted by sender
 *  G(x) = 1011, polynomial function
 *  r = 3, number of checkbits
 *  m, message to send, entered by user, 6 bits + 3 bits r
 */

#include <iostream>
#include <string>
using namespace std;

string encode_crc(string message, string gx);
string mod2division(string message, string gx);
int ctoi(char ch);
char itoc(int i);
bool message_is_valid(string message);

int main()
{
    string message;
    
    // input message
    cout << "Enter message in binary(6 bits): ";
    getline(cin, message);

    if (!message_is_valid(message))
    {
        cout << "Invalid message input" << endl;
        exit(1);
    }

    string gx = "1011";
    string encoded_msg = encode_crc(message, gx);

    cout << "Message to send is " << encoded_msg << endl;

    return 0;
}

string encode_crc(string message, string gx)
{
    int message_bits = message.length();
    int checkbits = gx.length() - 1;
    string padded_msg = message;
    // append r 0's
    for (int i = message_bits; i < message_bits + checkbits; i++)
    {
        padded_msg += '0';
    }

    string remainder = mod2division(padded_msg, gx);

    string encoded_msg = message + remainder;

    return encoded_msg;
}

string mod2division(string message, string gx)
{
    int checkbits = gx.length() - 1;

    string divisor = gx;
    int msg_length = message.length();

    int i = 0;
    while(true)
    {
        for (int j = 0, k = i; j < 4; k++, j++)
        {
            message[k] = itoc(ctoi(message[k]) ^ ctoi(divisor[j]));
        }  
        
        while(message[i++] != '1');
        i--;

        if (stoi(message.substr(0, msg_length - checkbits)) == 0)
            break;
    }

    string remainder = message.substr(msg_length - checkbits, checkbits);
    return remainder;
}

int ctoi(char ch)
{
    return ch - '0';
}

char itoc(int i)
{
    return '0' + i;
}

bool message_is_valid(string message)
{
    int msg_len = message.length();
    for (int i = 0; i < msg_len; i++)
    {
        if (message[i] != '1' && message[i] != '0')
            return false;
    }

    return true;
}

/*
    Output:
        Enter message in binary(6 bits): 101010
        Message to send is 101010001
*/