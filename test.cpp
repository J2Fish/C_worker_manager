#include "fileio.h"
#include "worker.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>

using namespace std;

int passed = 0;
int failed = 0;

void check(const string& test_name, bool condition) {
    if (condition) {
        cout << "  [PASS] " << test_name << endl;
        passed++;
    } else {
        cout << "  [FAIL] " << test_name << endl;
        failed++;
    }
}

void print_result() {
    cout << "\n==============================" << endl;
    cout << "  测试结束: " << passed << " 通过, " << failed << " 失败" << endl;
    cout << "==============================" << endl;
}

void test_add_and_file_commit() {
    cout << "\n=== 测试1: add 写入文件 ===" << endl;

    const string test_file = "file/test_add.txt";
    remove(test_file.c_str());

    {
        WorkersTable wt(test_file);

        wt.add(1001, "张三", 1);
        wt.add(1002, "李四", 2);
        wt.add(1003, "王五", 3);
    }

    ifstream ifs(test_file);
    check("文件存在", ifs.is_open());

    int id;
    string name;
    int job;
    int count = 0;
    while (ifs >> id >> name >> job) {
        count++;
        cout << "    读取到: " << id << " " << name << " " << job << endl;
    }
    ifs.close();

    check("写入了3条记录", count == 3);

    remove(test_file.c_str());
}

void test_search() {
    cout << "\n=== 测试2: search 查找 ===" << endl;

    const string test_file = "file/test_search.txt";
    remove(test_file.c_str());

    WorkersTable wt(test_file);
    wt.add(2001, "赵六", 1);
    wt.add(2002, "钱七", 2);
    wt.add(2003, "孙八", 3);

    int idx_id = wt.search(2002);
    check("按id查找2002找到", idx_id != -1);

    int idx_name = wt.search("赵六");
    check("按姓名查找赵六找到", idx_name != -1);

    int idx_none = wt.search(9999);
    check("按id查找9999找不到", idx_none == -1);

    remove(test_file.c_str());
}

void test_revise() {
    cout << "\n=== 测试3: revise 修改 ===" << endl;

    const string test_file = "file/test_revise.txt";
    remove(test_file.c_str());

    WorkersTable wt(test_file);
    wt.add(3001, "周九", 1);

    wt.revise(3001, "周九十");
    int idx = wt.search("周九十");
    check("修改姓名为周九十", idx != -1);

    wt.revise(3001, 2);
    idx = wt.search(3001);
    check("修改岗位为Manager", idx != -1 && wt.search(3001) != -1);

    wt.revise(3001, "周九", 3);
    idx = wt.search("周九");
    check("同时修改姓名和岗位", idx != -1);

    remove(test_file.c_str());
}

void test_sort() {
    cout << "\n=== 测试4: sort 排序 ===" << endl;

    const string test_file = "file/test_sort.txt";
    remove(test_file.c_str());

    WorkersTable wt(test_file);
    wt.add(3003, "A", 1);
    wt.add(3001, "B", 1);
    wt.add(3002, "C", 1);

    wt.sort(0);

    ifstream ifs(test_file);
    int ids[3];
    string names[3];
    int jobs[3];
    int i = 0;
    while (ifs >> ids[i] >> names[i] >> jobs[i]) i++;
    ifs.close();

    check("升序排序后第1个id=3001", ids[0] == 3001);
    check("升序排序后第2个id=3002", ids[1] == 3002);
    check("升序排序后第3个id=3003", ids[2] == 3003);

    wt.sort(1);

    ifs.open(test_file);
    i = 0;
    while (ifs >> ids[i] >> names[i] >> jobs[i]) i++;
    ifs.close();

    check("降序排序后第1个id=3003", ids[0] == 3003);
    check("降序排序后第2个id=3002", ids[1] == 3002);
    check("降序排序后第3个id=3001", ids[2] == 3001);

    remove(test_file.c_str());
}

void test_empty_file() {
    cout << "\n=== 测试5: 空文件初始化 ===" << endl;

    const string test_file = "file/test_empty.txt";
    remove(test_file.c_str());

    {
        ofstream ofs(test_file);
        ofs.close();
    }

    WorkersTable wt(test_file);
    check("空文件len=0", wt.count_file() == 0);

    remove(test_file.c_str());
}

void test_file_persistence() {
    cout << "\n=== 测试6: 文件持久化（关闭后重新打开） ===" << endl;

    const string test_file = "file/test_persist.txt";
    remove(test_file.c_str());

    {
        WorkersTable wt(test_file);
        wt.add(4001, "持久化测试", 1);
    }

    {
        WorkersTable wt2(test_file);
        int idx = wt2.search(4001);
        check("重新打开后能找到4001", idx != -1);
    }

    remove(test_file.c_str());
}

int main() {
    cout << "====================================" << endl;
    cout << "  职工管理系统 - 单元测试" << endl;
    cout << "====================================" << endl;

    test_add_and_file_commit();
    test_search();
    test_revise();
    test_sort();
    test_empty_file();
    test_file_persistence();

    print_result();

    return failed > 0 ? 1 : 0;
}