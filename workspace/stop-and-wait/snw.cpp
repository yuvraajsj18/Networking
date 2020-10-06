// Stop and wait ARQ implementation 

#include <iostream>
#include <string>
using namespace std;

void transmission_cases(int case_, int frame_num, string data);

int main()
{
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

    while (true)
    {
        cout << "\nChoose a scenerio:\n";
        cout << "1. Successful transmission of all frames.\n"
            << "2. Frame lost in network\n"
            << "3. Acknowledgement lost in network\n"
            << "4. Exit\n";

        int choice;
        cout << "Choice: ";
        cin >> choice;

        cout << "\n";
        switch(choice)
        {
            case 1:
            {
                for (int i = 0; i < num_frames; i++)
                    transmission_cases(1, i + 1, frames[i]);
            }
            break;
            case 2:
            {
                int lost_frame;
                cout << "Enter frame to lost: ";
                cin >> lost_frame;
                for (int i = 0; i < num_frames; i++)
                {
                    if (i + 1 == lost_frame)
                    {
                        transmission_cases(2, i + 1, frames[i]);
                        transmission_cases(1, i + 1, frames[i]);
                    }
                    else
                        transmission_cases(1, i + 1, frames[i]);
                }
            }
            break;
            case 3:
            {
                int lost_ack;
                cout << "Enter acknowledgment to lost: ";
                cin >> lost_ack;
                for (int i = 0; i < num_frames; i++)
                {
                    if (i + 2 == lost_ack)
                    {
                        transmission_cases(3, i + 1, frames[i]);
                        transmission_cases(1, i + 1, frames[i]);
                    }
                    else 
                        transmission_cases(1, i + 1, frames[i]);
                }
            }
            break;
            case 4:
                cout << "Exiting...";
                exit(0);
            break;
            default:
                cout << "Invalid Option\n";
        }
    }

    return 0;
}

void transmission_cases(int case_, int frame_num, string data)
{
    switch(case_)
        {
            case 1:
                cout << "Frame " << frame_num << " with data " << data << " successfully received\n";
                cout << "Acknowledgement " <<  frame_num + 1 << " successfully received\n\n";
            break;
            case 2:
                cout << "Frame " << frame_num << " with data "<< data << " lost in network\n";
                cout << "No acknowledgement received\n";
                cout << "Timer Expired, Resending\n\n";
            break;
            case 3:
                cout << "Frame " << frame_num << " with data "<< data << " successfully received\n";
                cout << "Acknowledgement " << frame_num + 1 << " lost in network\n";
                cout << "Timer Expired, Resending\n\n";
            break;
        }
        cout << "\n";
}


/*
Stop and wait ARQ
Enter number of frames to send: 4
Enter data in each frame:
Data in frame 1: 100
Data in frame 2: 200
Data in frame 3: 300
Data in frame 4: 400

Choose a scenerio:
1. Successfull transmission of all frames.
2. Frame lost in network
3. Acknowledgement lost in network
4. Exit
Choice: 1

Frame 1 with data 100 successfully received
Acknowledgement 2 successfully received


Frame 2 with data 200 successfully received
Acknowledgement 3 successfully received


Frame 3 with data 300 successfully received
Acknowledgement 4 successfully received


Frame 4 with data 400 successfully received
Acknowledgement 5 successfully received



Choose a scenerio:
1. Successfull transmission of all frames.
2. Frame lost in network
3. Acknowledgement lost in network
4. Exit
Choice: 2

Enter frame to lost: 2
Frame 1 with data 100 successfully received
Acknowledgement 2 successfully received


Frame 2 with data 200 lost in network
No acknowledgement received
Timer Expired, Resending


Frame 2 with data 200 successfully received
Acknowledgement 3 successfully received


Frame 3 with data 300 successfully received
Acknowledgement 4 successfully received


Frame 4 with data 400 successfully received
Acknowledgement 5 successfully received



Choose a scenerio:
1. Successfull transmission of all frames.
2. Frame lost in network
3. Acknowledgement lost in network
4. Exit
Choice: 3

Enter acknowledgment to lost: 3
Frame 1 with data 100 successfully received
Acknowledgement 2 successfully received


Frame 2 with data 200 successfully received
Acknowledgement 3 lost in network
Timer Expired, Resending


Frame 2 with data 200 successfully received
Acknowledgement 3 successfully received


Frame 3 with data 300 successfully received
Acknowledgement 4 successfully received


Frame 4 with data 400 successfully received
Acknowledgement 5 successfully received



Choose a scenerio:
1. Successfull transmission of all frames.
2. Frame lost in network
3. Acknowledgement lost in network
4. Exit
Choice: 4

Exiting...⏎  
*/
