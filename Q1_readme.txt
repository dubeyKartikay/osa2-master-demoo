In Q1.1
    pthread_create was used to create the different threads
    along with pthread_setschedparam to set the sceduling policy and also set the priority
    pthread_getschedparam was also used to verify whether the correct policy was instituted with
    the correct priority

    For the histogram
    Keeping everything constant, we first changed the priority of FIFO through 6 iterations
    1 , 5, 10 , 20 ,60 ,99
    and logged the times in a file called 'results'
    the main.py script then reads the file and makes an histogram for it



In Q1.2
    fork is called in a for loop 3 times to spawm 3 child processes all of which run the
    complie.sh script present in the folder,
    defalut priority is used and again stored in results
    main.py reads results and print out an histogram


Obersvations:
    FIFO already takes close to maximum cpu time, hen increasing its priority had marginal results
    RR on the other hand benefitted greatly from increasing its priority
    OTHER was the slowest as it's nice value was 0.
    FIFO was the fastest
    RR was in the middle
    OTHER was the slowest
