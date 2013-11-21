// ------------------------------------------
// CMPT 300 Project 2
// blockedqueue.cpp (file 7 of 9)
//
// Erik Schultz, eriks@sfu.ca, 301034882
// Ian Stewart, iastewar@sfu.ca, 301190316
// Yixuan Li, yixuanl@sfu.ca, 301191905
// ------------------------------------------

#include "blockedqueue.h"

    void blockedqueue::Block(process* a)
    {
        notready.push_back(a);
    }

    void blockedqueue::IOFinish(int position)
    {
        process* temp = notready[position];
        notready.erase(notready.begin()+position);
        ready.push(temp);
    }

    process* blockedqueue::Unblock()
    {
        process* temp = ready.front();
        ready.pop();
        return temp;
    }


