#include "command.h"
#include "fileio.h"
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

Cmd::Cmd(){
    while (1){
        init_cmd();
    } 
}



void Cmd::init_cmd(){
    cout << "\t" << "欢迎使用职工管理系统" << "\t" << "\n"
         << "\t" << "0.退出管理系统" << "\t" << "\n"
         << "\t" << "1.增加职工信息" << "\t" << "\n"
         << "\t" << "2.显示职工信息" << "\t" << "\n"
         << "\t" << "3.删除离职职工" << "\t" << "\n"
         << "\t" << "4.修改职工信息" << "\t" << "\n"
         << "\t" << "5.查找职工信息" << "\t" << "\n"
         << "\t" << "6.按照编号排序" << "\t" << "\n"
         << "\t" << "7.清空当前文档" << "\t" << "\n"
         << "\t" << "8.打开/创建文档" << "\t" << "\n"
         << "\t" << "==================" << "\t" <<endl;
    cout << ">>" ;
    cin >> last_order;
    if (cin.fail()){
    cin.clear();              // 清除 fail 状态
    cin.ignore(1000, '\n');   // 丢掉缓冲区里的垃圾
    }
    order_resolver(last_order);
    
}

void Cmd::exit(){
    ::exit(0);
}

void Cmd::order_resolver(int orders){
    if (orders != 0 && orders != 8 && !wt){
        cout << "请先打开/创建文档" << endl;
        return;
    }
    switch (orders){
        case 0: exit(); break;
        case 1: add(); break;
        case 2: wt -> show_table(); break;
        case 3: del(); break;
        case 4: revise(); break;
        case 5:{
            int mode;
            cout << "按编号查找(0)/按姓名查找(1)>>";
            cin >> mode;
            if (mode == 0){
                int id;
                cout << "输入id>>";
                cin >> id;
                wt -> search(id);
            } else {
                string name;
                cout << "输入姓名>>";
                cin >> name;
                wt -> search(name);
            }
            break;
        }
        case 6: sort(); break;
        case 7: clear(); break;
        case 8: open_file(); break;
        default: break;
    }
}

void Cmd::open_file(){
    cout << "请输入文件地址>>";
    cin >> file_address;
    if (wt) delete wt;
    fstream test(file_address, ios::in);
    if (!test.is_open()){
        char cc;
        cout << "文件不存在，是否创建新文件(y/n)" << endl;
        cin >> cc;
        switch (cc){
            case ('y'):
            case ('Y'):
                wt = new WorkersTable(file_address);
                cout << "列表如下：" << endl;
                wt -> show_table();
                break;
            case ('n'):
            case ('N'):
            default:
                break; 
        }
    }
    else{
        wt = new WorkersTable(file_address);
    }
}

void Cmd::add(){
    int count;
    cout << "添加的记录数>>";
    cin >> count;
    for (int i = 0; i < count; i++){
        int id;
        string name;
        int job;
        cout << "第" << i << "/"<< count << "条"<< endl; 
        cout << "id>>";
        cin >> id;
        cin.ignore();
        cout << "name>>";
        getline(cin, name);
        cout << "job>>";
        cin >> job;
        wt -> add(id, name, job);
        //cout << "录入成功" << endl;
    }
}

void Cmd::del(){
    int id;
    cout << "输入删除员工的id>>";
    cin >> id;
    wt->del(id);
}

void Cmd::search(int id){
    wt->search(id);
}

void Cmd::search(string name){
    wt->search(name);
}

void Cmd::clear(){
    wt->clear();
}

void Cmd::revise(){
    int id;
    cout << "输入被修改的id>>";
    cin >> id;
    cin.ignore(); 
    string name;
    int job;
    string temp;
    cout << "修改name>>";
    getline(cin, name);
    cout << "修改job>>";
    getline(cin, temp);
    if (name == "" && temp == ""){
        cout << "未做任何修改" << endl;
    } else if (name == ""){
        wt->revise(id, stoi(temp));
    } else if (temp == ""){
        wt->revise(id, name);
    } else {
        wt->revise(id, name, stoi(temp));
    }
} 

void Cmd::sort(){
    int mode;
    cout << "升序/降序(0/1)>>";
    cin >> mode;
    wt -> sort(mode);
    wt -> show_table();
}