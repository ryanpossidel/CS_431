#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

int main(int argc, char *argv[]) {
     if(argc != 2) {
          cerr << "Provide a single filename." << endl;
          exit(EXIT_FAILURE);
     }

     ifstream f(argv[1], ios::binary | ios::ate);

     if(!f.is_open()) {
          perror("The file didn't open correctly");
          exit(EXIT_FAILURE);
     }

     iostream::pos_type size = f.tellg();
     char *buf = new char[size + (iostream::pos_type)1];
     f.seekg(0);

     // read the file all at once
     f.read(buf, size);
     buf[size] = '\0';
     f.close();
     
     //assigns some variables
     int line_no = 1;
     char *b = buf;
     int i = 0;
     while(*b != '\0') {
          if(*b != ' '){
               cout << "Line " << line_no << ": ";

               //determines if *b is a letter
               if(isalpha(*b)){

                    //makes a string consecutive letters
                    //assigns e=b and increments e until its not a character
                    //then makes a string out of it
                    char *e = b;
                    do{
                         e++;
                    }
                    while(isalpha(*e));

                    string s;
                    s.assign(b,e-b);
                    
                    //determines if it is a variable
                    if(islower(*b) && e-b ==1){
                         cout << "VARI " << "\"" << s << "\" " <<endl;
                    }
                    //determines if it 'is'
                    else if(s == "is"){
                         cout << "ASSI " << "\"" << s << "\"" <<endl;
                         b = e-1;
                    }
                    //determines if it is 'print'
                    else if(s == "print"){
                         cout << "PRIN " << "\"" << s << "\"" <<endl;
                         b = e-1;
                    }
                    //determines if its a special comment Cc cC
                    else if(*b=='C' && *(b+1) == 'c'){
                         while(*e != '\0' && *e != '\n' && *e != '\r' && *e != '-'){
                                   e++; 
                         }
                         s.assign(b, e-b);
                         size_t pos = s.find("cC");
                         if(pos != string::npos){
                              s.assign(b, pos + 2);
                              cout << "COMM " << "\"" << s << "\"" <<endl;
                              b += pos+1;
                         }
                         else{
                              cout << "HUH? " << "\"" << s << "\"" <<endl;
                              b = e-1;
                         }
                    }
                    //if not any HUH?
                    else{
                         cout << "HUH? " << "\"" << s << "\" " <<endl;
                         b = e-1;
                    }   
               }
               //determines if its a number
               else if(isdigit(*b)){
                    char *e = b;
                    do{
                         e++;
                    }
                    while(isdigit(*e));

                    string s;
                    s.assign(b,e-b);

                    cout << "NUMB " << "\"" << s << "\" " <<endl;
                    b = e-1;
               }
               //determines if its a newline or carriage return
               else if(*b == '\n') {
                    cout << "NEWL " << endl;
                    line_no++;
               }
               else if(*b == '\r') {
                    cout << "NEWL " << endl;
                    line_no++;
                    b++;
               }
               //determines if its a '+'
               else if(*b == '+'){
                    cout << "PLUS " << "\"" << *b << "\" " << endl;
               }
               //determines if its a '-'
               else if(*b == '-'){
                    cout << "HYPH " << "\"" << *b << "\" " << endl;
               }
               //determines if its a comment
               else if(*b == '#'){
                    cout << "COMM " << "\"";
                    while(*b != '\n' && *b != '\r' && *b != '\0'){
                         cout<< *b;
                         b++;
                    }
                    cout << "\"" << endl;
               }
               //If not any of them HUH?
               else{
                   cout << "HUH? " << "\"" << *b << "\" " << endl;
               }
          
          }
          b++;
     }

     delete[] buf;

     exit(EXIT_SUCCESS);
}