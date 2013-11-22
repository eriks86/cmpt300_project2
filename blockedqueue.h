// ------------------------------------------
// CMPT 300 Project 2
// blockedqueue.h (file 6 of 9)
//
// Erik Schultz, eriks@sfu.ca, 301034882
// Ian Stewart, iastewar@sfu.ca, 301190316
// Yixuan Li, yixuanl@sfu.ca, 301191905
// ------------------------------------------

#ifndef BLOCKEDQUEUE_H
#define BLOCKEDQUEUE_H
#include <queue>
#include <vector>

using namespace std;

//Implement the blocked queue with a vector and a queue
class blockedqueue
{
    public:
        void Block(process* a);
        void IOFinish(int position);
        process Unblock();

    private:
        queue<process*> ready;
        vector<process*> notready;
};

#endif
