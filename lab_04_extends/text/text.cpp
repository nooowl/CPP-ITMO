#include <string>
#include <iostream>
#include <fstream>
#include "class.h"

bool Text::check(int first, int second){
	error = "ERROR!";
	if (first < second){
		return false;
	}
	return true;
}

int Text::skipWhitespace(int i, std::string s){
	while (i < s.length() && s[i] == ' '){
		i++;
	}
	return i;
}

std::vector<std::string> Text::split(std::string s){
	std::vector<std::string> newString;
	int i = 0;
	int d = 0;
	while (s[i] != '\0'){
		if (s[i] == ' '){
			newString.push_back(s.substr(i - d, d));
			i = skipWhitespace(i, s);
			d = 0;
			continue;
		}
		d++;
		i++;
	}
	if (d != 0) newString.push_back(s.substr(i - d, d));
	return newString;
}

void Text::getText(std::string name){
	std::ifstream file(name);
	while (!file.eof()) {
		std::string help;
		std::getline(file, help);
		text.push_back(split(help));
	}
}

std::string Text::join(std::vector<std::string> words){
	std::string res = "";
	for (int i = 0; i < words.size(); i++)
		res += words[i] + ' ';
	return res;
}

Text::Text(){};

Text::Text(std::string name){
	getText(name);
}

int Text::getCountOfStrings(){
	return text.size();
}

std::string Text::getString(int n){
	if (check(text.size(), n))
		return join(text[n - 1]);
	return error;
}

int Text::getCountOfWords(int n){
	if (check(text.size(), n))
		return text[n - 1].size();
	return 0;
}

std::string Text::getWord(int n, int i){
	if (check(text.size(), n)){
		if (check(text[n].size(), i))
			return text[n - 1][i - 1];
	}
	return error;
}

EditableText::EditableText() : Text(){};

EditableText::EditableText(std::string name) : Text(name){}

void EditableText::changeString(int n, std::string newString){
	if (check(text.size(), n))
		text[n - 1] = split(newString);
	return;
}

void EditableText::changeWord(int n, int i, std::string newWord){
	if (check(text.size(), n)){
		if (check(text[n].size(), i))
			text[n - 1][i - 1] = newWord;
	}
	return;
}

std::pair<int, int> EditableText::getPos(std::string word){
	for (int i = 0; i < text.size(); i++)
		for (int j = 0; j < text[i].size();j++)
			if (text[i][j] == word){
				return std::make_pair(i + 1, j + 1);
			}
	return std::make_pair(0, 0);
}

void EditableText::printText(){
	for (int i = 0; i < text.size(); i++)
		std::cout << join(text[i]) << '\n';
}

Menu::Menu(std::string name){
	poem = EditableText(name);
}

void Menu::start(){
	std::string s;
	poem.printText();
	while (s != "--end"){
		std::cin >> s;
		if (s == "--countOfStrings")
			getCountOfStrings();
		if (s == "--countOfWords")
			getCountOfWords();
		if (s == "--string")
			getString();
		if (s == "--word")
			getWord();
		if (s == "--changeString")
			changeString();
		if (s == "--changeWord")
			changeWord();
		if (s == "--position")
			getPos();
	}
}

void Menu::getCountOfStrings(){
	std::cout << poem.getCountOfStrings() << "\n";
}

void Menu::getCountOfWords(){
	int n;
	std::cin >> n;
	std::cout << poem.getCountOfWords(n) << "\n";
}

void Menu::getString(){
	int n;
	std::cin >> n;
	std::cout << poem.getString(n) << "\n";
}

void Menu::getWord(){
	int n, i;
	std::cin >> n >> i;
	std::cout << poem.getWord(n, i) << "\n";
}

void Menu::changeString(){
	int n;
	std::string s;
	std::cin >> n;
	std::getline(std::cin, s);
	poem.changeString(n, s);
	poem.printText();
}

void Menu::changeWord(){
	int n, i;
	std::string s;
	std::cin >> n >> i;
	std::cin >> s;
	poem.changeWord(n, i, s);
	poem.printText();
}

void Menu::getPos(){
	std::string s;
	std::cin >> s;
	std::cout << poem.getPos(s).first << " " << poem.getPos(s).second << "\n";
}