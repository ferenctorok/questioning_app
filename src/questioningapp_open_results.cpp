#include <questioningapp.h>
#include <results_window.h>


vector<Result *>* QuestioningApp::readResults(string filename)
{
    ifstream infile(filename);
    if (infile.is_open())
    {
        string error_msg = "";
        streampos oldpos;
        string question_num;
        string type;
        string num_of_trials;
        string question;
        string real_text_answer;
        vector<string> given_text_answers;
        string head_answer_option;
        string answer_option;
        vector<string> answer_options_vect;
        string real_multi_answers;
        vector<string> given_multi_answers;
        vector<Result *> *results = new vector<Result *>;

        // reading in the questions:
        while (!infile.eof()) {
            // empty vectors:
            answer_options_vect.clear();
            given_text_answers.clear();
            given_multi_answers.clear();

            //jump back to last read line if there is still left from the file:
            infile.seekg(oldpos);
            question_num = get_text_after(infile, oldpos, error_msg, "QUESTION");
            if (question_num == "NOT_FOUND") return file_corrupted<Result>(error_msg);

            // reading the number of trials:
            num_of_trials_string = get_text_after(infile, oldpos, error_msg, "trials:");
            if (num_of_trials_string == "NOT_FOUND") return file_corrupted<Result>(error_msg);
            num_of_trials = stoi(num_of_trials_string);

            // reading the type of the question:
            type_string = get_text_after(infile, oldpos, error_msg, "type:");
            if (type_string != "text" && type_string != "multi") return file_corrupted<Result>(error_msg);

            // reading the question:
            question_string = get_text_after(infile, oldpos, error_msg, "question:");
            if (question_string == "NOT_FOUND") return file_corrupted<Result>(error_msg);

            if (type_string == "text")
            {
                // reading the answer:
                answer_string = get_text_after(infile, oldpos, error_msg, "answer:");
                if (answer_string == "NOT_FOUND") return file_corrupted<Result>(error_msg);

                // adding the new question to the vector:
                questions_vect->push_back(new TextQuestion(question_string, type_string,
                                                           question_num, num_of_trials, answer_string));
            }
            else
            {
                // check whether there is the header answer_options:
                head_answer_option_string = get_text_after(infile, oldpos, error_msg, "answer_options:");
                if (head_answer_option_string == "NOT_FOUND") return file_corrupted<Result>(error_msg);

                // reading in the answer options:
                answer_option_string = get_text_after(infile, oldpos, error_msg, "*");
                if (answer_option_string == "NOT_FOUND") return file_corrupted<Result>(error_msg);
                while (answer_option_string != "NOT_FOUND")
                {
                    answer_options_vect.push_back(answer_option_string);
                    answer_option_string = get_text_after(infile, oldpos, error_msg, "*");
                }
                //set back the file to the previous line for further reading:
                infile.seekg(oldpos);

                // reading the answers:
                answer_string = get_text_after(infile, oldpos, error_msg, "answers:");
                if (answer_string == "NOT_FOUND") return file_corrupted<Result>(error_msg);
                multi_answers_vect = get_multi_answers_from_string(answer_string);

                // adding the new question to the vector:
                questions_vect->push_back(new MultiChoiceQuestion(question_string, type_string, question_num,
                                                                  num_of_trials, answer_options_vect, multi_answers_vect));
            }
            // jumping over empty lines:
            getline(infile, question_num_string);
            oldpos = infile.tellg();
            while (question_num_string.find_first_not_of(" ") == string::npos && !infile.eof())
            {
                getline(infile, question_num_string);
            }

            question_num++;
        }
        return questions_vect;
    }
    else return new vector<Question *>;
}


vector<int> QuestioningApp::get_multi_answers_from_string(string str)
{
    vector<int> answers;
    size_t pos_end = str.find(",");
    size_t pos_beg(0);
    string actual_string;
    while (pos_end != string::npos)
    {
        actual_string = str.substr(pos_beg, pos_end - pos_beg);
        answers.push_back(std::stoi(actual_string));
        pos_beg = pos_end + 1;
        pos_end = str.find(",", pos_beg);
    }
    return answers;
}

