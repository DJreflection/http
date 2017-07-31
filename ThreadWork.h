//
// Created by zy on 7/27/17.
//

#ifndef HTT4_THREADWORK_H
#define HTT4_THREADWORK_H

#include <vector>
#include <thread>

using namespace std;

void ThreadInit(vector<pair<int ,thread> >&ThreadPool);
void WriteLog();

#endif //HTT4_THREADWORK_H
