#ifndef _CLASS_H_
#define _CLASS_H_
#include <string>
#include <vector>

class Text{
private:
	int skipWhitespace(int i, std::string s);
	void getText(std::string name);
public:
	Text();
	Text(std::string name);
	int getCountOfStrings();
	std::string getString(int n);
	int getCountOfWords(int n);
	std::string getWord(int n, int i);
protected:
	std::string error;
	bool check(int first, int second);
	std::vector<std::string> split(std::string s);
	std::string join(std::vector<std::string> words);
	std::vector<std::vector<std::string>> text;
};

class EditableText : public Text{
public:
	EditableText();
	EditableText(std::string name);
	void changeString(int n, std::string newString);
	void changeWord(int n, int i, std::string newWord);
	std::pair<int, int> getPos(std::string word);
	void printText();
};

class Menu{
private:
	EditableText poem;
	void getCountOfStrings();
	void getCountOfWords();
	void getWord();
	void getString();
	void changeString();
	void changeWord();
	void getPos();
	void printText();
public:
	Menu(std::string name);
	void start();
};

#endif