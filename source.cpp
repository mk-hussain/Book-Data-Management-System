#include<bits/stdc++.h>
using namespace std;

class Book{

private:
    int id;
    char title[20];
    float price;

public:
    // default constructor
    Book(){
        id = -1; //  data not initialized
    }
    
    void input(){
        cout<<"Enter Book Id : ";
        cin>>id;
        cout<<"Enter Book Title : ";
        cin.ignore();
        cin.getline(title,19);
        cout<<"Enter Book price : ";
        cin>>price;
        cout<<endl;
    }

    void print(){
       // book data must be initialized
       cout<<"Id = "<<id<<endl;
       cout<<"Title = "<<title<<endl;
       cout<<"price = "<<price<<endl;
       cout<<endl;
    }

    int store(){
        if(id == -1) return 0;// didnt store
        ofstream fout;
        fout.open("data.bin",ios::app|ios::binary);
        fout.write((char*)this,sizeof(*this));
        fout.close();
        return 1;// stored 
    }

	static void read(){
		//cout<<"reading"<<endl;
		ifstream fin;
		fin.open("data.bin",ios::in|ios::binary);
		Book b;
		fin.read((char*)&b,sizeof(b));
		while(!fin.eof()){
			b.print();
			fin.read((char*)&b,sizeof(b));
		}
	}

	static void search(){
	    char title[20];
	    cout<<"Enter a title : ";
		cin.ignore();
	    cin.getline(title,19);
		cout<<"All Books with title : "<<title<<" :-"<<endl;
		ifstream fin;
		fin.open("data.bin",ios::in|ios::binary);
		if(!fin) {
			cout<<"File Not found "<<endl;
			return ;
		}
		Book b;
		fin.read((char*)&b,sizeof(b));
		while(!fin.eof()){
			if(strcmp(title,b.title) == 0){
				b.print();
				cout<<endl;
			}
			fin.read((char*)&b,sizeof(b));
		}
		fin.close();
	}

	static void update(){
	    char title[20];
	    cout<<"Enter a title : ";
		cin.ignore();
	    cin.getline(title,19);

		fstream file;
		file.open("data.bin",ios::in|ios::out|ios::ate|ios::binary);
		// when file is open in update mode file pointer points to the last byte of the file
		file.seekp(0);// brings file pointer to start of the file
		Book b;
		file.read((char*)&b,sizeof(b));
		while(!file.eof()){
			if(strcmp(title,b.title) == 0){
			    b.print();
				b.input();
				long pos = file.tellp();
				file.seekp(pos - sizeof(b));
				file.write((char*)&b,sizeof(b));
				break;// only single update
			}
			file.read((char*)&b,sizeof(b));
		}
	}

	static void deleteBook(){
	    char title[20];
	    cout<<"Enter a title : ";
	    cin.ignore();
	    cin.getline(title,19);

		ifstream fin;
		ofstream fout;
		fin.open("data.bin",ios::in |ios::binary);
		fout.open("temp.bin",ios::out|ios::binary);
		Book b;
		fin.read((char*)&b,sizeof(b));
		while(!fin.eof()){
			if(strcmp(b.title,title)){
				// enter only when book title != given title
				fout.write((char*)&b,sizeof(b));
			}
			fin.read((char*)&b,sizeof(b));
		}

		fin.close();
		fout.close();

		remove("data.bin");
		rename("temp.bin","data.bin");

	}

};
int main(){
	bool stop = false;
	while(true){
		cout<<"What do u want to do ? "<<endl;
		cout<<"1 : Enter new Book \n2 : Read All Books \n3 : Search a Book \n4 : Update a Book \n5 : Delete a Book \n6 : Exit\n";
		int x;
		cin>>x;
		if(x >= 6) break;
		switch (x)
		{
			case 1:{
					   Book b;
					   b.input();
					   b.store();
					   break;
				   }
			case 2:{
					   Book::read();
					   break;
				   }
			case 3:{
					   Book::search();
					   break;
					   
				   }
			case 4:{
					   Book::update();
					   break;
				   }
			case 5:{
					   Book::deleteBook();
					   break;
				   }
			default :{
							 cout<<"do nothing"<<endl;
							 stop = true;
							 break;
						 }
		}
		if(stop) break;
	}
    return 0;
}
