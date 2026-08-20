#include "worker.h"
#include "fileio.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;


WorkersTable::WorkersTable(string address):file(address){
    count_file();
    init_table();
}
        
int WorkersTable::file_commit(){
    table_commit();
    fstream ofs(file, ios::out);
    if (! ofs.is_open()){
        cout << "文件" << file << "打开失败" << endl;
        return 0;
    }
    for (int i = 0; i < len; i++ ){
        if (wkers[i] != nullptr){
            ofs << *(ids[i]) << " "
                << *(names[i]) << " "
                << (wkers[i] -> m_Job) <<endl;
        }
    }
    ofs.close();
    return 0;

    
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
    int flag = -1;
    for (int i = 0; i < len; i++ ){
        if (number == *(ids[i])){
            flag = i;
        }
    }
    if (flag == -1) {
        cout << "找不到id为" << number << "的职工" << endl;
    }
    return flag;
}

int WorkersTable::del(int number){
    int p = search(number);
    int end = end_table();
    if (p == -1){
        return 0;
    }
    char a;
    cout << "确认删除?y/n" ;
    cin >> a;
    switch (a){
        case ('y'):
        case ('Y'):
            delete wkers[p];
            wkers[p] = wkers[end];
            ids[p] = ids[end];
            names[p] = names[end];
            wkers[end] = nullptr;
            ids[end] = nullptr;
            names[end] = nullptr;
            table_commit();
            break;
        case ('n'):
            break;
        case ('N'):
            break;
        default:
            break;
    }
    cout << "成功删除" <<endl;
    return 0;

}

void WorkersTable::init_table(){
    fstream ifs;
    ifs.open(file, ios::in | ios::out | ios::app);
    if (! ifs.is_open()){
        cout << "文件" << file << "打开失败" << endl;
    }
    if (len == 0){
        cout << "表格为空" << endl;
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
        p = job_judge(job, number, name);
        wkers[flag] = p;
        names[flag] = &(p -> m_Name);
        ids[flag] = &(p -> m_Number);
        flag++;
    }
    ifs.close();
}

int WorkersTable::count_file(){
    fstream ifs(file, ios::in);
    int number;
    string name;
    int job;
    while (ifs >> number && ifs >> name && ifs >> job){
        len++;
    }
    ifs.close();
    return len;
}


void WorkersTable::table_commit(){
    end_table();
    AbstractWorker** wkers_ = new AbstractWorker*[end + 2 + len_add];
    string** names_ = new string*[end + 2 + len_add];
    int** ids_ = new int*[end + 2 + len_add];
    for (int i = 0; i < len; i++ ){
        if (wkers[i] != nullptr){
            wkers_[i] = wkers[i];
            names_[i] = names[i];
            ids_[i] = ids[i];
        }
    }
    for (int i = 0; i < len_add; i++ ){
        wkers_[i + len] = add_wkers[i];
        names_[i + len] = &(add_wkers[i] -> m_Name);
        ids_[i + len] = &(add_wkers[i] -> m_Number);
        //delete add_wkers[i];
        }
    delete[] add_wkers;
    add_wkers = nullptr;
    delete[] wkers;
    delete[] ids;
    delete[] names;
    wkers = wkers_;
    ids = ids_;
    names = names_;
    len = end + len_add;
    len_add = 0;
}

int WorkersTable::end_table(){
    end = 0;
    for (int i = len - 1; i >= 0; i-- ){
        if (wkers[i] != nullptr){
            end = i+1;
            break;
        }
    }
    return end; //最后一个有效函数的索引
}

int WorkersTable::add(int id, string name, int job){
    len_add++;
    AbstractWorker* p = nullptr;
    AbstractWorker** temp = new AbstractWorker*[len_add];
    for (int i = 0; i < len_add-1; i++){
        temp[i] = add_wkers[i];
        add_wkers[i] = nullptr; 
    }
    delete[] add_wkers;
    add_wkers = temp;
    p = job_judge(job , id, name);
    add_wkers[len_add-1] = p;
    table_commit();
    file_commit();
    cout << "录入成功" << endl;
    return 0;
}


int WorkersTable::revise(int number, int job){
    int order = search(number);
    if (order == -1){
        return 0;
    }
    AbstractWorker* p = wkers[order];
    p = job_judge(job, number, p -> m_Name);
    delete wkers[order];
    wkers[order] = p;
    names[order] = &(p -> m_Name);
    ids[order] = &(p -> m_Number);
    return 0;
    

}

int WorkersTable::revise(int number, string name, int job){
    int order = search(number);
    if (order == -1){
        return 0;
    }
    delete wkers[order];
    AbstractWorker* p = wkers[order];
    p = job_judge(job, number, name);
    wkers[order] = p;
    names[order] = &(p -> m_Name);
    ids[order] = &(p -> m_Number);
    return 0;
    

}

int WorkersTable::revise(int number, string name){
    int order = search(number);
    if (order == -1){
        return 0;
    }
    AbstractWorker* p = wkers[order];
    p -> m_Name = name;
    return 0;
}

AbstractWorker* WorkersTable::job_judge(int job, int id, string name){
    AbstractWorker* p = nullptr;
    if (job == 1){
        p = new Employee(id, name);
    }
    else if (job == 2){
        p = new Manager(id, name);
    }
    else if (job == 3){
        p = new Employer(id, name);
    }
    else {
        cout << "job must give 1/2/3(Employee/Manager/Employer)" << endl;
    }
    return p;
}

void WorkersTable::clear(){
    char a;
    cout << "确认清空？(y/n)";
    cin >> a;
    switch (a){
        case ('y'):
        case ('Y'):  
            for (int i = 0; i < len; i++){
                delete wkers[i];
                
            }
            for (int i = 0; i < len_add; i++){
                delete add_wkers[i];
            }
            delete[] wkers;
            delete[] names;
            delete[] ids;
            delete[] add_wkers;
            len = 0;
            end = 0;
            len_add = 0;
            wkers = nullptr;
            add_wkers = nullptr;
            file_commit();
            cout << "成功删除" <<endl;
            break;
        case ('n'):
        case ('N'):
        default:
            break;
    }
    
}

void WorkersTable::sort(int mode){
    for (int i = len - 1; i > 0; i--){
        for (int j = 0; j < i; j++){
            if ((mode == 0 ? wkers[j] -> m_Number > wkers[j+1] -> m_Number : wkers[j] -> m_Number < wkers[j+1] -> m_Number)){
                AbstractWorker* tmp_w = wkers[j];
                wkers[j] = wkers[j+1];
                wkers[j+1] = tmp_w;

                string* tmp_n = names[j];
                names[j] = names[j+1];
                names[j+1] = tmp_n;

                int* tmp_id = ids[j];
                ids[j] = ids[j+1];
                ids[j+1] = tmp_id;
            }
        }
    }
    file_commit();
}

void WorkersTable::show_table(){
    if (len == 0){
        cout << "表格为空" << endl;
        return;
    }
    for (int i = 0; i < len; i++){
        if (wkers[i] != nullptr){
            wkers[i] -> show_info();
        }
    }
}