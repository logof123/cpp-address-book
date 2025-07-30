#include <iostream>
#include <vector>
#include <string>
#include <fstream>   // <--- 新增：文件流
#include <sstream>   // <--- 新增：字符串流
#include <limits>

// Contact 结构体 (无变化)
struct Contact {
    std::string name;
    std::string phone;
    std::string email;
};


// *** 新增函数 ***
// 函数：将联系人保存到文件
void saveContacts(const std::vector<Contact>& contacts, const std::string& filename) {
    // 1. 创建一个输出文件流对象
    std::ofstream outFile(filename);
    if (!outFile) { // 检查文件是否成功打开
        std::cerr << "Error: Could not open file for writing." << std::endl;
        return;
    }
    // 2. 遍历 vector
    for (const auto& contact : contacts) {
        // 3. 按 CSV 格式写入文件，用逗号分隔，用换行符结束一行
        outFile << contact.name << "," << contact.phone << "," << contact.email << std::endl;
    }
    // outFile 对象在函数结束时会自动关闭文件
    std::cout << "Contacts saved successfully." << std::endl;
}

// *** 新增函数 ***
// 函数：从文件加载联系人
void loadContacts(std::vector<Contact>& contacts, const std::string& filename) {
    // 1. 创建一个输入文件流对象
    std::ifstream inFile(filename);
    if (!inFile) { // 如果文件打不开（比如第一次运行还不存在），不是错误，直接返回
        return;
    }

    std::string line;
    // 2. 每次从文件中读取一行，存入 line 变量
    while (std::getline(inFile, line)) {
        // 3. 为这一行创建一个字符串流，方便解析
        std::stringstream ss(line);
        std::string name, phone, email;

        // 4. 使用 getline 从字符串流中按逗号分割提取数据
        if (std::getline(ss, name, ',') && std::getline(ss, phone, ',') && std::getline(ss, email)) {
            contacts.push_back({name, phone, email});
        }
    }
}


// 函数：显示一个联系人的详情
void printContact(const Contact& contact) {
    std::cout << "  Name:  " << contact.name << std::endl;
    std::cout << "  Phone: " << contact.phone << std::endl;
    std::cout << "  Email: " << contact.email << std::endl;
    std::cout << "-------------------------" << std::endl;
}

// viewContacts 函数 (稍作修改，调用 printContact)
void viewContacts(const std::vector<Contact>& contacts) {
    if (contacts.empty()) {
        std::cout << "Address book is empty." << std::endl;
        return;
    }
    std::cout << "\n--- All Contacts ---" << std::endl;
    for (const auto& contact : contacts) {
        printContact(contact);
    }
}

// addContact 函数 (无变化)
void addContact(std::vector<Contact>& contacts) {
    Contact newContact;
    std::cout << "Enter name: ";
    std::getline(std::cin, newContact.name);
    std::cout << "Enter phone number: ";
    std::getline(std::cin, newContact.phone);
    std::cout << "Enter email address: ";
    std::getline(std::cin, newContact.email);
    contacts.push_back(newContact);
    std::cout << "Contact added successfully!" << std::endl;
}

// searchContact 函数 (稍作修改，调用 printContact)
void searchContact(const std::vector<Contact>& contacts) {
    std::string searchName;
    std::cout << "Enter name to search: ";
    std::getline(std::cin, searchName);

    bool found = false;
    for (const auto& contact : contacts) {
        if (contact.name.find(searchName) != std::string::npos) {
            if (!found) {
                std::cout << "\n--- Search Results ---" << std::endl;
            }
            printContact(contact);
            found = true;
        }
    }
    if (!found) {
        std::cout << "No contact found with that name." << std::endl;
    }
}

// deleteContact 函数 (无变化)
void deleteContact(std::vector<Contact>& contacts) {
    if (contacts.empty()) {
        std::cout << "Address book is empty, nothing to delete." << std::endl;
        return;
    }
    std::string nameToDelete;
    std::cout << "Enter the exact name of the contact to delete: ";
    std::getline(std::cin, nameToDelete);

    bool found = false;
    for (auto it = contacts.begin(); it != contacts.end(); ) {
        if (it->name == nameToDelete) {
            it = contacts.erase(it);
            found = true;
            std::cout << "Contact '" << nameToDelete << "' deleted successfully." << std::endl;
            break;
        } else {
            ++it;
        }
    }
    if (!found) {
        std::cout << "Contact '" << nameToDelete << "' not found." << std::endl;
    }
}

// showMenu 函数 (无变化)
void showMenu() {
    std::cout << "\n===== Address Book Menu =====" << std::endl;
    std::cout << "1. Add Contact" << std::endl;
    std::cout << "2. View All Contacts" << std::endl;
    std::cout << "3. Search Contact" << std::endl;
    std::cout << "4. Delete Contact" << std::endl;
    std::cout << "5. Save and Exit" << std::endl;
    std::cout << "===========================" << std::endl;
    std::cout << "Enter your choice: ";
}


// *** main 函数最终版 ***
int main() {
    std::vector<Contact> contacts;
    const std::string filename = "contacts.csv"; // 定义数据文件名

    // *** 关键步骤1：程序启动时，加载数据 ***
    loadContacts(contacts, filename);

    int choice;
    while (true) {
        showMenu();
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cout << "Invalid input. Please enter a number." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1: addContact(contacts); break;
            case 2: viewContacts(contacts); break;
            case 3: searchContact(contacts); break;
            case 4: deleteContact(contacts); break;
            case 5:
                // *** 关键步骤2：程序退出前，保存数据 ***
                saveContacts(contacts, filename);
                std::cout << "Exiting program. Goodbye!" << std::endl;
                return 0;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }
    return 0;
}