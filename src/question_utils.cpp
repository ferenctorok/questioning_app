#include <question_utils.h>

// Question:
// base class for questions.
Question::Question(string question,
                   string type,
                   int number,
                   int num_of_trials)
{
    this->question = question;
    this->type = type;
    this->number = number;
    this->num_of_trials = num_of_trials;
}


string Question::getQuestion() {return question;}

string Question::getType() {return type;}

int Question::getQuestionNum() {return number;}

int Question::getNumOfTrials() {return num_of_trials;}

void Question::useTrial() {used_trials++;}

bool Question::outOfTrials() {return (num_of_trials <= used_trials);}

int Question::getRemainingTrials() {return num_of_trials - used_trials;}


// TextQuestion(public Question):
// child class of Question for text answer based questions.
TextQuestion::TextQuestion(string question,
                           string type,
                           int number,
                           int num_of_trials,
                           string answer):
    Question(question, type, number, num_of_trials)
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
                                         int number,
                                         int num_of_trials,
                                         vector<string> options,
                                         vector<int> answer):
    Question(question, type, number, num_of_trials)
{
    this->options = options;
    this->answer = answer;
}


bool MultiChoiceQuestion::isCorrectAnswer(vector<int> given_answer)
{
    return (answer == given_answer);
}


vector<string>* MultiChoiceQuestion::getOptions()
{
    return &options;
}





