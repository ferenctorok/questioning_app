#include <QApplication>

#include <questioningapp.h>
#include <question_utils.h>

int main(int argc, char *argv[])
{
    string *question1 = new string("yolo");
    string *question2 = new string("yolo");
    string *answer1 = new string("yolo");
    vector<int> *answer2 = new vector<int> {1, 2, 3};

    Question<string> q1(question1, answer1);
    Question<vector<int>> q2(question2, answer2);

    if (q1.isCorrectAnswer("yolo")) cout << "yolo1\n";
    if (q2.isCorrectAnswer({1, 2, 3})) cout << "yolo2\n";

    QApplication a(argc, argv);
    QuestioningApp w;
    w.show();
    return a.exec();
}
