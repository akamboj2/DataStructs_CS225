#include <iostream>
#include "OfficeHour.h"

/*
Given the current Office Hour queue and the currently on-duty staffers, return
how long the nth student will need to wait before a Staffer can reach them
Return -1 if there are no staff available to help the nth student

@param queue A queue containing the students currently waiting for help
@param onDutyStaff  A vector of Staffers currently on duty
@param nthStudent   The student for whom we are calculating a wait time
@return             How many minutes the nth student will have to wait before getting help
*/
int waitTime(queue<Student> queue, vector<Staffer> onDutyStaff, int nthStudent) {
    // Your code here!
    int time =0;
    Student at;
    vector<int> times;
    for (int i=0;i<onDutyStaff.size();i++) times.push_back(0);

    for (int i=0;i<nthStudent;i++){
      at=queue.front();
      //look for smallest time staff duty and use them
      int min = 0;


    }
    return -1;
}
