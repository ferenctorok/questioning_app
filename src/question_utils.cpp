#include <question_utils.h>

// Question:
// base class for questions.
Question::Question(string question,
                   string type)
{
    this->question = question;
    this->type = type;
}


string Question::getQuestion()
{
    return question;
}


string Question::getType()
{
    return type;
}


// TextQuestion(public Question):
// child class of Question for text answer based questions.
TextQuestion::TextQuestion(string question,
                           string type,
                           string answer):
    Question(question, type)
{
    this->answer = answer;
}


bool TextQuestion::isCorrectAnswer(const string given_answer)
{
    return (answer == given_answer);
}


// MultiChoiceQuestion(public Question):
// child class of Question for Multiple choice questions.
MultiChoiceQuestion::MultiChoiceQuestion(string question,
                                         string type,
                                         vector<string *> options,
                                         vector<int> answer):
    Question(question, type)
{
    this->options = options;
    this->answer = answer;
}


bool MultiChoiceQuestion::isCorrectAnswer(vector<int> given_answer)
{
    return (answer == given_answer);
}


vector<string *>* MultiChoiceQuestion::getOptions()
{
    return &options;
}





