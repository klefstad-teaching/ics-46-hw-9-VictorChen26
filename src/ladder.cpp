#include <iostream>
#include <fstream>
#include <queue>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <cmath>
#include "ladder.h"
using namespace std;

#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}

void error(string word1, string word2, string msg){
    cerr << word1 << word2 << ": " << msg << endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d){
    if(str1 == str2)
        return false;
    int n1 = str1.size();
    int n2 = str2.size();
    if (abs(n1 - n2) > 1)
        return false;
    int s1_index = 0, s2_index = 0, diff = 0;
    while(s1_index < n1 && s2_index < n2) {
        if(str1[s1_index] != s2[s2_index]) {
            diff++;
            if(diff > d)
                return false;
            if(n1 > n2)
                ++s1_index;
            else if(n1 < n2)
                ++s2_index;
            else {
                ++s1_index;
                ++s2_index;
            }
        } else {
            ++s1_index;
            ++s2_index;
        }
    }
    diff += (n1 - s1_index) + (n2 - s2_index);
    return diff == d;
}


bool is_adjacent(const string& word1, const string& word2){
    return edit_distance_within(word1, word2);
}
vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list){
    queue<vector<string>> ladderQueue;
    ladderQueue.push({begin_word});
    set<string> visited;
    
    visited.insert(begin_word);

    while (!ladderQueue.empty()){
        vector<string> ladder = ladderQueue.front();
        ladderQueue.pop();
        string last_word = ladder.back();
        for (const string &word : word_list) {
            if (is_adjacent(last_word, word) && visited.find(word) == visited.end()) {
                vector<string> newLadder = ladder;
                newLadder.push_back(word);
                visited.insert(word);
                if (word == end_word)
                    return newLadder;
                ladderQueue.push(newLadder);
            }
        }
    }
    return vector<string>();
}
void load_words(set<string> & word_list, const string& file_name){
    ifstream infile(filename);
    if (!infile)
        error(filename, "", "file cannot be opened.");
    string in;
    while (infile >> in)
        word_list.insert(word);
    file.close();
}

void print_word_ladder(const vector<string>& ladder){
    if (ladder.empty()) {
        cout << "No word ladder found." << endl;
        return;
    }
    cout << "Word ladder found: " << endl;
    for (size_t i = 0; i < ladder.size(); ++i) {
        cout << ladder[i];
        if (i < ladder.size() - 1)
            cout << " -> ";
    }
    cout << endl;
}
