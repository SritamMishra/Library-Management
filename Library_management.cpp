#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

// BOOK CLASS:

class Book{
public:
    int id;
    string title,author;
    bool available;

    Book(int _id, string _title, string _author){
        _id=id;
        _title=title;
        _author=author;
        available = true;
    }
    void display(){
        cout<<setw(5)<<id<<endl;
        cout<<setw(25)<<title<<endl;
        cout<<setw(25)<<author<<endl;
        cout<<setw(15)<<(available? "Available":"Borrowed")<<endl;  
    }
};

// LIBRARY CLASS:
class Library{
private:
    vector<Book>books;
    int nextID;

public:
    Library(){
        nextID;
        loadfromfile();
    }
    void addbook(string title, string author){
        books.push_back(Book(nextID++,title,author));
        cout<<"📚 Book Added Successfully! ";
        savetofile();
    }

// FILE HANDLING:

    void savetofile(){
        ofstream fout("library.txt");
        for(auto &book : books){
        fout<<book.id<<"|"
            <<book.title<<"|"
            <<book.author<<"|"
            <<book.available<<'\n';
        }
        fout.close();
    }
    
    void loadfromfile(){
        ifstream fin("library.txt");
        if(!fin) return;
        books.clear();
        string line;
        while (getline(fin, line)){
            stringstream ss(line);
            string idstr,title,author,availstr;
            getline(ss,idstr,'|');
            getline(ss,title,'|');
            getline(ss,author,'|');
            getline(ss, availstr,'|');
            Book b(stoi(idstr),title,author);
            b.available=(availstr == "1");
            books.push_back(b);
            nextID= stoi(idstr)+1;
        }
        fin.close();
    }
    void viewbook(){
        if(books.empty()){
            cout<<"📚 No Books in Library! ";
            return;
        }
        cout<<setw(5)<<"ID";
        cout<<setw(25)<<"Title";
        cout<<setw(25)<<"Author";
        cout<<setw(15)<<"Status"<<endl;
        cout<<string(70,'-')<<endl;

        for( auto &book: books){
            book.display();
        }
    }

    void searchbook(string keyboard){
        bool found = false;
        for(auto &book : books){
            if(book.title.find(keyboard) != string::npos || book.author.find(keyboard) != string::npos){
                if(!found){
                    cout<<setw(5)<<"ID"<<'\n';
                    cout<<setw(25)<<"Title"<<'\n';
                    cout<<setw(25)<<"Author"<<'\n';
                    cout<<setw(15)<<"Status"<<'\n';
                    cout<<string(70,'-')<<endl;
                }
                book.display();
                found = true;
            }
        }
        if(!found) cout<<"❌ No book found with keyword: "<<keyboard<<endl;
    }

    void borrowbook(int id){
        for(auto &book:books){
            if(book.id == id){
                if(book.available){
                    book.available=false;
                    cout<<"📕 You Borrowed! "<<book.title<<'\n';
                    savetofile();
                }else{
                    cout<<"Book already Borrowed! ";
                }
                return; 
            }
        }
        cout<<"❌ Book ID not found! ";
    }

    void returnbook(int id){
        for(auto &book:books){
            if(book.id == id){
                if (!book.available){
                    book.available=true;
                    cout << "📚 You returned \"" << book.title << "\".\n";
                    savetofile();
                }else{
                    cout<<"📚 This book wasnt borrowed!\n ";
                }
                return;
            }
            
        }
        cout<<"📚 Book ID was not found ❌ ";
    }

};


// MAIN: 
int main(){
    Library lib;
    int choice;
    string title,author,keyboard;
    int id;

    do{
        cout << "\n====== 📚 Library Management System ======\n";
        cout << "1. Add Book\n";
        cout << "2. View All Books\n";
        cout << "3. Search Book\n";
        cout << "4. Borrow Book\n";
        cout << "5. Return Book\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();

        switch(choice){
        case 1:
            cout<<"Enter Title: ";
            getline(cin,title);
            cout<<"Enter author: ";
            getline(cin,author);
            lib.addbook(title,author);
            break;

        case 2:
            lib.viewbook();
            break;

        case 3:
            cout<<"Keyboard: ";
            getline(cin,keyboard);
            lib.searchbook(keyboard);
            break;

        case 4:
            cout<<"Enter Book ID: ";
            cin>>id;
            lib.borrowbook(id);
            break;

        case 6:
            cout<<"👋 Exiting Goodbye! ";
            break;

        default:
            cout<<"Invalid Choice! ";
        }
    }   
    while(choice != 6);
    
    return 0;
}

