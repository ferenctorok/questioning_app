#include <questioningapp.h>
#include <results_window.h>


vector<Result *>* QuestioningApp::readResults(string filename)
{
    ifstream infile(filename);
    if (infile.is_open())
    {
        string error_msg = "";
        streampos oldpos;
        string head_buffer;
        string question_num;
        string correct_string;
        bool correct;
        string type;
        string num_of_trials;
        string question;
        string real_answer;
        vector<string> answer_options_vect;
        vector<string> given_answers;
        vector<Result *> *results = new vector<Result *>;

        // reading in the questions:
        while (!infile.eof()) {
            // empty vectors:
            answer_options_vect.clear();
            given_answers.clear();

            //jump back to last read line if there is still left from the file:
            infile.seekg(oldpos);
            question_num = get_text_after(infile, oldpos, error_msg, "QUESTION");
            if (question_num == "NOT_FOUND") return file_corrupted<Result>(error_msg);

            // reading whether the answer was correct or not:
            correct_string = get_text_after(infile, oldpos, error_msg, "correct:");
            if (correct_string == "NOT_FOUND") return file_corrupted<Result>(error_msg);
            correct = stoi(correct_string);

            // reading the number of trials:
            num_of_trials = get_text_after(infile, oldpos, error_msg, "trials:");
            if (num_of_trials == "NOT_FOUND") return file_corrupted<Result>(error_msg);

            // reading the type of the question:
            type = get_text_after(infile, oldpos, error_msg, "type:");
            if (type != "text" && type != "multi")
            {
                error_msg = "type must be either \"text\" or \"multi\"\n";
                error_msg += "received" + type;
                return file_corrupted<Result>(error_msg);
            }

            // reading the question:
            question = get_text_after(infile, oldpos, error_msg, "question:");
            if (question == "NOT_FOUND") return file_corrupted<Result>(error_msg);

            if (type == "multi")
            {
                // check whether there is the header answer_options:
                head_buffer = get_text_after(infile, oldpos, error_msg, "answer_options:");
                if (head_buffer == "NOT_FOUND") return file_corrupted<Result>(error_msg);

                // reading in the answer options:
                answer_options_vect = read_string_list(infile, oldpos, error_msg);
                if (answer_options_vect.empty()) return file_corrupted<Result>(error_msg);
            }

            // reading the real answer:
            real_answer = get_text_after(infile, oldpos, error_msg, "real_answer:");
            if (real_answer == "NOT_FOUND") return file_corrupted<Result>(error_msg);

            // finding the given answers header:
            head_buffer = get_text_after(infile, oldpos, error_msg, "given_answers:");
            if (head_buffer == "NOT_FOUND") return file_corrupted<Result>(error_msg);

            // reading the given answers:
            given_answers = read_string_list(infile, oldpos, error_msg);
            if (given_answers.empty()) return file_corrupted<Result>(error_msg);

            // adding the new Result object to the vector:
            results->push_back(new Result(question_num, correct, num_of_trials, type,
                                          question, real_answer, answer_options_vect,
                                          given_answers));

            // jumping over empty lines:
            getline(infile, question_num);
            oldpos = infile.tellg();
            while (question_num.find_first_not_of(" ") == string::npos && !infile.eof())
            {
                getline(infile, question_num);
            }
        }
        return results;
    }
    else return new vector<Result *>;
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

