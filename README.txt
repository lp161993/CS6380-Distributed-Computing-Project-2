README file:

This code is used to identify Leader among a set of asynchronous processes using LCR algorithm. 
The input.dat file contains n- the num of asynchronous processes and the process ids. 

In the main() function of the code, we read the input.dat file to find n. Then the main function initiates the threads which runs asynchronously. 

In general, once the master creates the thread, each thread separately runs for n rounds. In round 0, it pushes its own ID to the output queue. IN subsequent rounds, it processes the incoming IDs and if the ID is high, it pushes the incoming ID or pushes 0. During the push operation, a delay is used to infuse the asynchronous behavior.

The outgoing and incoming messages are processed according to the LCR algorithm and after n rounds, the leader is identified and all threads output their ID along with their leader.

Run the code: Compile AsynchLCR.cpp, and run the code. If you want to change the input, open input.dat file and alter the value of n and their respective process IDs.

Sample input:
10
21 84 22 67 34 44 71 79 82 13

Sample Output:


My ID is 13 and my leader is 84
My ID is 71 and my leader is 84
My ID is 67 and my leader is 84
My ID is 21 and my leader is 84
My ID is 82 and my leader is 84
My ID is 34 and my leader is 84
My ID is 79 and my leader is 84
My ID is 44 and my leader is 84
My ID is 22 and my leader is 84
My ID is 84 and my leader is 84

--------------------------------
Process exited after 0.46 seconds with return value 0
Press any key to continue . . .

Note: If we observe the order of Process IDs in the input and the order in the output are different, exhibiting asynchronous behavior.
