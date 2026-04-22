#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>

using namespace std;

// ========== ABSTRACT BASE CLASS ==========
class LibraryItem {
private:
    string title;
    string author;
    string dueDate;

public:
    // Constructor
    LibraryItem(string title = "", string author = "", string dueDate = "") {
        this->title = title;
        this->author = author;
        this->dueDate = dueDate;
    }
    
    // Virtual destructor
    virtual ~LibraryItem() {}
    
    // Pure virtual functions (Abstraction)
    virtual void checkOut() = 0;
    virtual void returnItem() = 0;
    virtual void displayDetails() const = 0;
    
    // Getters (Encapsulation)
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    string getDueDate() const { return dueDate; }
    
    // Setters (Encapsulation)
    void setTitle(string newTitle) { title = newTitle; }
    void setAuthor(string newAuthor) { author = newAuthor; }
    void setDueDate(string newDueDate) { dueDate = newDueDate; }
};

// ========== BOOK CLASS (Inheritance) ==========
class Book : public LibraryItem {
private:
    string isbn;
    int pageCount;
    string genre;

public:
    Book(string title = "", string author = "", string dueDate = "",
         string isbn = "", int pageCount = 0, string genre = "")
        : LibraryItem(title, author, dueDate) {
        this->isbn = isbn;
        this->pageCount = pageCount;
        this->genre = genre;
    }
    
    ~Book() {}
    
    void checkOut() override {
        cout << "📚 Book \"" << getTitle() << "\" has been checked out." << endl;
    }
    
    void returnItem() override {
        cout << "📚 Book \"" << getTitle() << "\" has been returned." << endl;
    }
    
    void displayDetails() const override {
        cout << "\n=== BOOK DETAILS ===" << endl;
        cout << "Title: " << getTitle() << endl;
        cout << "Author: " << getAuthor() << endl;
        cout << "ISBN: " << isbn << endl;
        cout << "Genre: " << genre << endl;
        cout << "Page Count: " << pageCount << endl;
        cout << "Due Date: " << getDueDate() << endl;
        cout << "===================" << endl;
    }
    
    // Additional getters
    string getIsbn() const { return isbn; }
    int getPageCount() const { return pageCount; }
    string getGenre() const { return genre; }
    
    void setIsbn(string newIsbn) { isbn = newIsbn; }
    void setPageCount(int newPageCount) { 
        if (newPageCount < 0) throw invalid_argument("Page count cannot be negative!");
        pageCount = newPageCount; 
    }
    void setGenre(string newGenre) { genre = newGenre; }
};

// ========== DVD CLASS (Inheritance) ==========
class DVD : public LibraryItem {
private:
    int duration; // in minutes
    string rating;
    string director;

public:
    DVD(string title = "", string author = "", string dueDate = "",
        int duration = 0, string rating = "", string director = "")
        : LibraryItem(title, author, dueDate) {
        this->duration = duration;
        this->rating = rating;
        this->director = director;
    }
    
    ~DVD() {}
    
    void checkOut() override {
        cout << "🎬 DVD \"" << getTitle() << "\" has been checked out." << endl;
    }
    
    void returnItem() override {
        cout << "🎬 DVD \"" << getTitle() << "\" has been returned." << endl;
    }
    
    void displayDetails() const override {
        cout << "\n=== DVD DETAILS ===" << endl;
        cout << "Title: " << getTitle() << endl;
        cout << "Director: " << director << endl;
        cout << "Duration: " << duration << " minutes" << endl;
        cout << "Rating: " << rating << endl;
        cout << "Due Date: " << getDueDate() << endl;
        cout << "==================" << endl;
    }
    
    int getDuration() const { return duration; }
    string getRating() const { return rating; }
    string getDirector() const { return director; }
    
    void setDuration(int newDuration) {
        if (newDuration < 0) throw invalid_argument("Duration cannot be negative!");
        duration = newDuration;
    }
    void setRating(string newRating) { rating = newRating; }
    void setDirector(string newDirector) { director = newDirector; }
};

