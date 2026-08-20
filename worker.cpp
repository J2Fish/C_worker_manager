#include <iostream>
#include "worker.h"
using namespace std;
#include <string>

//AbstractWorker define=========================
AbstractWorker::AbstractWorker(int number, string name, int job)
: m_Number(number),m_Name(name), m_Job(job){}
//Employ define=================================
Employee::Employee(int number, string name)
: AbstractWorker(number, name, 1){}
void Employee::show_info(){
    cout << "\t" << "Id: " << this -> m_Number
         << "\t" << "Name: " << this -> m_Name
         << "\t" << "Job: " << "Employee" 
         << "\t" << "Responsibility:" << "完成经理交给的任务" <<endl;
}
//Manager define================================
Manager::Manager(int number, string name)
: AbstractWorker(number, name, 2){}
void Manager::show_info(){
    cout << "\t" << "Id: " << this -> m_Number
         << "\t" << "Name: " << this -> m_Name
         << "\t" << "Job: " << "Manager" 
         << "\t" << "Responsibility:" << "完成老板交给的任务，并下发任务给员工" <<endl;
}
//Employer define===============================
Employer::Employer(int number, string name)
: AbstractWorker(number, name, 3){}
void Employer::show_info(){
    cout << "\t" << "Id: " << this -> m_Number
         << "\t" << "Name: " << this -> m_Name
         << "\t" << "Job: " << "Employer" 
         << "\t" << "Responsibility:" << "管理公司所有事务" <<endl;
}


