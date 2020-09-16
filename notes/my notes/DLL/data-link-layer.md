# The Data Link Layer

In this article we are going to study design issues of DLL and how DLL handles limitation of the communication channel like errors and finite data rate.

Table of Content:

1. [Review](#review)
2. [Data Link Layer Design Issues](#Data-Link-Layer-Design-Issues)
   1. [Network Layer Services](#Services-provided-to-the-Network-Layer)
      1. Unacknowledged Connectionless Service
      2. Acknowledged Connectionless Service
      3. Acknowledged Connection Oriented Service
   2. [Framing](#framing)
      1. Frames
      2. Framing Methods
         1. Character Count Method
         2. Flag Bytes with Byte Stuffing
         3. Flag Bits with Bit Stuffing
   3. [Error Control](#Error-Control)
   4. [Flow Control](#Flow-Control)
      1. Feedback-based flow control
      2. Rate-based flow control
3. [Error Detection and Correction](#Error-Detection-and-Correction)

## Review

The data link layer is responsible for the **node to node**(or hop to hope) delivery of the message. It makes sure data transfer is error-free from one node to another, over the physical layer.

The data link layer is concerned for delivery on the same network between two directly connected nodes like in LAN.

![image-20200915112409933](/home/yuvrajsj18/.config/Typora/typora-user-images/image-20200915112409933.png)**The data link layer is responsible for moving frames from one hop to the next.**

Functions of the Data Link Layer:

1. **Framing** - The data link layer divides the stream of bits received from the network layer into manageable *data units* called **frames**.

2. **Physical Addressing** - After creating frames, DLL adds **physical addresses**(MAC address) of the sender and receiver in the header of each frame.

   - If the frame is intended for a system outside the sender's network, the receiver address is the address of the device that connects the network to the next one.

3. **Flow Control** - If the rate at which the data are *absorbed* by the receiver is less than the rate at which data are *produced* in the sender, the data link layer imposes a flow control mechanism to avoid overwhelming the receiver.

   Example - If the sender can send 5 frames per second but the receiver can only receive 3 frames per second the data link layer will reduce the frames from 5 to 3 per second on the sender's side.

4. **Error Control** - The DLL adds **reliability** to the physical layer by adding mechanisms to detect and retransmit damaged or lost frames. It also uses a mechanism to recognize duplicate frames.

   **Error Control is achieved through a trailer added to the end of the frame**.

5. **Access Control** - When two or more devices are connected to the same link, data link layer protocols are necessary to determine which device has control over the link at any given time.

   ![image-20200915112426110](/home/yuvrajsj18/.config/Typora/typora-user-images/image-20200915112426110.png)



## Data Link Layer Design Issues

The function of DLL includes:

1. Providing a well-defined service interface to the network layer.
2. Dealing with transmission errors.
3. Regulating the flow of data so that slow receivers are not swamped by fast senders.

To accomplish these goals, DLL uses frames to encapsulate the packets it gets from Network Layer.

Each Frame has a frame header, a payload field(data), and a frame trailer.

![Relationship between packet and frame](/home/yuvrajsj18/.config/Typora/typora-user-images/image-20200915113425613.png)

There are four issues that DLL needs to handle:

1. Network Layer Services
2. Framing
3. Error Control
4. Flow Control

Let's discuss each

### Services provided to the Network Layer

- Principle service function of the data link layer is to transfer the data from the network layer on the source machine to the network layer on the destination machine.

  - Process in the network layer that hands some bits to the data link layer for transmission.
  - Job of data link layer is to transmit the bits to destination machine so they can be handed over to the network layer there.

  ![Virtual and Actual Data Path](/home/yuvrajsj18/.config/Typora/typora-user-images/image-20200915113839246.png)

- Possible Services Offered - 
  - Unacknowledged connectionless service.
    - It consist of having the *source machine send independent frames to the destination machine without having the destination machine acknowledge them.*
    - No logical connection is established beforehand or release afterwards.
    - Lost frames are not recovered.
    - Example - Ethernet, Voice over IP, in all communication channel where real time operation is more important that quality of transmission.
  - Acknowledged connectionless service.
    - *Each frame send by the DLL is acknowleged and the sender knows if a specific frame has been recieved or lost.*
    - No logical connection is established.
    - Typically the protocol uses a *specific time period that if has passed without getting acknowledgment it will re-send the frame.*
    - This service is useful for communication when an unreliable channel is used (Ex. 802.11 WiFi).
    - Network layer does not know frame size of the packets and other restrictions of the data link layer. Hence It becomes necessary for DLL to have some mechanism to optimize the transmission.
  - **Acknowledged connection-oriented service**.
    - Source and destination establish a connection first.
    - Each frame sent is numbered.
      - DLL guarantees that each frame sent is indeed received.
      - It guarantees that *each frame is received only once* and that all frames are received in the correct order.
    - Examples:
      - Satellite channel communication.
      - Long-distance telephonic communication.
    - Three distinct phases:
      1. **Connection is established** by having both side initialize variables and counters needed to keep track of which frames have been received and which once have not.
      2. **One or more frames are transmitted**.
      3. Finally, **the connection is released** - freeing up the variables, buffers, and other resources used to maintain the connection.

### Framing

- To provide services to the network layer, the data link layer must use the service provided by the physical layer.

  - Physical layer will try to deliver the bit stream received from DLL to the destination, errors may occur in the process.
  - Errors could be:
    - Number of bits received does not match number of bits transmitted.
    - Bits may have different values.
  - It is DLL's job to correct this errors if necessary.

- Transmission of the data link later starts with breaking up the bit stream

  - into **discrete frames**
  - *computation of a checksum* for each frame
  - Include the *checksum into the frame* before it is transmitted.

- Framing is more difficult than one could think!

- Process of wrapping data with certain info before sending out

  ![A frame](/home/yuvrajsj18/.config/Typora/typora-user-images/image-20200916142832904.png)

- A frame typically consists of

  - *Flag* - indication for start and end of a frame.
  - *Header* - source/destination addresses, as well as other control information.
  - *Data* - actual data received from the network layer.
  - *Trailer* - error detection/correction code

  #### Framing Methods

- Character Count.

- Flag bytes with byte stuffing.

- Starting and ending flags, with big stuffing.

  ##### <u>Character Count Method for Framing</u>

  - It uses a *field in the header to specify the number of bytes in the frame*.

  - Once the header information is being received it will be used to determine end of the frame.

  - When the data link layer at the destination sees the character count, it knows how many characters follow and hence where the end of the frame is.

  - **Trouble with this algorithm** is that when the count is incorrectly received the destination will get out of sync with transmission.

    - For example if the character count of 5 in the second frame becomes a 7, the destination will get out of sync and will not be able to locate the start of the next frame.

    ![character count method](/home/yuvrajsj18/.config/Typora/typora-user-images/image-20200916151838452.png)

  - Even if the checksum is incorrect, so the destination knows that the frame is bad, it still has no way of telling where the next frame starts.

  - Sending a frame back to the source asking for retransmission does not help either, since the destination does not know how many characters to skip over to get to the start of the retransmission.

  - For this Reason, this method is rarely used.

  ##### <u>Flag Bytes with byte stuffing framing method</u>

- This method gets around the boundary detection of the frame by having each frame appended by the *frame start and frame end special bytes*.

- These special bytes are called **Flag Bytes**.

- In this way, if the receiver ever loses sync, it can just search for the flag byte to find the end of the current frame.

- Two consecutive flag bytes indicate the end of one frame and start of another frame.

- If flag appears in the data field then an escape sequence of bits is used to indicate the 'flag' as part of data, also if ESC appears in data another ESC is used to escape it.
  ![Byte Stuffing](/home/yuvrajsj18/.config/Typora/typora-user-images/image-20200916152744334.png)

- ![Sending and recieving frame with byte stuffing](/home/yuvrajsj18/.config/Typora/typora-user-images/image-20200916153027813.png)

- A major **disadvantage** of using this framing method is that it is closely tied to the use of 8 bit characters.

  Not all character codes use 80bit characters. For example, UNICODE uses 16-bit.

  - As network developed, the disadvantages of embedding the character code length in the framing mechanisms became more and more obvious, so a new technique had to be developed to allow arbitrary sized characters. 

  ##### <u>Flag Bits with Byte Stuffing Framing Method</u>

- This methods achieves the same thing as Byte Stuffing method by using Bits (1 Bit) instead of Bytes (8 bits).

- It was developed for high level data link control protocol(HDLC) protocol.

- Each frame begins and ends with a special bit pattern:

  - `01111110` or `0x7E` = Flag Byte
  - Whenever the sender's data link layer encounters *five consecutive 1s* in the data it automatically stuffs a *0 bit* into the outgoing bit stream.
  - USB uses bit stuffing.

  ![Bit Stuffing](/home/yuvrajsj18/.config/Typora/typora-user-images/image-20200916161202954.png)

  ![Bit stuffing and unstuffing](/home/yuvrajsj18/.config/Typora/typora-user-images/image-20200916161243809.png)

- With Bit Stuffing, the boundary between two frames can be unambiguously recognized by the flag pattern.
- Thus, if the receiver loses track of where it is, then all it has to do is scan the input for flag sequences, since they can only occur at frame boundaries and never within the data. 

### Error Control

- After solving the marking of the of the frame with start and end. The data link layer has to handle eventual errors in transmission.
  - Ensuring that *all frames are delivered* to the network layer at the destination and *in proper order.*
- Suppose that the sender just kept outputting frames without regard to whether they were arriving properly.
- This might be fine for unacknowledged connectionless service, but would most certainly be not fine for reliable connection-oriented service.
- The usual way to ensure reliable delivery is to provide the sender with *some feedback* about what is happening at the other end of the line. Typically, the protocol calls for the receiver to send back *special control frames bearing positive or negative acknowledgement about the incoming frame*.
- If the sender receives *positive acknowledgement* it will know that *the frame has arrived safely*.
- On the other hand, a negative acknowledgement means that something has gone wrong, and the frame must be retransmitted.
- An additional complication comes from the possibility that hardware troubles may cause a frame to vanish completely.
  - In this case, the receiver will not react at all, since it has no reason.
  - And, the sender will hang forever in wait of a positive or negative acknowledgement.
  - This possibility is dealt with by **introducing timers** into the data link layer.
- When the sender transmit a frame, it generally also starts a **timer**. The timer is *set to expire after an interval long enough for the frame to reach the destination, be processed there, and have the acknowledgement propagate back to sender.*
- Normally, the frame will be correctly received and the acknowledgement will get back before the timer runs out, in which case the timer will be cancelled.
- However, if either the frame or acknowledgement is lost, the timer will go off, alerting the sender to a potential problem. The solution is just to *transmit the frame again*.
- To prevent the receiver to accept the same frame multiple times, **sequence numbers are assigned to the outgoing frames** so that the receiver can distinguish retransmission from originals.

### Flow Control

- Another important design issue that occurs in the data link later is what to do with a sender that systematically wants to transmit frames faster than the receiver can accept them.
- The situation can occur when the sender is running on a fast(or lightly loaded) computer and the receiver is running on a slow (or heavily loaded) machine.
- Two approaches are used to handle flow control:
  1. **Feedback-based Flow Control**
     - The receiver sends back information to the sender giving it permission to send more data or atleast telling the sender how the receiver is doing.
     - when a connection is set up, the receiver might say: *''You may send me n frames now, but after they have been sent, do not send any more until I have told you to continue.''* 
  2. **Rate-based Flow Control**
     - The protocol has a built-in mechanism that limits the rate at which sender may transmit data, without feedback from the receiver



## Error Detection and Correction













