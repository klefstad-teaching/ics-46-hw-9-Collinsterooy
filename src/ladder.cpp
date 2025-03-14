#include "ladder.h"

using namespace std;

void error(string word1, string word2, string msg)
{
	cerr << "error: " << word1 << " " << word2 << " " << msg;
}
bool edit_distance_within(const std::string& str1, const std::string& str2, int d)
{
	int sz1 = str1.size();
int sz2 = str2.size();


if (abs(sz1 - sz2) > d) return false;

vector<vector<int>> track(sz1 + 1, vector<int>(sz2 + 1, 0));

for (int i = 0; i <= sz1; ++i)
{
	track[i][0] = i;
}
	
for (int j = 0; j <= sz2; ++j)
{
	track[0][j] = j;
}
	

for (int i = 1; i <= sz1; ++i)
{
	for (int j = 1; j <= sz2; ++j) 
	{
		if (str1[i - 1] == str2[j - 1]) 
		{
			track[i][j] = track[i - 1][j - 1]; 
		}
		else 
		{
			track[i][j] = 1 + min({
				track[i - 1][j - 1], 
				track[i][j - 1],     
				track[i - 1][j]      
				});
		}
	}
}

return track[sz1][sz2] <= d;

}

bool is_adjacent(const string& word1, const string& word2)
{

	return (edit_distance_within(word1, word2, 1));

}
vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list)
{
	if (begin_word == end_word) return { begin_word };

	queue<vector<string>> ladder_queue;
	ladder_queue.push({ begin_word });

	set<string> visited;
	visited.insert(begin_word);

	while (!ladder_queue.empty()) {
		vector<string> ladder = ladder_queue.front();
		ladder_queue.pop();

		string last_word = ladder.back();

		for (const string& word : word_list) {
			if (is_adjacent(last_word, word) && visited.find(word) == visited.end()) {
				visited.insert(word);

				vector<string> new_ladder = ladder;
				new_ladder.push_back(word);

				if (word == end_word) {
					return new_ladder;
				}

				ladder_queue.push(new_ladder);
			}
		}
	}

	return {}; 

}

void load_words(set<string>& word_list, const string& file_name)
{
	ifstream inputFile(file_name);

	if (!inputFile)
		error("Cant", " Open", file_name);


	string word;


	while (inputFile >> word)
	{
		word_list.insert(word);
	}
		
	inputFile.close();

}
void print_word_ladder(const vector<string>& ladder)
{
	if (ladder.empty())
	{
		error("No", "words in ", "ladder");

		return;

	}

	for (int i = 0; i < ladder.size(); ++i)
	{
		if (i > 0) cout << " -> ";
		cout << ladder[i];
	
	}


}
void verify_word_ladder()
{
	set<string> word_list;

	load_words(word_list, "src/words.txt");

	my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);

	my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);

	my_assert(generate_word_ladder("code", "data", word_list).size() == 6);

	my_assert(generate_word_ladder("work", "play", word_list).size() == 6);

	my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);

	my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);


}