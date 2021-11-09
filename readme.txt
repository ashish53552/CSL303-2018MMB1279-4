Submitter name:Ashish Kaushik

Roll No.:2018MMB1279

Course:CS303


Please Refer to: CS303-2018MMB1279-4-results.pdf for the results table
=================================


1. What does this program do

The programme is used to simulate various disk scheduling algorithms such as Random, SCAN, C-SCAN, FIFO, SSTF.

2. A description of how this program works (i.e. its logic)

The main programme comprises of four modules disk_scheduler.h, d_types.h, process_request.h, headers.h

The headers file comprises all the global and structures used throughout the code;

process_request file takes in the value of struct request and returns the time taken which contains the
seek time and read/write time respectively.

Total time = Ts(Seek Time)+ Rotational Latency  + Transfer time

A global variable which defines the starting location of the head is created using a struct which contains the 
value of platter, cylinder, sector before which the disk head is pointing.

After each request the head location is updated.

All the disk scheduling algorithms return a new queue array accordingly following which the requests are exectuted.

Disk scheduling algorithms

Random:
    -Pick a random index from the array
    -Mark it and put in the final queue to be exectued
    -Repeat until finished

FIFO:
    -Process in the order of arrival

SCAN:
    - starts from the initial location to the end[higher track] and then it moves back till all the requests are processed.

C-SCAN
    -starts from current till max comes back to 0 goes to inc side till all are processed.

SSTF:
    - At each iteration find which request takes the shortest seek time and process request

All are implemented using arrays and a done array which is a boolean and takes care of which requests are finished

Throughput and other variables are calculated using standard formulae the results of which are 
given in: CS303-2018MMB1279-4-results.pdf

/*Each algo throughput is tested on 1000 requests */

3. How to compile and run this program

-----------------------------------------------------------------------------------------------
Compile
-----------------------------------------------------------------------------------------------
main file:
gcc -o client client.c -lpthread -ldl -lm
./client


Example :
gcc -o client client.c -lpthread -ldl -lm
./client

Enter Rotational speed of disk, r revolutions per minute
60
Enter Average seek time, Ts in ms
5
Enter Sector size, N in bytes
512

Output:
-------------------------FIFO--------------------------
Throughput (requests/s)= 0.999601
<Avg.= 1000.399597, Min.= 51.250000, Max.= 1954.166748, StdDev.= 420.520752> of response time (ms)


-------------------------Random--------------------------
Throughput (requests/s)= 1.006133
<Avg.= 993.904480, Min.= 56.666668, Max.= 1959.166748, StdDev.= 390.017029> of response time (ms)


-------------------------SSTF--------------------------
Throughput (requests/s)= 1.767165
<Avg.= 565.878174, Min.= 50.000000, Max.= 1052.916626, StdDev.= 311.295166> of response time (ms)


-------------------------SCAN--------------------------
Throughput (requests/s)= 0.986273
<Avg.= 1013.918518, Min.= 50.000000, Max.= 1950.000000, StdDev.= 405.081726> of response time (ms)


-------------------------C-SCAN--------------------------
Throughput (requests/s)= 0.986524
<Avg.= 1013.660278, Min.= 50.000000, Max.= 1950.000000, StdDev.= 404.167053> of response time (ms)


unit test:
gcc -o unit_test unit_test.c -lpthread -ldl -lm
./unit_test

*prints the request generated array and queue array after each algorithm for testing purposes each array element contains the value
of struct location which is defined in d_types.h*/


