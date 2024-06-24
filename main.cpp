#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

struct Date { int day, month, year; };

enum ShipmentStatus { Pending, InTransit, Delivered };
enum PaymentStatus { Unpaid, Paid };

std::string dateToString(const Date& date) {
    return std::to_string(date.day) + "/" + std::to_string(date.month) + "/" + std::to_string(date.year);
}

class Person {
private:
    std::string name, address;
    int id, tel, totalOrders;
 public:
    Person(const std::string& name, const std::string& address, int id, int tel, int totalOrders = 0)
        : name(name), address(address), id(id), tel(tel), totalOrders(totalOrders){}

    void displayPerson() const {
        std::cout << "ID: " << id << "\nName: " << name << "\nAddress: " << address << "\nTel: " << tel << "\nTotal orders: " << totalOrders << "\n";
    }

    void displayPersonForShipment() const {
        std::cout << "ID: " << id << "\nName: " << name << "\nAddress: " << address << "\nTel: " << tel <<"\n";
    }

    void updateDetails(const std::string& name, const std::string& address, int tel) {
        this->name = name;
        this->address = address;
        this->tel = tel;
    }

    int getId() const {
        return id;
    }

    friend class SRSManagement;
};

class Shipment {
private:
    int shipmentId;
    Date sendDate, receiveDate;
    PaymentStatus paymentStatus;
    ShipmentStatus status;
    Person sender, receiver;
    std::string goodsInfo;
public:
    Shipment(int shipmentId, const Date& sendDate, const Date& receiveDate, const Person& sender, const Person& receiver, const std::string& goodsInfo, ShipmentStatus status, PaymentStatus paymentStatus)
        : shipmentId(shipmentId), sendDate(sendDate), receiveDate(receiveDate), sender(sender), receiver(receiver), goodsInfo(goodsInfo), status(status), paymentStatus(paymentStatus) {}

    int getShipmentId() const { 
        return shipmentId;
    }

    Person& getSender() {
        return sender;
    }

    Person& getReceiver() {
        return receiver;
    }

    void displayShipment() const {
        std::cout << "Shipment ID: " << shipmentId << "\n" << "Receive Date: " << dateToString(sendDate) << "\n" << "Delivery Date: " << dateToString(receiveDate) << "\n";
        std::cout << "-----Sender information:\n";
        sender.displayPersonForShipment();
        std::cout << "-----Sender information:\n";
        receiver.displayPersonForShipment();
        std::cout << "Goods Info: " << goodsInfo << "\n" << "Shipment Status: " << (status == Pending ? "Pending" : status == InTransit ? "In Transit" : "Delivered") << "\n" << "Payment Status: " << (paymentStatus == Unpaid ? "Unpaid" : "Paid") << "\n";
    }

    friend class SRSManagement;
};

class SRSManagement {
private:
    std::vector<Person> senders;
    std::vector<Person> receivers;
    std::vector<Shipment> shipments;
public:
    void addPerson(std::vector<Person>& list, const std::string& role) {
        system("CLS");
        std::string name, address;
        int id, tel;

        std::cout << "Enter " << role << " ID: ";
        std::cin >> id;
        std::cin.ignore();

        auto it = std::find_if(list.begin(), list.end(), [id](const Person& p) {
            return p.id == id;
            });

        if (it != list.end()) {
            std::cout << role << " with ID " << id << " already exists. Please enter a new ID.\n";
            system("pause");
            return;
        }

        std::cout << "Enter " << role << " Name: ";
        std::getline(std::cin, name);

        std::cout << "Enter " << role << " Address: ";
        std::getline(std::cin, address);

        std::cout << "Enter " << role << " Tel: ";
        std::cin >> tel;
        std::cin.ignore();

        list.emplace_back(name, address, id, tel);
        std::cout << role << " added successfully!\n";
        system("pause");
    }

    void printAllPersons(const std::vector<Person>& list, const std::string& role) const {
        system("CLS");
        std::cout << "All " << role << "s:\n";
        for (const auto& person : list) {
            person.displayPerson();
            std::cout << "----------------\n";
        }
        system("pause");
    }

    void deletePerson(std::vector<Person>& list, const std::string& role) {
        system("CLS");
        int id;
        std::cout << "Enter " << role << " ID to delete: ";
        std::cin >> id;

        auto it = std::find_if(list.begin(), list.end(), [id](const Person& p) {
            return p.id == id;
            });

        if (it != list.end()) {
            list.erase(it);
            std::cout << role << " with ID " << id << " deleted successfully!\n";
            system("pause");
        }
        else {
            std::cout << role << " with ID " << id << " does not exist.\n";
            system("pause");
        }
    }

