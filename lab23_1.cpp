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

void importDataFromFile(string filename, vector<string> &names, vector<int> &scores, vector<char> &grades){
    ifstream source(filename.c_str());
    string textline;
    while(getline(source, textline)){
        size_t colonPos = textline.find(':');
        

        string name = textline.substr(0, colonPos);
        size_t endPos = name.find_last_not_of(" \t\r\n");
        if(endPos != string::npos) name = name.substr(0, endPos + 1);
        
        string scoreStr = textline.substr(colonPos + 1);
        int a, b, c;
        sscanf(scoreStr.c_str(), "%d %d %d", &a, &b, &c);
        
        int total = a + b + c;
        
        names.push_back(name);
        scores.push_back(total);
        grades.push_back(score2grade(total));
    }
}

void getCommand(string &command, string &key){
    cout << "Please input your command: \n";
    string input;
    getline(cin, input);
    
    size_t spacePos = input.find_first_of(' ');
    if(spacePos == string::npos){
        command = input;
        key = "";
    }else{
        command = input.substr(0, spacePos);
        key = input.substr(spacePos + 1);
    }
}
void searchName(const vector<string> &names, const vector<int> &scores, const vector<char> &grades, string key){
    cout << "---------------------------------\n";
    bool found = false;
    for(size_t i = 0; i < names.size(); i++){
        if(toUpperStr(names[i]) == key){
            cout << names[i] << "'s score = " << scores[i] << "\n";
            cout << names[i] << "'s grade = " << grades[i] << "\n";
            found = true;
            break;
        }
    }
    if(!found){
        cout << "Cannot found.\n";
    }
    cout << "---------------------------------\n";
}
void searchGrade(const vector<string> &names, const vector<int> &scores, const vector<char> &grades, string key){
    cout << "---------------------------------\n";
    bool found = false;
    for(size_t i = 0; i < names.size(); i++){
        string gradeStr(1, grades[i]); 
        if(gradeStr == key){
            cout << names[i] << " (" << scores[i] << ")\n";
            found = true;
        }
    }
    if(!found){
        cout << "Cannot found.\n";
    }
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