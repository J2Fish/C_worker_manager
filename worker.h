// worker.h
#ifndef WORKER_H        // 防止重复包含的保护宏
#define WORKER_H

#include <string>
using namespace std;

// 抽象基类：声明
class AbstractWorker {
public:
    int m_Number;
    string m_Name;
    int m_Job;
    AbstractWorker(int number, string name, int job);
    virtual ~AbstractWorker() = default;
    virtual void show_info() = 0;

};

// 子类声明
class Employee : public AbstractWorker {
public:
    Employee(int number, string name);
    void show_info() override;
};

class Manager : public AbstractWorker {
public:
    Manager(int number, string name);
    void show_info() override;
};

class Employer : public AbstractWorker {
public:
    Employer(int number, string name);
    void show_info() override;
};

#endif  // WORKER_H