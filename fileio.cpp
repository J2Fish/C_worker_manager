#include <iostream>
#include <fstream>
#include <string>
#include "worker.h"
#include <unordered_map>
#include "fileio.h"
using namespace std;


WorkersTable::WorkersTable(string address):file(address){
    count_file();
    init_table();
}
        
void WorkersTable::add(AbstractWorker& w){
    fstream ifs(file, ios::out);
    if (! ifs.is_open()){
        cout << "文件" << file << "打开失败" << endl;
    }
    ifs << w.m_Number <<" "<< w.m_Name <<" "<< w.m_Job <<endl;
}

int WorkersTable::search(string name){
    int flag = -1;
    for (int i = 0; i < len; i++ ){
        if (name == *(names[i])){
            flag = i;
        }
    }
    if (flag == -1) {
        cout << "找不到名为" << name << "的职工" << endl;
    }
    return flag;
}

int WorkersTable::search(int number){
    AbstractWorker** p = nullptr;
    for (int i = 0; i < len; i++ ){
        if (number == *(ids[i])){
            p = &(wkers[i]);
        }
    }
    if (p == nullptr) {
        cout << "找不到id为" << number << "的职工" << endl;
    }
    return p;
}

int WorkersTable::del(int number){
    AbstractWorker** p= search(number);
    if (p == nullptr){
        return 0;
    }
    char a;
    cout << "确认删除?y/n" ;
    cin >> a;
    switch (a){
        case ('y'):
            delete *p;
            *p = ;
            delete p;
            p = nullptr;
            break;
        case ('Y'):
            delete *p;
            *p = nullptr;
            delete p;
            p = nullptr;
            break;
        case ('n'):
            break;
        case ('N'):
            break;
        default:
            break;
    }
    return 0;

}

void WorkersTable::init_table(){
    fstream ifs;
    ifs.open(file, ios::in | ios::out | ios::app);
    if (! ifs.is_open()){
        cout << "文件" << file << "打开失败" << endl;
    }
    int number;
    string name;
    int job;
    wkers = new AbstractWorker*[len];
    names = new string*[len];
    ids = new int*[len];
    int flag = 0;
    while (ifs >> number && ifs >> name && ifs >> job){
        AbstractWorker* p = nullptr;
        if (job == 1){
            p = new Employee(number, name);
        }
        else if (job == 2){
            p = new Manager(number, name);
        }
        else if (job == 3){
            p = new Employer(number, name);
        }
        wkers[flag] = p;
        names[flag] = &(p -> m_Name);
        ids[flag] = &(p -> m_Number);
        flag++;
    }
}

int WorkersTable::count_file(){
    fstream ifs(file, ios::in);
    int number;
    string name;
    int job;
    while (ifs >> number && ifs >> name && ifs >> job){
        len++;
    }
    return len;
}


void WorkersTable::table_commit(){
    count_table();
    wkers = new AbstractWorker*[len_table];
    names = new string*[len_table];
    ids = new int*[len_table];
    for (int i = 0; i < len; i++ ){
        if (wkers[i] != nullptr){
            wkers[i] = p;
            names[i] = &(p -> m_Name);
            ids[i] = &(p -> m_Number);
        }
    }
}