    void updatePerson(std::vector<Person>& list, const std::string& role) {
        system("CLS");
        int id;
        std::cout << "Enter " << role << " ID to update: ";
        std::cin >> id;

        auto it = std::find_if(list.begin(), list.end(), [id](const Person& p) {
            return p.id == id;
            });

        if (it != list.end()) {
            Person& personToUpdate = *it;
            int choice;
            std::cout << role << " found! What do you want to update?\n";
            std::cout << "1. Name\n2. Address\n3. Telephone\nEnter your choice: ";
            std::cin >> choice;
            std::cin.ignore();

            switch (choice) {
            case 1: {
                std::string newName;
                std::cout << "Enter new name: ";
                std::getline(std::cin, newName);
                personToUpdate.updateDetails(newName, personToUpdate.address, personToUpdate.tel);
                std::cout << "Name updated successfully!\n";
                system("pause");
                break;
            }
            case 2: {
                std::string newAddress;
                std::cout << "Enter new address: ";
                std::getline(std::cin, newAddress);
                personToUpdate.updateDetails(personToUpdate.name, newAddress, personToUpdate.tel);
                std::cout << "Address updated successfully!\n";
                system("pause"); 
                break;
            }
            case 3: {
                int newTel;
                std::cout << "Enter new telephone: ";
                std::cin >> newTel;
                personToUpdate.updateDetails(personToUpdate.name, personToUpdate.address, newTel);
                std::cout << "Telephone updated successfully!\n";
                system("pause"); 
                break;
            }
            default:
                std::cout << "Invalid choice!\n";
                system("pause"); 
                break;
            }
        }
        else {
            std::cout << role << " with ID " << id << " does not exist.\n";
            system("pause");
        }
    }

    void findPerson(const std::vector<Person>& list, const std::string& role) const {
        system("CLS");
        int id;
        std::cout << "Enter " << role << " ID to find: ";
        std::cin >> id;
        std::cin.ignore();

        auto it = std::find_if(list.begin(), list.end(), [id](const Person& p) {
            return p.id == id;
            });

        if (it != list.end()) {
            it->displayPerson();
            system("pause");
        }
        else {
            std::cout << role << " with ID " << id << " does not exist. Returning to main menu.\n";
            system("pause");
        }
    }
    
    void addShipment(std::vector<Shipment>& list, std::vector<Person>& senders, std::vector<Person>& receivers) {
        system("CLS");
        int shipmentId, senderId, receiverId, status, pstatus;
        std::string goods;
        Date sDate, rDate;

        std::cout << "Enter the information for new Shipment" << std::endl;

        auto findPersonById = [](std::vector<Person>& persons, int id) -> Person& {
            for (auto& person : persons) {
                if (person.getId() == id) {
                    return person;
                }
            }
            throw std::runtime_error("Person with ID not found.");
        };

        auto findShipmentById = [&list](int id) -> bool {
            for (auto& shipment : list) {
                if (shipment.getShipmentId() == id) {
                    return true;
                }
            }
            return false;
        };

        std::cout << "Enter the Sender ID: ";
        std::cin >> senderId;

        Person* sender = nullptr;
        try {
            sender = &findPersonById(senders, senderId);
        }
        catch (const std::runtime_error& e) {
            std::cerr << e.what() << std::endl;
            system("pause");
            return;
        }

        std::cout << "Enter the Receiver ID: ";
        std::cin >> receiverId;

        Person* receiver = nullptr;
        try {
            receiver = &findPersonById(receivers, receiverId);
        }
        catch (const std::runtime_error& e) {
            std::cerr << e.what() << std::endl;
            system("pause");
            return;
        }

        std::cout << "Enter the Shipment ID: ";
        std::cin >> shipmentId;

        if (findShipmentById(shipmentId)) {
            std::cerr << "Shipment with ID " << shipmentId << " already exists." << std::endl;
            system("pause");
            return;
        }

        std::cout << "Send Date (day month year): "; std::cin >> sDate.day >> sDate.month >> sDate.year;
        std::cout << "Receive Date (day month year): "; std::cin >> rDate.day >> rDate.month >> rDate.year;
        std::cin.ignore();
        std::cout << "Goods information: "; std::getline(std::cin, goods);
        std::cout << "Shipment Status: Received (0) / InTransit (1) / Delivered (2): "; std::cin >> status;
        std::cout << "Payment Status: Unpaid (0) / Paid (1): "; std::cin >> pstatus;

        Shipment newShipment(shipmentId, sDate, rDate, *sender, *receiver, goods, static_cast<ShipmentStatus>(status), static_cast<PaymentStatus>(pstatus));
        list.push_back(newShipment);

        sender->totalOrders++;
        receiver->totalOrders++;


        std::cout << "Shipment added successfully!" << std::endl;
        system("pause");
    }

