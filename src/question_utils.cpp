#include <question_utils.h>


template <class T>
Question<T>::Question(string *question,
                      T *answer)
{
    this->question = question;
    this->answer = answer;
}
// explicit instanciation:
template Question<string>::Question(string *, string *);
template Question<vector<int>>::Question(string *, vector<int> *);


template <class T>
Question<T>::~Question()
{
    delete question;
    delete answer;
}
// explicit instanciation:
template Question<string>::~Question();
template Question<vector<int>>::~Question();


template <class T>
bool Question<T>::isCorrectAnswer(const T &candidate_answer)
{
    return (*answer == candidate_answer);
}
// explicit instanciation:
template bool Question<string>::isCorrectAnswer(const string &);
template bool Question<vector<int>>::isCorrectAnswer(const vector<int> &);
