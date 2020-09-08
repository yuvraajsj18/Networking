/*
 *  Calculate CRC message transmitted by sender
 *  G(x) = 1011, polynomial function
 *  r = 3, number of checkbits
 *  m, message to send, entered by user, 6 bits + 3 bits r
 */

#include <iostream>
#include <string>
using namespace std;

#define message_bits 6  // bits in m
#define checkbits 3 // r

string mod2division(string message);
int ctoi(char ch);
char itoc(int i);
bool message_is_valid(string message);\


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

    string remainder = mod2division(message);

    string encoded_msg = message + remainder;

    cout << "Message to send is " << encoded_msg << endl;

    return 0;
}

string mod2division(string message)
{
    // append r 0's
    for (int i = message_bits; i < message_bits + checkbits; i++)
    {
        message += '0';
    }

    string divisor = "1011";
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