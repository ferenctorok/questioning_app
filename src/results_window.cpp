#include <results_window.h>


Result::Result(string question_number,
               bool correct,
               string trials,
               string type,
               string question,
               string real_text_answer,
               string given_text_answer,
               vector<string> options,
               string real_multi_answer,
               vector<string> given_multi_answers)
{
    this->question_number = question_number;
    this->correct = correct;
    this->trials = trials;
    this->type = type;
    this->question = question;
    this->real_text_answer = real_text_answer;
    this->given_text_answer = given_text_answer;
    this->options = options;
    this->real_multi_answer = real_multi_answer;
    this->given_multi_answers = given_multi_answers;
}