// ========== MAGAZINE CLASS (Inheritance) ==========
class Magazine : public LibraryItem {
private:
    int issueNumber;
    string publisher;
    int month;
    int year;

public:
    Magazine(string title = "", string author = "", string dueDate = "",
             int issueNumber = 0, string publisher = "", int month = 0, int year = 0)
        : LibraryItem(title, author, dueDate) {
        this->issueNumber = issueNumber;
        this->publisher = publisher;
        this->month = month;
        this->year = year;
    }
    
    ~Magazine() {}
    
    void checkOut() override {
        cout << "📰 Magazine \"" << getTitle() << "\" has been checked out." << endl;
    }
    
    void returnItem() override {
        cout << "📰 Magazine \"" << getTitle() << "\" has been returned." << endl;
    }
    
    void displayDetails() const override {
        cout << "\n=== MAGAZINE DETAILS ===" << endl;
        cout << "Title: " << getTitle() << endl;
        cout << "Publisher: " << publisher << endl;
        cout << "Issue Number: " << issueNumber << endl;
        cout << "Date: " << month << "/" << year << endl;
        cout << "Due Date: " << getDueDate() << endl;
        cout << "=======================" << endl;
    }
    
    int getIssueNumber() const { return issueNumber; }
    string getPublisher() const { return publisher; }
    int getMonth() const { return month; }
    int getYear() const { return year; }
    
    void setIssueNumber(int newIssueNumber) {
        if (newIssueNumber < 0) throw invalid_argument("Issue number cannot be negative!");
        issueNumber = newIssueNumber;
    }
    void setPublisher(string newPublisher) { publisher = newPublisher; }
    void setMonth(int newMonth) {
        if (newMonth < 1 || newMonth > 12) throw invalid_argument("Month must be between 1 and 12!");
        month = newMonth;
    }
    void setYear(int newYear) { year = newYear; }
};

// ========== PATRON CLASS ==========
class Patron {
private:
    int patronId;
    string name;
    string email;
    string phone;
    vector<string> borrowedItems;
    
public:
    Patron(int id = 0, string name = "", string email = "", string phone = "") {
        this->patronId = id;
        this->name = name;
        this->email = email;
        this->phone = phone;
    }
    
    // Getters
    int getPatronId() const { return patronId; }
    string getName() const { return name; }
    string getEmail() const { return email; }
    string getPhone() const { return phone; }
    vector<string> getBorrowedItems() const { return borrowedItems; }
    
    // Setters
    void setName(string newName) { name = newName; }
    void setEmail(string newEmail) { email = newEmail; }
    void setPhone(string newPhone) { phone = newPhone; }
    
    void borrowItem(string title) {
        borrowedItems.push_back(title);
    }
    
    void returnItem(string title) {
        auto it = find(borrowedItems.begin(), borrowedItems.end(), title);
        if (it != borrowedItems.end()) {
            borrowedItems.erase(it);
        }
    }
    
    void displayDetails() const {
        cout << "\n=== PATRON DETAILS ===" << endl;
        cout << "ID: " << patronId << endl;
        cout << "Name: " << name << endl;
        cout << "Email: " << email << endl;
        cout << "Phone: " << phone << endl;
        cout << "Borrowed Items: " << borrowedItems.size() << endl;
        for (const auto& item : borrowedItems) {
            cout << "  - " << item << endl;
        }
        cout << "=====================" << endl;
    }
};

// ========== TRANSACTION CLASS ==========
class Transaction {
private:
    int transactionId;
    string itemTitle;
    int patronId;
    string checkoutDate;
    string dueDate;
    string returnDate;
    bool isReturned;
    
public:
    Transaction(int id = 0, string itemTitle = "", int patronId = 0,
                string checkoutDate = "", string dueDate = "") {
        this->transactionId = id;
        this->itemTitle = itemTitle;
        this->patronId = patronId;
        this->checkoutDate = checkoutDate;
        this->dueDate = dueDate;
        this->returnDate = "";
        this->isReturned = false;
    }
    
    void markReturned(string returnDate) {
        this->returnDate = returnDate;
        isReturned = true;
    }
    
