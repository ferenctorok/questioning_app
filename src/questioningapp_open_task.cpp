#include <questioningapp.h>
#include <new_questions.h>


vector<Question *>* QuestioningApp::readQuestions(string filename)
{
    ifstream infile(filename);
    if (infile.is_open())
    {
        string error_msg = "";
        streampos oldpos;
        string timestamp;
        string question_num_string;
        int question_num = 0;
        string type_string;
        string num_of_trials_string;
        int num_of_trials;
        string question_string;
        string answer_string;
        string head_answer_option_string;
        string answer_option_string;
        vector<string> answer_options_vect;
        vector<int> multi_answers_vect;
        vector<Question *> *questions_vect = new vector<Question *>;

        // reading the timestamp:
        timestamp = get_text_after(infile, oldpos, error_msg, "timestamp:");
        if (timestamp == "NOT_FOUND") return file_corrupted<Question>(error_msg);

        // we have to set oldpos after the timestamp line to enter the while cycle correctly:
        oldpos = infile.tellg();

        // reading in the questions:
        while (infile.good()) {
            // empty vectors:
            answer_options_vect.clear();
            multi_answers_vect.clear();

            //jump back to last read line if there is still left from the file:
            infile.seekg(oldpos);
            question_num_string = get_text_after(infile, oldpos, error_msg, "QUESTION");
            if (question_num_string == "NOT_FOUND") return file_corrupted<Question>(error_msg);

            // reading the number of trials:
            num_of_trials_string = get_text_after(infile, oldpos, error_msg, "trials:");
            if (num_of_trials_string == "NOT_FOUND") return file_corrupted<Question>(error_msg);
            num_of_trials = stoi(num_of_trials_string);

            // reading the type of the question:
            type_string = get_text_after(infile, oldpos, error_msg, "type:");
            if (type_string != "text" && type_string != "multi")
            {
                error_msg = "type must be either \"text\" or \"multi\"\n";
                error_msg += "received" + type_string;
                return file_corrupted<Question>(error_msg);
            }

            // reading the question:
            question_string = get_text_after(infile, oldpos, error_msg, "question:");
            if (question_string == "NOT_FOUND") return file_corrupted<Question>(error_msg);

            if (type_string == "text")
            {
                // reading the answer:
                answer_string = get_text_after(infile, oldpos, error_msg, "answer:");
                if (answer_string == "NOT_FOUND") return file_corrupted<Question>(error_msg);

                // adding the new question to the vector:
                questions_vect->push_back(new TextQuestion(question_string, type_string,
                                                           question_num, num_of_trials, answer_string));
            }
            else
            {
                // check whether there is the header answer_options:
                head_answer_option_string = get_text_after(infile, oldpos, error_msg, "answer_options:");
                if (head_answer_option_string == "NOT_FOUND") return file_corrupted<Question>(error_msg);

                // reading in the answer options:
                answer_options_vect = read_string_list(infile, oldpos, error_msg);
                if (answer_options_vect.empty()) return file_corrupted<Question>(error_msg);

                // reading the answers:
                answer_string = get_text_after(infile, oldpos, error_msg, "answers:");
                if (answer_string == "NOT_FOUND") return file_corrupted<Question>(error_msg);
                multi_answers_vect = get_multi_answers_from_string(answer_string);

                // adding the new question to the vector:
                questions_vect->push_back(new MultiChoiceQuestion(question_string, type_string, question_num,
                                                                  num_of_trials, answer_options_vect, multi_answers_vect));
            }
            // jumping over empty lines:
            getline(infile, question_num_string);
            oldpos = infile.tellg();
            while (question_num_string.find_first_not_of(" ") == string::npos && infile.good())
            {
                getline(infile, question_num_string);
            }

            question_num++;
        }
        infile.close();
        return questions_vect;
    }
    else return new vector<Question *>;
}