    void printAllShipments(const std::vector<Shipment> list) const {
        system("CLS");
        std::cout << "All shipments:\n";
        for (const auto& shipment : list) {
            shipment.displayShipment();
            std::cout << "----------------\n";
        }
        system("pause");
    }

    void deleteShipment(std::vector<Shipment>& list, std::vector<Person>& senders, std::vector<Person>& receivers) {
        system("CLS");
        int id;
        std::cout << "Enter Shipment ID to delete: ";
        std::cin >> id;

        auto it = std::find_if(list.begin(), list.end(), [id](const Shipment& s) { return s.getShipmentId() == id; });

        if (it != list.end()) {
            
            auto findPersonById = [](std::vector<Person>& persons, int id) -> Person& {
                for (auto& person : persons) {
                    if (person.getId() == id) {
                        return person;
                    }
                }
                throw std::runtime_error("Person with ID not found.");
            };

            Person* sender = nullptr;
            try {
                sender = &findPersonById(senders, it->sender.id);
            }
            catch (const std::runtime_error& e) {
                std::cerr << e.what() << std::endl;
                system("pause");
                return;
            }

            Person* receiver = nullptr;
            try {
                receiver = &findPersonById(receivers, it->receiver.id);
            }
            catch (const std::runtime_error& e) {
                std::cerr << e.what() << std::endl;
                system("pause");
                return;
            }

            sender->totalOrders--;
            receiver->totalOrders--;

            list.erase(it);
            std::cout << "Shipment with ID " << id << " deleted successfully!\n";
            system("pause");
        }
        else {
            std::cout << "Shipment with ID " << id << " does not exist.\n";
            system("pause");
        }
    }

    void updateShipment(std::vector<Shipment>& list) {
        system("CLS");
        int id;
        std::cout << "Enter Shipment ID to update: ";
        std::cin >> id;

        auto it = std::find_if(list.begin(), list.end(), [id](const Shipment& s) { return s.shipmentId == id; });

        // Check if shipment is found
        if (it != list.end()) {
            int choice;
            bool updateAgain = true;

            while (updateAgain) {
                system("CLS");
                // Menu for choosing the field to update
                std::cout << "\nSelect field to update for Shipment ID " << id << ":" << std::endl;
                std::cout << "1. Send Date\n";
                std::cout << "2. Receive Date\n";
                std::cout << "3. Status\n";
                std::cout << "4. Payment Status\n";
                std::cout << "5. Goods Info\n";
                std::cout << "6. Exit update\n";
                std::cout << "Enter your choice: ";
                std::cin >> choice;

                switch (choice) {
                case 1: {
                    // Update Send Date
                    Date newSendDate;
                    std::cout << "Enter new Send Date (day month year): ";
                    std::cin >> newSendDate.day >> newSendDate.month >> newSendDate.year;
                    it->sendDate = newSendDate;
                    std::cout << "Shipment with ID " << id << "'s Send Date updated successfully!" << std::endl;
                    system("pause");
                    break;
                }
                case 2: {
                    // Update Receive Date
                    Date newReceiveDate;
                    std::cout << "Enter new Receive Date (day month year): ";
                    std::cin >> newReceiveDate.day >> newReceiveDate.month >> newReceiveDate.year;
                    it->receiveDate = newReceiveDate;
                    std::cout << "Shipment with ID " << id << "'s Receive Date updated successfully!" << std::endl;
                    system("pause");
                    break;
                }
                case 3: {
                    // Update Status
                    std::cout << "Enter new Shipment Status: Pending (0) / InTransit (1) / Delivered (2): ";
                    int statusChoice; std::cin >> statusChoice; it->status = static_cast<ShipmentStatus>(statusChoice);
                    std::cout << "Shipment with ID " << id << "'s Status updated successfully!" << std::endl;
                    system("pause");
                    break;
                }
                case 4: {
                    // Update Payment Status
                    std::cout << "Enter new Payment Status: Unpaid (0) / Paid (1): ";
                    int pstatusChoice; std::cin >> pstatusChoice; it->paymentStatus = static_cast<PaymentStatus>(pstatusChoice);
                    std::cout << "Shipment with ID " << id << "'s Payment Status updated successfully!" << std::endl;
                    system("pause");
                    break;
                }
                case 5: {
                    // Update Goods Info
                    std::string newGoodsInfo;
                    std::cout << "Enter new Goods Info: ";
                    // Consider using std::getline to handle spaces in input
                    std::cin.ignore();
                    std::getline(std::cin, newGoodsInfo); // Consume newline character from previous input
                    it->goodsInfo = newGoodsInfo;
                    std::cout << "Shipment with ID " << id << "'s Goods Info updated successfully!" << std::endl;
                    system("pause");
                    break;
                }
                case 6:
                    updateAgain = false;
                    break;
                default:
                    std::cout << "Invalid choice. Please try again." << std::endl;
                }
            }

            // Optional: Confirmation message
            std::cout << "Shipment with ID " << id << " updated successfully!" << std::endl;
        }
        else {
            std::cout << "Shipment with ID " << id << " not found!" << std::endl;
            system("pause");
        }
    }

