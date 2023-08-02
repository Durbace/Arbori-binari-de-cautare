#include <iostream>
#include <fstream>
#include<map>
#include<string>
std::string removePunctuation(std::string& word) {
	std::string result;
	for (auto c : word)
		if (std::isalpha(c))
			result += std::tolower(c);
	return result;
}
std::map<std::string, int> countWords() {
	std::ifstream fin("Text.txt");
	std::map<std::string, int> wordCounts;
	std::string word, cleanedWord;
	while (fin >> word) {
		cleanedWord = removePunctuation(word);
		if (!cleanedWord.empty()) {
			wordCounts[cleanedWord]++;
		}
	}
	fin.close();
	return wordCounts;
}
void display(std::map<std::string, int>wordCounts) {
	for (auto p : wordCounts)
		std::cout << p.first << ':' << p.second << std::endl;
}
int main() {
	std::map<std::string, int> wordCounts = countWords();
	display(wordCounts);
	return 0;
}