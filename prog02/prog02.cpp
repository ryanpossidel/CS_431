/*CS 431 Prog2
Language: C++
Compiler: g++
*/
#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

int main(int argc, char *argv[]){
	ifstream f(argv[1]);
	int state_cnt;
	int init_state;	
	
	f >> state_cnt >> init_state;
	bool final[state_cnt + 1] = {false};
	int final_cnt;
	f >> final_cnt;
	for(int i = 0; i < final_cnt; i++){
		int s;
		f >> s;
		final[s] = true;
	}
	string alphabet;
	f >> alphabet;
	
	int alphabet_cnt = alphabet.length();
	int trans[state_cnt + 1][alphabet_cnt];
	//assigns the 0 row in the transition table to all 0s
	for(int i = 0; i < alphabet_cnt; i++){
		trans[0][i] = 0;
	}
	//assigns the transition table from the file
	for(int s = 1; s <= state_cnt; s++){
		for(int i = 0; i < alphabet_cnt; i++){
			f >> trans[s][i];
		}
	}
	
	// Determines if the string is valid using the transition table
	string line;
	while(f >> line){
		int curr_state = init_state;
		int sequence[line.length()];
		for(int i = 0; i < line.length(); i++){
				int x = alphabet.find(line[i]);
				if(trans[curr_state][x] != 0){
					curr_state = trans[curr_state][x];
					sequence[i] = curr_state;
				}
				else{
					curr_state = 0;
					break;
				}
		}
		if(final[curr_state]){
			cout << "Y" << " " << line << " " << init_state << " ";
			for(int i = 0; i < line.length(); i++){
					cout << sequence[i] << " ";
			}
			cout << endl;
		}else{
			cout << "N" << " " << line << endl;
		}
	}
	
	f.close();
	
	return EXIT_SUCCESS;
}