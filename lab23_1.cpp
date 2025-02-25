#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(const string &filename, vector<string> &names, vector<int> &scores, vector<char> &grades){
    ifstream source(filename);
    string textline;
    char format[] = "%[^:]: %d %d %d";
    char name[100];
    int a,b,c;
    while(getline(source,textline)){
        const char *text = textline.c_str();
        sscanf(text,format,name,&a,&b,&c);
        names.push_back(name);
        scores.push_back(a+b+c);
        grades.push_back(score2grade(a+b+c));
    }
    source.close();
}

void getCommand(string &command, string &key){
    string line;
    cout << "Please input your command: "<<endl;
    getline(cin,line);
    int idx = line.find_first_of(" ");
    command = line.substr(0,idx);
    key = line.substr(idx+1);

}

void searchName(const vector<string> names, vector<int> scores, vector<char> grades, string key){
    bool found = false;
    cout << "---------------------------------\n";
    for(unsigned i = 0; i < names.size(); i++){
        if(key == toUpperStr(names[i])){
            cout << names[i] << "'s score = " << scores[i] << endl;
            cout << names[i] << "'s grade = " << grades[i] << endl;
            found = true;
        }
    }
    if(!found) cout << "Cannot found." << endl;
    cout << "---------------------------------\n";

}

void searchGrade(vector<string> &names, vector<int> &scores, vector<char> &grades, string key){
    bool found = false;
    cout << "---------------------------------\n";
    for(unsigned i = 0; i < names.size(); i++){
        if(key[0] == grades[i]){
            cout << names[i] << " (" << scores[i] <<")"<< endl;
            found = true;
        }
    }
    if(!found) cout << "Cannot found." << endl;
    cout << "---------------------------------\n";
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}
