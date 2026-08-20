// fileio.h
#ifndef FILEIO_H        // 防止重复包含的保护宏
#define FILEIO_H


#include <iostream>
#include <fstream>
#include <string>
#include "worker.h"
using namespace std;


class WorkersTable{
    public:
        WorkersTable(string address);
        void add(AbstractWorker& w);
        int search(string name);
        int search(int number);
        int del(int number);
        void show_table();
        int count_file();
        int end_table();
        int add(int id, string name, int job);
        void table_commit();
        int file_commit();
        int revise(int number,int job);
        int revise(int number, string name);
        int revise(int number, string name, int job);
        void sort(int mode);
        void clear();
    protected:
        void init_table();
        AbstractWorker* job_judge(int job, int id, string name);
        string file;
        int len = 0;
        int end = 0;
        int len_add = 0;
        AbstractWorker** add_wkers = nullptr;
        AbstractWorker** wkers = nullptr;
        string** names = nullptr;
        int** ids = nullptr;
};

#endif 