    void displayDetails() const {
        cout << "\n=== TRANSACTION DETAILS ===" << endl;
        cout << "Transaction ID: " << transactionId << endl;
        cout << "Item: " << itemTitle << endl;
        cout << "Patron ID: " << patronId << endl;
        cout << "Checkout Date: " << checkoutDate << endl;
        cout << "Due Date: " << dueDate << endl;
        cout << "Return Date: " << (isReturned ? returnDate : "Not returned yet") << endl;
        cout << "Status: " << (isReturned ? "Returned" : "Active") << endl;
        cout << "==========================" << endl;
    }
    
    bool getIsReturned() const { return isReturned; }
    string getItemTitle() const { return itemTitle; }
    int getPatronId() const { return patronId; }
};

// ========== LIBRARY CLASS ==========
class Library {
private:
    vector<LibraryItem*> items;
    vector<Patron> patrons;
    vector<Transaction> transactions;
    int nextItemId;
    int nextPatronId;
    int nextTransactionId;
    
public:
    Library() {
        nextItemId = 0;
        nextPatronId = 100;
        nextTransactionId = 1000;
    }
    
    ~Library() {
        // Clean up dynamically allocated memory
        for (auto item : items) {
            delete item;
        }
    }
    
    // Add item to library (Polymorphism)
    void addItem(LibraryItem* item) {
        if (item == nullptr) {
            throw invalid_argument("Cannot add null item!");
        }
        items.push_back(item);
        cout << "✅ Item \"" << item->getTitle() << "\" added successfully!" << endl;
    }
    
    // Remove item from library
    void removeItem(string title) {
        auto it = find_if(items.begin(), items.end(), [&title](LibraryItem* item) {
            return item->getTitle() == title;
        });
        
        if (it != items.end()) {
            delete *it;
            items.erase(it);
            cout << "✅ Item \"" << title << "\" removed successfully!" << endl;
        } else {
            throw runtime_error("Item not found!");
        }
    }
    
    // Search for item
    LibraryItem* searchItem(string title) {
        for (auto item : items) {
            if (item->getTitle() == title) {
                return item;
            }
        }
        return nullptr;
    }
    
    // Add patron
    void addPatron(string name, string email, string phone) {
        Patron patron(nextPatronId++, name, email, phone);
        patrons.push_back(patron);
        cout << "✅ Patron \"" << name << "\" added with ID: " << patron.getPatronId() << endl;
    }
    
    // Search patron
    Patron* searchPatron(int id) {
        for (auto& patron : patrons) {
            if (patron.getPatronId() == id) {
                return &patron;
            }
        }
        return nullptr;
    }
    
    // Checkout item
    void checkoutItem(string itemTitle, int patronId, string checkoutDate, string dueDate) {
        LibraryItem* item = searchItem(itemTitle);
        if (!item) {
            throw runtime_error("Item not found!");
        }
        
        Patron* patron = searchPatron(patronId);
        if (!patron) {
            throw runtime_error("Patron not found!");
        }
        
        // Create transaction
        Transaction transaction(nextTransactionId++, itemTitle, patronId, checkoutDate, dueDate);
        transactions.push_back(transaction);
        
        // Update patron's borrowed items
        patron->borrowItem(itemTitle);
        
        // Update item's due date
        item->setDueDate(dueDate);
        
        // Polymorphic behavior
        item->checkOut();
        
        cout << "✅ Item checked out successfully!" << endl;
    }
    
    // Return item
    void returnItem(string itemTitle, int patronId, string returnDate) {
        LibraryItem* item = searchItem(itemTitle);
        if (!item) {
            throw runtime_error("Item not found!");
        }
        
        Patron* patron = searchPatron(patronId);
        if (!patron) {
            throw runtime_error("Patron not found!");
        }
        
        // Find and update transaction
        for (auto& transaction : transactions) {
            if (transaction.getItemTitle() == itemTitle && 
                transaction.getPatronId() == patronId &&
                !transaction.getIsReturned()) {
                transaction.markReturned(returnDate);
                break;
            }
        }
        
        // Update patron's borrowed items
        patron->returnItem(itemTitle);
        
        // Polymorphic behavior
        item->returnItem();
        
        cout << "✅ Item returned successfully!" << endl;
    }
    
