#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


bool can_assign_worker(
    const vector<size_t>& work,
    const AvailabilityMatrix& avail,
    const size_t maxShifts,
    const size_t row,
    const size_t worker_id
)
{
   if(avail[row][worker_id] == 1 && work[worker_id] < maxShifts) return true;
   else return false;
}

bool assign_worker(
    DailySchedule& sched,
    vector<size_t>& work,
    const size_t row,
    const size_t col,
    const size_t worker_id
)
{
    sched[row][col] = worker_id;
    work[worker_id]++;
    return true;
}

bool unassign_worker(
    DailySchedule& sched,
    vector<size_t>& work,
    const size_t row,
    const size_t col,
    const size_t worker_id
)
{
    sched[row][col] = sched.size();
    work[worker_id]--;
    return false;
}

bool is_schedule_complete(
    const size_t dailyNeed,
    const size_t col
)
{
    if(col == dailyNeed) return true;
    else return false;
}

bool is_day_complete(
    const AvailabilityMatrix& avail,
    const size_t row
)
{
    if(row == avail.size()) return true;
    else return false;
}

bool is_worker_valid(
    const vector<Worker_T>& temp,
    const Worker_T curr,
    const size_t col
)
{
    if(col == 0 || (find(temp.begin(), temp.end(), curr) != temp.end())) return true;
    else return false;
}

bool helperFunction(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    vector<size_t>& work,
    size_t row,
    size_t col
)
{
    if (is_schedule_complete(dailyNeed, col)) {
        col = 0;
        row++;
    }
   
    if (is_day_complete(avail, row)) {
        return true;
    }

    for(Worker_T i = 0; i < avail[row].size(); i++) {
        if (is_worker_valid(sched[row], i, col) && can_assign_worker(work, avail, maxShifts, row, i)) {
            assign_worker(sched, work, row, col, i);
            if (helperFunction(avail, dailyNeed, maxShifts, sched, work, row, col + 1)) {
                return true;
            }
            unassign_worker(sched, work, row, col, i);
        }
    }
    return false;
}

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0) return false;
    else{
        sched.clear();

        for (size_t i = 0; i < avail.size(); i++) {
            vector<Worker_T> temp(dailyNeed, avail[0].size());
            sched.push_back(temp);
        }

        vector<size_t> work(avail[0].size(), 0);
        return helperFunction(avail, dailyNeed, maxShifts, sched, work, 0, 0);
    }
    
}
