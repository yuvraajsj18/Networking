/*
 *  Check CRC message received from sender
 *  G(x) = 1011, polynomial function
 *  r = 3, number of checkbits
 *  m, message received, 6 bits + 3 bits r
 */

#include <iostream>
#include <string>
using namespace std;

bool decode_crc(string messsage, string gx);
string mod2division(string message, string gx);
int ctoi(char ch);
char itoc(int i);
bool message_is_valid(string message);

int main()
{
    string message;
    string gx = "1011";
    
    // input message
    cout << "Enter message received in binary(9 bits): ";
    getline(cin, message);

    if (!message_is_valid(message))
    {
        cout << "Invalid message input" << endl;
        exit(1);
    }

    if (decode_crc(message, gx))
    {
        cout << "Message received without error." << endl;
    }
    else
    {
        cout << "Message received with error" << endl;
    }

    return 0;
}

bool decode_crc(string message, string gx)
{
    string remainder = mod2division(message, gx);

    if (stoi(remainder) == 0)
        return true;
    else
        return false;
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
Output 1:
    Enter message received in binary(9 bits): 101010001
    Message received without error.

Output 2:
    Enter message in binary(9 bits): 101001001            
    Message received with error
*/

