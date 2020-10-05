#include <question_utils.h>


Question::Question(string *question)
{
    this->question = question;
}


Question::~Question()
{
    delete question;
}
