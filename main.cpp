#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

// Date structure
struct Date {
    int day, month, year;
};

// Convert date to string
std::string dateToString(const Date& date) {
    return std::to_string(date.day) + "/" + std::to_string(date.month) + "/" + std::to_string(date.year);
}

// Shipment status enumeration
enum ShipmentStatus { Received, InTransit, Delivered };

// Payment status enumeration
enum PaymentStatus { Unpaid, Paid };

// Base class Information
class Information {
protected:
    std::string senderName, receiverName, senderAddress, receiverAddress;
    int senderID, receiverID, senderTel, receiverTel;
public:
    // Constructor
    Information(const std::string& sName, const std::string& rName, const std::string& sAddress,
        const std::string& rAddress, int sID, int rID, int sTel, int rTel)
        : senderName(sName), receiverName(rName), senderAddress(sAddress),
        receiverAddress(rAddress), senderID(sID), receiverID(rID), senderTel(sTel), receiverTel(rTel) {}

    // Display function for sender information
    void displaySenderInfo() const {
        std::cout << "Sender ID: " << senderID << "\n";
        std::cout << "Sender Name: " << senderName << "\n";
        std::cout << "Sender Address: " << senderAddress << "\n";
        std::cout << "Sender Tel: " << senderTel << "\n";
    }

    // Display function for receiver information
    void displayReceiverInfo() const {
        std::cout << "Receiver ID: " << receiverID << "\n";
        std::cout << "Receiver Name: " << receiverName << "\n";
        std::cout << "Receiver Address: " << receiverAddress << "\n";
        std::cout << "Receiver Tel: " << receiverTel << "\n";
    }

    friend class SenderManagement;
    friend class ReceiverManagement;
};

// Derived class Sender inheriting from Information
class Sender : public Information {
public:
    // Constructor
    Sender(const std::string& sName, const std::string& sAddress, int sID, int sTel)
        : Information(sName, "", sAddress, "", sID, 0, sTel, 0) {}

    // Display sender information
    void displaySender() const {
        std::cout << "Sender Information:\n";
        displaySenderInfo(); // Call the base class method to display sender info
    }

    void updateSenderDetails(const std::string& name, const std::string& address, int tel) {
        senderName = name;
        senderAddress = address;
        senderTel = tel;
    }
};

// Derived class Receiver inheriting from Information
class Receiver : public Information {
public:
    // Constructor
    Receiver(const std::string& rName, const std::string& rAddress, int rID, int rTel)
        : Information("", rName, "", rAddress, 0, rID, 0, rTel) {}

    // Display receiver information
    void displayReceiver() const {
        std::cout << "Receiver Information:\n";
        displayReceiverInfo(); // Call the base class method to display receiver info
    }

    void updateReceiverDetails(const std::string& name, const std::string& address, int tel) {
        receiverName = name;
        receiverAddress = address;
        receiverTel = tel;
    }
};

class Shipment : public Information {
private:
    std::string shipmentId;
    Date receiveDate, sendDate;
    std::string goodsInfo;
    ShipmentStatus status;
    PaymentStatus pstatus;

public:
    // Constructor
    Shipment(const std::string& sName, const std::string& sAddress, int sID,
        const std::string& rName, const std::string& rAddress, int rID,
        const std::string& sId, const Date& rDate, const Date& sDate,
        const std::string& gInfo, ShipmentStatus st, PaymentStatus pst)
        : Information(sName, rName, sAddress, rAddress, sID, rID, 0, 0),
        shipmentId(sId), receiveDate(rDate), sendDate(sDate),
        goodsInfo(gInfo), status(st), pstatus(pst) {}
};

class SenderManagement {
private:
    std::vector<Sender> senders;
public:
    void addSender() {
        system("CLS"); // Xóa màn hình
        std::string name, address;
        int id, tel;

        std::cout << "Enter Sender ID: ";
        std::cin >> id;
        std::cin.ignore(); // Ignore the newline character left by std::cin

        // Check if the sender ID already exists
        auto it = std::find_if(senders.begin(), senders.end(), [id](const Sender& s) {
            return s.senderID == id;
            });

        if (it != senders.end()) {
            std::cout << "Sender with ID " << id << " already exists. Please enter a new ID.\n";
            addSender(); // Recursive call to addSender to retry with a new ID
            return;
        }

        std::cout << "Enter Sender Name: ";
        std::getline(std::cin, name);

        std::cout << "Enter Sender Address: ";
        std::getline(std::cin, address);

        std::cout << "Enter Sender Tel: ";
        std::cin >> tel;
        std::cin.ignore(); // Ignore the newline character left by std::cin

        // Create a new Sender object and add it to the vector
        Sender newSender(name, address, id, tel);
        senders.push_back(newSender);

        std::cout << "Sender added successfully!\n";
    }

    void printAllSenders() const {
        system("CLS");
        std::cout << "All Senders:\n";
        for (const auto& sender : senders) {
            sender.displaySender();
            std::cout << "----------------\n";
        }
        system("pause");
    }

