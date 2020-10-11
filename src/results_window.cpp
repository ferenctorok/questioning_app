#include <results_window.h>


Result::Result(string question_number,
               bool correct,
               string trials,
               string type,
               string question,
               string real_answer,
               vector<string> options,
               vector<string> given_answers)
{
    this->question_number = question_number;
    this->correct = correct;
    this->trials = trials;
    this->type = type;
    this->question = question;
    this->real_answer = real_answer;
    this->options = options;
    this->given_answers = given_answers;
}


ResultsWindow::ResultsWindow(vector<Result *> *results,
                             QWidget *parent):
    QWidget(parent)
{

}


ResultsWindow::~ResultsWindow() {delete results;}