    // Display all items
    void displayAllItems() const {
        if (items.empty()) {
            cout << "No items in the library." << endl;
            return;
        }
        
        cout << "\n========== LIBRARY CATALOG ==========" << endl;
        for (auto item : items) {
            item->displayDetails();
        }
        cout << "=====================================" << endl;
    }
    
    // Display all patrons
    void displayAllPatrons() const {
        if (patrons.empty()) {
            cout << "No patrons registered." << endl;
            return;
        }
        
        cout << "\n========== LIBRARY PATRONS ==========" << endl;
        for (const auto& patron : patrons) {
            patron.displayDetails();
        }
        cout << "=====================================" << endl;
    }
    
    // Display all transactions
    void displayAllTransactions() const {
        if (transactions.empty()) {
            cout << "No transactions recorded." << endl;
            return;
        }
        
        cout << "\n========== TRANSACTION HISTORY ==========" << endl;
        for (const auto& transaction : transactions) {
            transaction.displayDetails();
        }
        cout << "=========================================" << endl;
    }
};

// ========== MAIN FUNCTION WITH MENU ==========
int main() {
    Library library;
    int choice;
    
    cout << "=========================================" << endl;
    cout << "   WELCOME TO LIBRARY MANAGEMENT SYSTEM  " << endl;
    cout << "=========================================" << endl;
    
    // Pre-populate with some sample data
    try {
        library.addItem(new Book("The C++ Programming Language", "Bjarne Stroustrup", "", "978-0321563842", 1368, "Programming"));
        library.addItem(new Book("Clean Code", "Robert C. Martin", "", "978-0132350884", 464, "Software Engineering"));
        library.addItem(new DVD("Inception", "Christopher Nolan", "", 148, "PG-13", "Christopher Nolan"));
        library.addItem(new DVD("The Matrix", "Wachowski Brothers", "", 136, "R", "Lana Wachowski"));
        library.addItem(new Magazine("National Geographic", "National Geographic Society", "", 456, "National Geographic", 3, 2024));
        library.addItem(new Magazine("Time Magazine", "Time USA", "", 789, "Time", 4, 2024));
        
        library.addPatron("John Doe", "john@example.com", "123-456-7890");
        library.addPatron("Jane Smith", "jane@example.com", "098-765-4321");
    } catch (const exception& e) {
        cout << "Error setting up sample data: " << e.what() << endl;
    }
    
    do {
        cout << "\n========== MAIN MENU ==========" << endl;
        cout << "1. Display All Items" << endl;
        cout << "2. Add New Item" << endl;
        cout << "3. Remove Item" << endl;
        cout << "4. Search Item" << endl;
        cout << "5. Display All Patrons" << endl;
        cout << "6. Add New Patron" << endl;
        cout << "7. Checkout Item" << endl;
        cout << "8. Return Item" << endl;
        cout << "9. Display Transaction History" << endl;
        cout << "0. Exit" << endl;
        cout << "==============================" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        
        try {
            switch (choice) {
                case 1: {
                    library.displayAllItems();
                    break;
                }
                case 2: {
                    int itemType;
                    cout << "\n--- Add New Item ---" << endl;
                    cout << "1. Book" << endl;
                    cout << "2. DVD" << endl;
                    cout << "3. Magazine" << endl;
                    cout << "Enter item type: ";
                    cin >> itemType;
                    cin.ignore();
                    
                    string title, author, dueDate;
                    cout << "Enter title: ";
                    getline(cin, title);
                    cout << "Enter author/director/publisher: ";
                    getline(cin, author);
                    cout << "Enter due date (YYYY-MM-DD): ";
                    getline(cin, dueDate);
                    
                    if (itemType == 1) {
                        string isbn, genre;
                        int pageCount;
                        cout << "Enter ISBN: ";
                        getline(cin, isbn);
                        cout << "Enter page count: ";
                        cin >> pageCount;
                        cin.ignore();
                        cout << "Enter genre: ";
                        getline(cin, genre);
                        
                        if (pageCount < 0) throw invalid_argument("Page count cannot be negative!");
                        library.addItem(new Book(title, author, dueDate, isbn, pageCount, genre));
                    } 
                    else if (itemType == 2) {
                        int duration;
                        string rating, director;
                        cout << "Enter duration (minutes): ";
                        cin >> duration;
                        cin.ignore();
                        cout << "Enter rating: ";
                        getline(cin, rating);
                        cout << "Enter director: ";
                        getline(cin, director);
                        
                        if (duration < 0) throw invalid_argument("Duration cannot be negative!");
                        library.addItem(new DVD(title, author, dueDate, duration, rating, director));
                    } 
                    else if (itemType == 3) {
                        int issueNumber, month, year;
                        string publisher;
                        cout << "Enter issue number: ";
                        cin >> issueNumber;
                        cout << "Enter month (1-12): ";
                        cin >> month;
                        cout << "Enter year: ";
                        cin >> year;
                        cin.ignore();
                        cout << "Enter publisher: ";
                        getline(cin, publisher);
                        
                        if (issueNumber < 0) throw invalid_argument("Issue number cannot be negative!");
                        if (month < 1 || month > 12) throw invalid_argument("Month must be between 1 and 12!");
                        library.addItem(new Magazine(title, author, dueDate, issueNumber, publisher, month, year));
                    }
                    break;
                }
                case 3: {
                    string title;
                    cin.ignore();
                    cout << "Enter item title to remove: ";
                    getline(cin, title);
                    library.removeItem(title);
                    break;
                }
                case 4: {
                    string title;
                    cin.ignore();
                    cout << "Enter item title to search: ";
                    getline(cin, title);
                    LibraryItem* item = library.searchItem(title);
                    if (item) {
                        item->displayDetails();
                    } else {
                        cout << "Item not found!" << endl;
                    }
                    break;
                }
                case 5: {
                    library.displayAllPatrons();
                    break;
                }
                case 6: {
                    string name, email, phone;
                    cin.ignore();
                    cout << "Enter patron name: ";
                    getline(cin, name);
                    cout << "Enter email: ";
                    getline(cin, email);
                    cout << "Enter phone: ";
                    getline(cin, phone);
                    library.addPatron(name, email, phone);
                    break;
                }
                case 7: {
                    string itemTitle, checkoutDate, dueDate;
                    int patronId;
                    cin.ignore();
                    cout << "Enter item title: ";
                    getline(cin, itemTitle);
                    cout << "Enter patron ID: ";
                    cin >> patronId;
                    cin.ignore();
                    cout << "Enter checkout date (YYYY-MM-DD): ";
                    getline(cin, checkoutDate);
                    cout << "Enter due date (YYYY-MM-DD): ";
                    getline(cin, dueDate);
                    library.checkoutItem(itemTitle, patronId, checkoutDate, dueDate);
                    break;
                }
                case 8: {
                    string itemTitle, returnDate;
                    int patronId;
                    cin.ignore();
                    cout << "Enter item title: ";
                    getline(cin, itemTitle);
                    cout << "Enter patron ID: ";
                    cin >> patronId;
                    cin.ignore();
                    cout << "Enter return date (YYYY-MM-DD): ";
                    getline(cin, returnDate);
                    library.returnItem(itemTitle, patronId, returnDate);
                    break;
                }
                case 9: {
                    library.displayAllTransactions();
                    break;
                }
                case 0: {
                    cout << "Thank you for using Library Management System!" << endl;
                    break;
                }
                default: {
                    cout << "Invalid choice! Please try again." << endl;
                }
            }
        } catch (const invalid_argument& e) {
            cout << "❌ Invalid Input Error: " << e.what() << endl;
        } catch (const runtime_error& e) {
            cout << "❌ Runtime Error: " << e.what() << endl;
        } catch (const exception& e) {
            cout << "❌ Unexpected Error: " << e.what() << endl;
        } catch (...) {
            cout << "❌ Unknown error occurred!" << endl;
        }
        
    } while (choice != 0);
    
    return 0;
}