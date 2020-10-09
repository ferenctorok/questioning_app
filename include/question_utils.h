#ifndef QUESTION_UTILS_H
#define QUESTION_UTILS_H
#include <iostream>
#include <vector>

using namespace std;


// Question:
// base class for questions.
class Question
{
public:
    Question(string question = "",
             string type = "",
             int number = 0);
    virtual ~Question() {};

    string getQuestion();
    string getType();
    virtual vector<string>* getOptions() {};
    virtual bool isCorrectAnswer(const string given_answer) {};
    virtual bool isCorrectAnswer(const vector<int> given_answer) {};

private:
    string question;
    string type;
    int number;
};


// TextQuestion(public Question):
// child class of Question for text answer based questions.
class TextQuestion: public Question
{
public:
    TextQuestion(string question = "",
                 string type = "",
                 int number = 0,
                 string answer = "");
    ~TextQuestion() {};

    bool isCorrectAnswer(const string given_answer);

private:
    string answer;
};


// MultiChoiceQuestion(public Question):
// child class of Question for Multiple choice questions.
class MultiChoiceQuestion: public Question
{
public:
    MultiChoiceQuestion(string question = "",
                        string type = "",
                        int number = 0,
                        vector<string> options = vector<string>(),
                        vector<int> answer = vector<int>());
    ~MultiChoiceQuestion() {};

    bool isCorrectAnswer(vector<int> given_answer);
    vector<string>* getOptions();

private:
    vector<string> options;
    vector<int> answer;
};

#endif
