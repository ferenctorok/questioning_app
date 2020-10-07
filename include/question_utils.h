#ifndef QUUESTION_UTILS_H
#define QUESTION_UTILS_H
#include <iostream>
#include <vector>

using namespace std;


class Question
{
public:
    Question(string *question = nullptr,
             string *type = nullptr);
    virtual ~Question();

    string getQuestion();
    string getType();
    virtual bool isCorrectAnswer(const string given_answer);
    virtual bool isCorrectAnswer(const vector<int> given_answer);

private:
    string *question;
    string *type;
};


class TextQuestion: public Question
{
public:
    TextQuestion(string *question = nullptr,
                 string *type = nullptr,
                 string *answer = nullptr);
    ~TextQuestion();

    bool isCorrectAnswer(const string *given_answer);

private:
    string *answer;
};


class MultiChoiceQuestion: public Question
{
public:
    MultiChoiceQuestion(string *question = nullptr,
                        string *type = nullptr,
                        vector<string *> *options = nullptr,
                        vector<int> *answer = nullptr);
    ~MultiChoiceQuestion();

    bool isCorrectAnswer(vector<int> *given_answer);
    vector<string *>* getOptions();
private:
    vector<string *> *options;
    vector<int> *answer;
};

#endif
