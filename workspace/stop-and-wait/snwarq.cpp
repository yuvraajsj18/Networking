// Stop and wait ARQ implementation 

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;

int main()
{
    srand(time(0));

    cout << "Stop and wait ARQ\n";

    int num_frames;
    cout << "Enter number of frames to send: ";
    cin >> num_frames;

    string *frames = new string[num_frames];
    cout << "Enter data in each frame:\n";
    cin.ignore();
    for (int i = 0; i < num_frames; i++)
    {
        cout << "Data in frame " << i + 1 << ": ";
        getline(cin, frames[i]);
    }

    cout << "\n";
    for (int i = 0; i < num_frames;)
    {
        int case_ = rand();
        if (case_ % 2 == 0)
            case_ = 1;
        else if (case_ % 3 == 0)
            case_ = 2;
        else
            case_ = 3;

        switch(case_)
        {
            case 1:
                cout << "Frame " << i + 1 << " with data "<< frames[i] << " successfully received\n";
                cout << "Acknowledgement " <<  i + 2 << " successfully received\n\n";
                i++;
            break;
            case 2:
                cout << "Frame " << i + 1 << " with data "<< frames[i] << " lost in network\n";
                cout << "No acknowledgement received\n";
                cout << "Timer Expired, Resending\n\n";
            break;
            case 3:
                cout << "Frame " << i + 1 << " with data "<< frames[i] << " successfully received\n";
                cout << "Acknowledgement " << i + 2 << " lost in network\n";
                cout << "Timer Expired, Resending\n\n";
            break;
        }
        cout << "\n";
    }

    return 0;
}

/*
Stop and wait ARQ
Enter number of frames to send: 3
Enter data in each frame:
Data in frame 1: Hello
Data in frame 2: World
Data in frame 3: Bye

Frame 1 with data Hello succefully received
Acknowledgement 2 lost in network
Timer Expired, Resending


Frame 1 with data Hello lost in network
No acknowledgement received
Timer Expired, Resending


Frame 1 with data Hello successfully received
Acknowledgement 2 successfully received


Frame 2 with data World successfully received
Acknowledgement 3 successfully received


Frame 3 with data Bye successfully received
Acknowledgement 4 successfully received

*/
