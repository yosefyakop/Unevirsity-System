#include <iostream>
#include <string>
#include <stack>
#include <queue>
using namespace std;

class Book {
public:
    string title, author, ISBN;
    Book(string t, string a, string i) {
        title = t;
        author = a;
        ISBN = i;
    }
};

struct fictionNode {
    Book* book;
    fictionNode* next;
    fictionNode(Book* b) {
        book = b;
        next = NULL;
    }
};

struct NonFictionNode {
    Book* book;
    NonFictionNode* next;
    NonFictionNode* prev;
    NonFictionNode(Book* b) {
        book = b;
        next = NULL;
        prev = NULL;
    }
};

class FictionSLL {
    fictionNode* head;
public:
    FictionSLL() {
        head = NULL;
    }
    void addBook(Book* book) {
        fictionNode* newNode = new fictionNode(book);
        newNode->next = head;
        head = newNode;
    }
    bool removeBook(string isbn) {
        fictionNode* temp = head;
        fictionNode* prev = NULL;
        while (temp != NULL && temp->book->ISBN != isbn) {
            prev = temp;
            temp = temp->next;
        }
        if (temp == NULL) return false;
        if (prev == NULL)
            head = temp->next;
        else
            prev->next = temp->next;
        delete temp;
        return true;
    }
    Book* searchBook(string item) {
        fictionNode* temp = head;
        while (temp != NULL) {
            if (temp->book->title == item || temp->book->ISBN == item)
                return temp->book;
            temp = temp->next;
        }
        return NULL;
    }
    void display() {
        fictionNode* temp = head;
        while (temp != NULL) {
            cout << "Title: " << temp->book->title
                 << ", Author: " << temp->book->author
                 << ", ISBN: " << temp->book->ISBN << endl;
            temp = temp->next;
        }
    }
};

class NonFictionDLL {
    NonFictionNode* head;
public:
    NonFictionDLL() {
        head = NULL;
    }
    void addBook(Book* book) {
        NonFictionNode* newNode = new NonFictionNode(book);
        newNode->next = head;
        if (head != NULL)
            head->prev = newNode;
        head = newNode;
    }
    bool removeBook(string isbn) {
        NonFictionNode* temp = head;
        while (temp != NULL && temp->book->ISBN != isbn) {
            temp = temp->next;
        }
        if (temp == NULL) return false;
        if (temp->prev != NULL)
            temp->prev->next = temp->next;
        else
            head = temp->next;
        if (temp->next != NULL)
            temp->next->prev = temp->prev;
        delete temp;
        return true;
    }
    Book* searchBook(string item) {
        NonFictionNode* temp = head;
        while (temp != NULL) {
            if (temp->book->title == item || temp->book->ISBN == item)
                return temp->book;
            temp = temp->next;
        }
        return NULL;
    }
    void display() {
        NonFictionNode* temp = head;
        while (temp != NULL) {
            cout << "Title: " << temp->book->title
                 << ", Author: " << temp->book->author
                 << ", ISBN: " << temp->book->ISBN << endl;
            temp = temp->next;
        }
    }
};

class RecentlyAddedStack {
    stack<Book*> recentBooks;
public:
    void pushBook(Book* book) {
        if (recentBooks.size() == 5) recentBooks.pop();
        recentBooks.push(book);
    }
    void display() {
        stack<Book*> tempStack = recentBooks;
        cout << "Recently Added Books:" << endl;
        while (!tempStack.empty()) {
            Book* book = tempStack.top();
            cout << "Title: " << book->title << endl;
            tempStack.pop();
        }
    }
};

class BorrowQueue {
    queue<Book*> borrowQueue;
public:
    void enqueueBook(Book* book) {
        if (borrowQueue.size() == 10) borrowQueue.pop();
        borrowQueue.push(book);
    }
    void display() {
        queue<Book*> tempQueue = borrowQueue;
        cout << "Borrowing History:" << endl;
        while (!tempQueue.empty()) {
            Book* book = tempQueue.front();
            cout << "Title: " << book->title << endl;
            tempQueue.pop();
        }
    }
};

class Library {
    FictionSLL fictionList;
    NonFictionDLL nonFictionList;
    RecentlyAddedStack recentStack;
    BorrowQueue borrowQueue;
public:
    void addBook(string type, string title, string author, string ISBN) {
        if (type != "fiction" && type != "nonfiction") {
            cout << "Invalid book type. Please enter 'fiction' or 'nonfiction'.\n";
            return;
        }
        Book* book = new Book(title, author, ISBN);
        if (type == "fiction")
            fictionList.addBook(book);
        else if (type == "nonfiction")
            nonFictionList.addBook(book);
        recentStack.pushBook(book);
        cout << "Book added successfully!" << endl;
    }
    void removeBook(string type, string ISBN) {
        bool removed = false;
        if (type == "fiction")
            removed = fictionList.removeBook(ISBN);
        else if (type == "nonfiction")
            removed = nonFictionList.removeBook(ISBN);
        if (removed)
            cout << "Book removed successfully!" << endl;
        else
            cout << "Book not found!" << endl;
    }
    void searchBook(string type, string key) {
        Book* book = NULL;
        if (type == "fiction")
            book = fictionList.searchBook(key);
        else if (type == "nonfiction")
            book = nonFictionList.searchBook(key);
        if (book)
            cout << "Found: Title: " << book->title
                 << ", Author: " << book->author
                 << ", ISBN: " << book->ISBN << endl;
        else
            cout << "Book not found!" << endl;
    }
    void viewRecentBooks() {
        recentStack.display();
    }
    void viewBorrowHistory() {
        borrowQueue.display();
    }
    void borrowBook(string type, string ISBN) {
        Book* book = NULL;
        if (type == "fiction")
            book = fictionList.searchBook(ISBN);
        else if (type == "nonfiction")
            book = nonFictionList.searchBook(ISBN);
        if (book) {
            borrowQueue.enqueueBook(book);
            cout << "Book borrowed: Title: " << book->title << endl;
        } else {
            cout << "Book not found!" << endl;
        }
    }
};

int main() {
    Library library;
    int choice;
    string type, title, author, ISBN, key;
    do {
        cout << "\nMenu:\n1. Add Book\n2. Remove Book\n3. Search Book\n4. View Recently Added Books\n5. View Borrowing History\n6. Borrow Book\n7. Exit\nEnter choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "Enter type (fiction/nonfiction), title, author, and ISBN: ";
                cin >> type >> title >> author >> ISBN;
                library.addBook(type, title, author, ISBN);
                break;
            case 2:
                cout << "Enter type (fiction/nonfiction) and ISBN to remove: ";
                cin >> type >> ISBN;
                library.removeBook(type, ISBN);
                break;
            case 3:
                cout << "Enter type (fiction/nonfiction) and title or ISBN to search: ";
                cin >> type >> key;
                library.searchBook(type, key);
                break;
            case 4:
                library.viewRecentBooks();
                break;
            case 5:
                library.viewBorrowHistory();
                break;
            case 6:
                cout << "Enter type (fiction/nonfiction) and ISBN to borrow: ";
                cin >> type >> ISBN;
                library.borrowBook(type, ISBN);
                break;
        }
    } while (choice != 7);
    return 0;
}
