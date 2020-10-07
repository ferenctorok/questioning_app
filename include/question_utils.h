#ifndef QUUESTION_UTILS_H
#define QUESTION_UTILS_H
#include <iostream>
#include <vector>

using namespace std;


template<class T>
class Question
{
public:
    Question(string *question = nullptr,
             T *answer = nullptr);
    ~Question();

    string getQuestion(){return *question;}
    bool isCorrectAnswer(const T &candidate_answer);

protected:
    string *question;
    T *answer;
};
#endif
