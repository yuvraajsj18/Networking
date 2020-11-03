#include <iostream>
#include <vector>
#include <string>

void simulate_gobackn(int simulate_case, std::vector<std::string> frames, int window_size);

int main()
{
    std::cout << "Go Back N Sliding Window Protocol\n";
    
    int num_frames;
    std::cout << "Enter number of frames to send: ";
    std::cin >> num_frames;

    int window_size;
    std::cout << "Enter window size: ";
    std::cin >> window_size;

    std::vector<std::string> frames(num_frames);
    std::cout << "Enter data for each frame:\n";
    for (int i = 0; i < num_frames; i++)
    {
        std::cout << "Frame " << i + 1 << ": ";
        std::cin >> frames[i];
    }

    while (true)
    {
        std::cout << "\nChoose a case to simulate:\n";
        std::cout << "1. All frames sent successfully\n"
                    << "2. A frame lost in network\n"
                    << "3. An acknowledgement lost in network\n"
                    << "4. Quit\n";

        int choice;
        std::cout << "Choice: ";
        std::cin >> choice;

        switch (choice)
        {
            case 1:
                simulate_gobackn(choice, frames, window_size);

                break;
            
            case 2:
                simulate_gobackn(choice, frames, window_size);

                break;

            case 3:
                simulate_gobackn(choice, frames, window_size);

                break;

            case 4:
                std::cout << "Exiting..\n";
                exit(0);
                
                break;
            
            default:
                std::cout << "Invalid option\n";
                break;
        }
    }

    return 0;
}

void simulate_gobackn(int simulate_case, std::vector<std::string> frames, int window_size)
{
    switch (simulate_case)
    {
    case 1:
    {
            for (int i = 0, seq_num = 1; i < frames.size(); i++, seq_num++)
            {
                std::cout << "Sending frame " << i + 1 << " with ";
                std::cout << "Sequence number: " << seq_num << "\n";

                if (seq_num == window_size)
                    seq_num = 0;
                
                if (seq_num == window_size - 1)
                {
                    std::cout << "Acknowledgement received for frame: " << i + 1 << " with sequence number " << seq_num << "\n";
                    std::cout << "Window slided to the next frame to send with sequence number: " << seq_num + 1 << "\n";  
                }
            }

            std::cout << "All Frames sent successfully\n\n";
    } 
        break;

    case 2:
    {
        int lost_frame;
        std::cout << "Enter number of lost frame: ";
        std::cin >> lost_frame;
        bool lost_once = false;
        
        for (int i = 0, seq_num = 1; i < frames.size(); i++, seq_num++)
        {
            std::cout << "Sending frame " << i + 1 << " with ";
            std::cout << "Sequence number: " << seq_num << "\n";

            if (seq_num == window_size)
                seq_num = 0;

            if (i + 1 == lost_frame - 1)
            {
                std::cout << "Acknowledgement received for frame: " << i + 1 << " with sequence number " << seq_num << "\n";
                std::cout << "Window slided to the next frame to send with sequence number: " << seq_num + 1 << "\n";  
                lost_once = true;
            }
            else if (seq_num == window_size - 1 && lost_once)
            {
                std::cout << "No acknowledgement received for any frame and time out occured\n";
                std::cout << "Resending frames...\n";
                i = lost_frame - 2;
                seq_num = lost_frame - 1;
                lost_once = false;
            }
            else if (seq_num == window_size - 1 && !lost_once)
            {
                std::cout << "Acknowledgement received for frame: " << i + 1 << " with sequence number " << seq_num << "\n";
                std::cout << "Window slided to the next frame to send with sequence number: " << seq_num + 1 << "\n";  
            }
        }
    }
        break;

    case 3:
    {
        int lost_ack;
        std::cout << "Enter number of lost acknowledgment: ";
        std::cin >> lost_ack;
        bool lost_once = false;
        
        for (int i = 0, seq_num = 1; i < frames.size(); i++, seq_num++)
        {
            std::cout << "Sending frame " << i + 1 << " with ";
            std::cout << "Sequence number: " << seq_num << "\n";

            if (seq_num == window_size)
                seq_num = 0;

            if (i + 1 == lost_ack - 1)
            {
                std::cout << "Acknowledgement received for frame: " << i + 1 << " with sequence number " << seq_num << "\n";
                std::cout << "Window slided to the next frame to send with sequence number: " << seq_num + 1 << "\n";  
                lost_once = true;
            }
            else if (seq_num == window_size - 1 && lost_once)
            {
                std::cout << "No acknowledgement received for any frame and time out occured\n";
                std::cout << "Resending frames...\n";
                i = lost_ack - 2;
                seq_num = lost_ack - 1;
                lost_once = false;
            }
            else if (seq_num == window_size - 1 && !lost_once)
            {
                std::cout << "Acknowledgement received for frame: " << i + 1 << " with sequence number " << seq_num << "\n";
                std::cout << "Window slided to the next frame to send with sequence number: " << seq_num + 1 << "\n";  
            }
        }
    }
        break;

    case 4:
    {
        std::cout << "Exiting...\n";
        exit(0);
    }
        break;
    default:
        std::cout << "Invalid option\n";
        break;
    }
}