    void findShipment(std::vector<Shipment>& list) const {
        system("CLS");
        int id;
        std::cout << "Enter Shipment ID to find: ";
        std::cin >> id;

        auto it = std::find_if(list.begin(), list.end(), [id](const Shipment& s) {
            return s.getShipmentId() == id;
            });

        if (it != list.end()) {
            it->displayShipment();
            system("pause");
        }
        else {
            std::cout << "Shipment with ID " << id << " does not exist. Returning to main menu.\n";
            system("pause");
        }
    }

    friend void displayMenuSRManagement(SRSManagement& manager);
    friend void displaySenderMenu(SRSManagement& manager);
    friend void displayReceiverMenu(SRSManagement& manager);
    friend void displayShipmentMenu(SRSManagement& manager);
};

void displayMenuSRManagement(SRSManagement& manager) {
    int choice;
    do {
        system("CLS");
        std::cout << "Main Menu:\n";
        std::cout << "1. Sender Management\n2. Receiver Management\n3. Shipment Management\n4. Exit\nEnter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            displaySenderMenu(manager);
            break;
        case 2:
            displayReceiverMenu(manager);
            break;
        case 3:
            displayShipmentMenu(manager);
        case 4:
            std::cout << "Exiting...\n";
            break;
        default:
            std::cout << "Invalid choice! Please try again.\n";
            system("pause");
            break;
        }
    } while (choice != 4);
}

void displaySenderMenu(SRSManagement& manager) {
    int choice;
    do {
        system("CLS");
        std::cout << "Sender Management Menu:\n";
        std::cout << "1. Add a Sender\n2. Print All Senders\n3. Delete a Sender\n4. Update Sender Details\n";
        std::cout << "5. Find a Sender\n6. Return to Main Menu\nEnter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            manager.addPerson(manager.senders, "Sender");
            break;
        case 2:
            manager.printAllPersons(manager.senders, "Sender");
            break;
        case 3:
            manager.deletePerson(manager.senders, "Sender");
            break;
        case 4:
            manager.updatePerson(manager.senders, "Sender");
            break;
        case 5:
            manager.findPerson(manager.senders, "Sender");
            break;
        case 6:
            return;
        default:
            std::cout << "Invalid choice! Please try again.\n";
            system("pause");
            break;
        }
    } while (choice != 6);
}

void displayReceiverMenu(SRSManagement& manager) {
    int choice;
    do {
        system("CLS");
        std::cout << "Receiver Management Menu:\n";
        std::cout << "1. Add a Receiver\n2. Print All Receivers\n3. Delete a Receiver\n4. Update Receiver Details\n";
        std::cout << "5. Find a Receiver\n6. Return to Main Menu\nEnter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            manager.addPerson(manager.receivers, "Receiver");
            break;
        case 2:
            manager.printAllPersons(manager.receivers, "Receiver");
            break;
        case 3:
            manager.deletePerson(manager.receivers, "Receiver");
            break;
        case 4:
            manager.updatePerson(manager.receivers, "Receiver");
            break;
        case 5:
            manager.findPerson(manager.receivers, "Receiver");
            break;
        case 6:
            return;
        default:
            std::cout << "Invalid choice! Please try again.\n";
            system("pause");
            break;
        }
    } while (choice != 6);
}

void displayShipmentMenu(SRSManagement& manager) {
    int choice;
    do {
        system("CLS");
        std::cout << "Shipment Management Menu:\n";
        std::cout << "1. Add a Shipment\n2. Print All Shipments\n3. Delete a Shipment\n4. Update Shipment Details\n";
        std::cout << "5. Find a Shipments\n6. Return to Main Menu\nEnter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            manager.addShipment(manager.shipments, manager.senders, manager.receivers);
            break;
        case 2:
            manager.printAllShipments(manager.shipments);
            break;
        case 3:
            manager.deleteShipment(manager.shipments, manager.senders, manager.receivers);
            break;
        case 4:
            manager.updateShipment(manager.shipments);
            break;
        case 5:
            manager.findShipment(manager.shipments);
            break;
        case 6:
            return;
        default:
            std::cout << "Invalid choice! Please try again.\n";
            system("pause");
            break;
        }
    } while (choice != 6);
}

int main() {
    SRSManagement srsm;
    displayMenuSRManagement(srsm);
    return 0;
}
