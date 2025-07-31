#include <iostream>
#include <vector>
#include <string>
#include <limits>

// vvvvv 新增的头文件，用于调用Windows API vvvvv
#include <windows.h> 

// Contact 结构体保持不变
struct Person {
    std::string m_Name;
    int m_Sex;
    int m_Age;
    std::string m_Phone;
    std::string m_Addr;
};

// Addressbooks 结构体保持不变
struct Addressbooks {
    std::vector<Person> PersonArr;
};

void showMenu() {
    std::cout << "***************************" << std::endl;
    std::cout << "*****  1. 添加联系人  *****" << std::endl;
    std::cout << "*****  2. 显示联系人  *****" << std::endl;
    std::cout << "*****  3. 删除联系人  *****" << std::endl;
    std::cout << "*****  4. 查找联系人  *****" << std::endl;
    std::cout << "*****  5. 修改联系人  *****" << std::endl;
    std::cout << "*****  6. 清空联系人  *****" << std::endl;
    std::cout << "*****  0. 退出通讯录  *****" << std::endl;
    std::cout << "***************************" << std::endl;
}

// ... 此处省略 addPerson, showPerson 等函数，它们无需任何改动 ...
void addPerson(Addressbooks &abs) {
    Person p;
    std::cout << "请输入姓名：" << std::endl;
    std::cin >> p.m_Name;
    std::cout << "请输入性别：" << std::endl;
    std::cout << "1 --- 男" << std::endl;
    std::cout << "2 --- 女" << std::endl;
    while (true) {
        std::cin >> p.m_Sex;
        if (p.m_Sex == 1 || p.m_Sex == 2) { break; }
        std::cout << "输入有误，请重新输入" << std::endl;
    }
    std::cout << "请输入年龄：" << std::endl;
    std::cin >> p.m_Age;
    std::cout << "请输入电话：" << std::endl;
    std::cin >> p.m_Phone;
    std::cout << "请输入地址：" << std::endl;
    std::cin >> p.m_Addr;
    abs.PersonArr.push_back(p);
    std::cout << "添加成功" << std::endl;
}
void showPerson(const Addressbooks &abs) {
    if (abs.PersonArr.empty()) {
        std::cout << "通讯录为空" << std::endl;
    } else {
        for (size_t i = 0; i < abs.PersonArr.size(); i++) {
            std::cout << "姓名：" << abs.PersonArr[i].m_Name << "\t";
            std::cout << "性别：" << (abs.PersonArr[i].m_Sex == 1 ? "男" : "女") << "\t";
            std::cout << "年龄：" << abs.PersonArr[i].m_Age << "\t";
            std::cout << "电话：" << abs.PersonArr[i].m_Phone << "\t";
            std::cout << "地址：" << abs.PersonArr[i].m_Addr << std::endl;
        }
    }
}
int isExist(const Addressbooks &abs, const std::string &name) {
    for (size_t i = 0; i < abs.PersonArr.size(); i++) {
        if (abs.PersonArr[i].m_Name == name) { return i; }
    }
    return -1;
}
void deletePerson(Addressbooks &abs) {
    std::cout << "请输入要删除的联系人姓名：" << std::endl;
    std::string name;
    std::cin >> name;
    int ret = isExist(abs, name);
    if (ret != -1) {
        abs.PersonArr.erase(abs.PersonArr.begin() + ret);
        std::cout << "删除成功" << std::endl;
    } else {
        std::cout << "查无此人" << std::endl;
    }
}
void findPerson(const Addressbooks &abs) {
    std::cout << "请输入要查找的联系人姓名：" << std::endl;
    std::string name;
    std::cin >> name;
    int ret = isExist(abs, name);
    if (ret != -1) {
        std::cout << "姓名：" << abs.PersonArr[ret].m_Name << "\t";
        std::cout << "性别：" << (abs.PersonArr[ret].m_Sex == 1 ? "男" : "女") << "\t";
        std::cout << "年龄：" << abs.PersonArr[ret].m_Age << "\t";
        std::cout << "电话：" << abs.PersonArr[ret].m_Phone << "\t";
        std::cout << "地址：" << abs.PersonArr[ret].m_Addr << std::endl;
    } else {
        std::cout << "查无此人" << std::endl;
    }
}
void modifyPerson(Addressbooks &abs) {
    std::cout << "请输入要修改的联系人姓名：" << std::endl;
    std::string name;
    std::cin >> name;
    int ret = isExist(abs, name);
    if (ret != -1) {
        Person &p = abs.PersonArr[ret];
        std::cout << "请输入新的姓名：" << std::endl;
        std::cin >> p.m_Name;
        std::cout << "请输入新的性别：" << std::endl;
        std::cout << "1 --- 男" << std::endl;
        std::cout << "2 --- 女" << std::endl;
        while (true) {
            std::cin >> p.m_Sex;
            if (p.m_Sex == 1 || p.m_Sex == 2) { break; }
            std::cout << "输入有误，请重新输入" << std::endl;
        }
        std::cout << "请输入新的年龄：" << std::endl;
        std::cin >> p.m_Age;
        std::cout << "请输入新的电话：" << std::endl;
        std::cin >> p.m_Phone;
        std::cout << "请输入新的地址：" << std::endl;
        std::cin >> p.m_Addr;
        std::cout << "修改成功" << std::endl;
    } else {
        std::cout << "查无此人" << std::endl;
    }
}
void cleanPerson(Addressbooks &abs) {
    abs.PersonArr.clear();
    std::cout << "通讯录已清空" << std::endl;
}
void clearScreen() { std::cout << std::string(50, '\n'); }
void pause() {
    std::cout << "\n按 Enter 键继续..." << std::endl;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

int main() {
    // vvvvv 新增的核心代码，设置控制台输出编码为 UTF-8 vvvvv
    SetConsoleOutputCP(CP_UTF8);

    Addressbooks abs;
    int select = 0;

    while (true) {
        showMenu();
        std::cout << "请输入您的选择：" << std::endl;
        std::cin >> select;

        switch (select) {
        case 1:
            addPerson(abs);
            break;
        case 2:
            showPerson(abs);
            break;
        case 3:
            deletePerson(abs);
            break;
        case 4:
            findPerson(abs);
            break;
        case 5:
            modifyPerson(abs);
            break;
        case 6:
            cleanPerson(abs);
            break;
        case 0:
            std::cout << "欢迎下次使用" << std::endl;
            return 0;
        default:
            std::cout << "输入有误，请重新输入" << std::endl;
            break;
        }
        
        pause();
        clearScreen();
    }

    return 0;
}