    void deleteSender() {
        system("CLS"); // Xóa màn hình
        int id;
        std::cout << "Enter Sender ID to delete: ";
        std::cin >> id;
        auto it = std::find_if(senders.begin(), senders.end(), [id](const Sender& s) {
            return s.senderID == id;
            });

        if (it != senders.end()) {
            senders.erase(it); // Erase the sender if found
            std::cout << "Sender with ID " << id << " deleted successfully!\n";
        }
        else {
            std::cout << "Sender with ID " << id << " does not exist.\n";
        }
    }

    void updateSender() {
        system("CLS"); // Xóa màn hình
        int id;
        std::cout << "Enter Sender ID to update: ";
        std::cin >> id;
        auto it = std::find_if(senders.begin(), senders.end(), [id](const Sender& s) {
            return s.senderID == id;
            });

        if (it != senders.end()) {
            Sender& senderToUpdate = *it;
            int choice;
            std::cout << "Sender found! What do you want to update?\n";
            std::cout << "1. Name\n";
            std::cout << "2. Address\n";
            std::cout << "3. Telephone\n";
            std::cout << "Enter your choice: ";
            std::cin >> choice;
            std::cin.ignore(); // Ignore the newline character left by std::cin

            switch (choice) {
            case 1: {
                std::string newName;
                std::cout << "Enter new name: ";
                std::getline(std::cin, newName);
                senderToUpdate.updateSenderDetails(newName, senderToUpdate.senderAddress, senderToUpdate.senderTel);
                std::cout << "Name updated successfully!\n";
                break;
            }
            case 2: {
                std::string newAddress;
                std::cout << "Enter new address: ";
                std::getline(std::cin, newAddress);
                senderToUpdate.updateSenderDetails(senderToUpdate.senderName, newAddress, senderToUpdate.senderTel);
                std::cout << "Address updated successfully!\n";
                break;
            }
            case 3: {
                int newTel;
                std::cout << "Enter new telephone: ";
                std::cin >> newTel;
                senderToUpdate.updateSenderDetails(senderToUpdate.senderName, senderToUpdate.senderAddress, newTel);
                std::cout << "Telephone updated successfully!\n";
                break;
            }
            default:
                std::cout << "Invalid choice!\n";
                break;
            }
        }
        else {
            std::cout << "Sender with ID " << id << " does not exist.\n";
        }
    }

    void findSender() {
        system("CLS"); // Xóa màn hình
        int id;
        std::cout << "Enter Sender ID to find: ";
        std::cin >> id;
        std::cin.ignore(); // Ignore the newline character left by std::cin

        auto it = std::find_if(senders.begin(), senders.end(), [id](const Sender& s) {
            return s.senderID == id;
            });

        if (it != senders.end()) {
            it->displaySender();
        }
        else {
            std::cout << "Sender with ID " << id << " does not exist. Returning to main menu.\n";
        }
    }
};

void displayMenuSenderManagement(SenderManagement& manager) {
    int choice;
    do {
        system("CLS"); // Xóa màn hình
        std::cout << "Menu Sender Management:\n";
        std::cout << "1. Add a Sender\n";
        std::cout << "2. Print All Senders\n";
        std::cout << "3. Delete a Sender\n";
        std::cout << "4. Update Sender Details\n";
        std::cout << "5. Find a Sender\n";
        std::cout << "6. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            manager.addSender();
            break;
        case 2:
            manager.printAllSenders();
            break;
        case 3:
            manager.deleteSender(); // Allow interactive deletion by ID
            break;
        case 4:
            manager.updateSender();
            break;
        case 5:
            manager.findSender();
        case 6:
            std::cout << "Exiting...\n";
            break;
        default:
            std::cout << "Invalid choice! Please try again.\n";
            break;
        }
    } while (choice != 6);
}

class ReceiverManagement {
private:
    std::vector<Receiver> receivers;
public:
    void addReceiver() {
        system("CLS"); // Xóa màn hình
        std::string name, address;
        int id, tel;

        std::cout << "Enter Receiver ID: ";
        std::cin >> id;
        std::cin.ignore(); // Ignore the newline character left by std::cin

        // Check if the receiver ID already exists
        auto it = std::find_if(receivers.begin(), receivers.end(), [id](const Receiver& r) {
            return r.receiverID == id;
            });

        if (it != receivers.end()) {
            std::cout << "Receiver with ID " << id << " already exists. Please enter a new ID.\n";
            addReceiver(); // Recursive call to addReceiver to retry with a new ID
            return;
        }

        std::cout << "Enter Receiver Name: ";
        std::getline(std::cin, name);

        std::cout << "Enter Receiver Address: ";
        std::getline(std::cin, address);

        std::cout << "Enter Receiver Tel: ";
        std::cin >> tel;
        std::cin.ignore(); // Ignore the newline character left by std::cin

        // Create a new Receiver object and add it to the vector
        Receiver newReceiver(name, address, id, tel);
        receivers.push_back(newReceiver);

        std::cout << "Receiver added successfully!\n";
    }

