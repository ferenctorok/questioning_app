#include <iostream>

using namespace std;


class Question
{
public:
    Question(string *question = nullptr);
    virtual ~Question();

    virtual bool isCorrectAnswer();
    string getQuestion(){return *question;}

protected:
    string *question;
};


class TextQuestion: public Question
{
public:
    TextQuestion(string *question = nullptr,
                 string *answer = nullptr);
    ~TextQuestion();

protected:
    string *answer;
};
