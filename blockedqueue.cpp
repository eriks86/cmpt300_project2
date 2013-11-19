// ------------------------------------------
// CMPT 300 Project 2
// blockedqueue.cpp (file 7 of 9)
//
// Erik Schultz, eriks@sfu.ca, 301034882
// Ian Stewart, iastewar@sfu.ca, 301190316
// Yixuan Li, yixuanl@sfu.ca, 301191905
// ------------------------------------------

#include blockedqueue.h
class BlockedQueue
{
    // for now i will call the jobs as : job
    // need to change later
    BlockedQueue::BlockedQueue()   // default constructor
    {
        ready = new job[10];
        notready = new job[10];
        readyNumOfEle = 0;
        notreadyNumOfEle = 0;
    }

    void BlockedQueue::Block(job a)
    {
        notready[notreadyNumOfEle] = a;
        notreadyNumOfEle++;
        if(notreadyNumOfEle >= sizeof(notready)/sizeof(notready[0]))
        {
            String *temp= new String[notreadyNumOfEle*2];
            std::copy(notready, notreadynumOfEle, temp);
            delete[] notready;
            notready = temp;
        }
    }

    void BlockedQueue::IOFinish(int position)
    {
        ready[readyNumOfEle] = notready[position];
        readyNumOfEle++;
        if(readyNumOfEle >= sizeof(ready)/sizeof(ready[0]))
        {
            String *temp = new String[readyNumOfEle*2];
            copy(ready, readynumOfEle, temp);
            delete[] ready;
            ready = temp;
        }
        for (int i = position; i < notreadyNumOfEle - 1; i++)
        {
            notready[i] = notready[i + 1];
        }
        notreadyNumOfEle--;
    }

    job BlockedQueue::Unblock()
    {
        job ret = ready[0];
        for (int i = 0; i < readyNumOfEle - 1; i++)
        {
            ready[i] = ready[i + 1];
        }
        readyNumOfEle--;
        return ret;
    }

    /*int BlockedQueue::Main()
    {
        return 0;
    }*/



}
