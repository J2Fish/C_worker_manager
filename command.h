// command.h
#ifndef COMMAND_H
#define COMMAND_H



#include "fileio.h"
#include <iostream>
#include <string>
using namespace std;
class Cmd{
    public:
        Cmd();
        void order_resolver(int orders);
        void init_cmd();
        void exit();
        void open_file();
        void add();
        void del();
        void revise();
        void clear();
        void search(string name);
        void search(int id);
        void sort();
    protected:
        int last_order;
        string file_address;
        WorkersTable* wt= nullptr;
};






#endif