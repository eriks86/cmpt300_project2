// ------------------------------------------
// CMPT 300 Project 2
// blockedqueue.cpp (file 7 of 9)
//
// Erik Schultz, eriks@sfu.ca, 301034882
// Ian Stewart, iastewar@sfu.ca, 301190316
// Yixuan Li, yixuanl@sfu.ca, 301191905
// ------------------------------------------

#include "blockedqueue.h"

    //Put blocked process into the vector that contains
    //processes that's waiting for I/O
    void blockedqueue::Block(process* a)
    {
        notready.push_back(a);
    }

    //When a process recieves it's I/O, move it from the vector
    //into the queue of processes that can be unblocked
    void blockedqueue::IOFinish(int position)
    {
        process* temp = notready[position];
        notready.erase(notready.begin()+position);
        ready.push(temp);
    }

    //Take the first process of the queue and unblock it
    process* blockedqueue::Unblock()
    {
        process* temp = ready.front();
        ready.pop();
        return temp;
    }


