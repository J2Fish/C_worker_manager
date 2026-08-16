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
        
        void table_commit();
        void flie_commit();
    protected:
        void init_table();
        string file;
        int len = 0;
        int len_table = 0;
        AbstractWorker** wkers = nullptr;
        string** names = nullptr;
        int** ids = nullptr;
};

#endif 