#include <iostream>
#include <vector>

using namespace std;


template<class T>
class Question
{
public:
    Question(string *question = nullptr,
             T *answer = nullptr)
    {
        this->question = question;
        this->answer = answer;
    }
    ~Question(){delete question, answer;}

    string getQuestion(){return *question;}
    bool isCorrectAnswer(const T &candidate_answer) {
        return (*answer == candidate_answer);
    }

protected:
    string *question;
    T *answer;
};