    void printAllReceivers() const {
        system("CLS"); // Xóa màn hình
        std::cout << "All Receivers:\n";
        for (const auto& receiver : receivers) {
            receiver.displayReceiver();
            std::cout << "----------------\n";
        }
        system("pause");
    }

    void deleteReceiver() {
        system("CLS"); // Xóa màn hình
        int id;
        std::cout << "Enter Receiver ID to delete: ";
        std::cin >> id;
        auto it = std::find_if(receivers.begin(), receivers.end(), [id](const Receiver& r) {
            return r.receiverID == id;
            });

        if (it != receivers.end()) {
            receivers.erase(it); // Erase the receiver if found
            std::cout << "Receiver with ID " << id << " deleted successfully!\n";
        }
        else {
            std::cout << "Receiver with ID " << id << " does not exist.\n";
        }
    }

    void updateReceiver() {
        system("CLS"); // Xóa màn hình
        int id;
        std::cout << "Enter Receiver ID to update: ";
        std::cin >> id;
        auto it = std::find_if(receivers.begin(), receivers.end(), [id](const Receiver& r) {
            return r.receiverID == id;
            });

        if (it != receivers.end()) {
            Receiver& receiverToUpdate = *it;
            int choice;
            std::cout << "Receiver found! What do you want to update?\n";
            std::cout << "1. Name\n";
            std::cout << "2. Address\n";
            std::cout << "3. Telephone\n";
            std::cout << "Enter your choice: ";
            std::cin >> choice;
            std::cin.ignore(); // Ignore the newline character left by std::cin

            switch (choice) {
            case 1: {
                std::string newName;
                std::cout << "Enter new name: ";
                std::getline(std::cin, newName);
                receiverToUpdate.updateReceiverDetails(newName, receiverToUpdate.receiverAddress, receiverToUpdate.receiverTel);
                std::cout << "Name updated successfully!\n";
                break;
            }
            case 2: {
                std::string newAddress;
                std::cout << "Enter new address: ";
                std::getline(std::cin, newAddress);
                receiverToUpdate.updateReceiverDetails(receiverToUpdate.receiverName, newAddress, receiverToUpdate.receiverTel);
                std::cout << "Address updated successfully!\n";
                break;
            }
            case 3: {
                int newTel;
                std::cout << "Enter new telephone: ";
                std::cin >> newTel;
                receiverToUpdate.updateReceiverDetails(receiverToUpdate.receiverName, receiverToUpdate.receiverAddress, newTel);
                std::cout << "Telephone updated successfully!\n";
                break;
            }
            default:
                std::cout << "Invalid choice!\n";
                break;
            }
        }
        else {
            std::cout << "Receiver with ID " << id << " does not exist.\n";
        }
    }

    void findReceiver() {
        system("CLS"); // Xóa màn hình
        int id;
        std::cout << "Enter Receiver ID to find: ";
        std::cin >> id;
        std::cin.ignore(); // Ignore the newline character left by std::cin

        auto it = std::find_if(receivers.begin(), receivers.end(), [id](const Receiver& r) {
            return r.receiverID == id;
            });

        if (it != receivers.end()) {
            it->displayReceiver();
        }
        else {
            std::cout << "Receiver with ID " << id << " does not exist. Returning to main menu.\n";
        }
    }
};

void displayMenuReceiverManagement(ReceiverManagement& manager) {
    int choice;
    do {
        system("CLS"); // Xóa màn hình
        std::cout << "Menu Receiver Management:\n";
        std::cout << "1. Add a Receiver\n";
        std::cout << "2. Print All Receivers\n";
        std::cout << "3. Delete a Receiver\n";
        std::cout << "4. Update Receiver Details\n";
        std::cout << "5. Find a Receiver\n";
        std::cout << "6. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            manager.addReceiver();
            break;
        case 2:
            manager.printAllReceivers();
            break;
        case 3:
            manager.deleteReceiver(); // Allow interactive deletion by ID
            break;
        case 4:
            manager.updateReceiver();
            break;
        case 5:
            manager.findReceiver();
            break;
        case 6:
            std::cout << "Exiting...\n";
            break;
        default:
            std::cout << "Invalid choice! Please try again.\n";
            break;
        }
    } while (choice != 6);
}
// Main function
int main() {
    SenderManagement sm;
    ReceiverManagement rm;
    int choice;
    do {
        system("CLS"); // Xóa màn hình
        std::cout << "BIET DOI HIGH CODE" << std::endl;
        std::cout << "=======================MENU=========================\n";
        std::cout << "==            1. Sender Management                ==\n";
        std::cout << "==            2. Receiver Management              ==\n";
        std::cout << "==            3. Exit                             ==\n";
        std::cout << "====================================================\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore(); // Bỏ qua newline trong bộ đệm
        switch (choice) {
        case 1:
            displayMenuSenderManagement(sm);
            break;
        case 2:
            displayMenuReceiverManagement(rm);
            break;
        case 3:
            std::cout << "Exiting the program.\n";
            break;
        default:
            std::cout << "Invalid choice!\n";
            system("pause"); // Tạm dừng chương trình
            break;
        }
    } while (choice != 3);

    return 0;
}
