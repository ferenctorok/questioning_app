#include <questioningapp.h>
#include <results.h>


vector<Result *>* QuestioningApp::readResults(string filename)
{
    ifstream infile(filename, ios_base::binary);
    if (infile.is_open())
    {
        string section_marker = "QUESTION";
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
        string answer_options_string;
        vector<string> answer_options_vect;
        string given_answers_string;
        vector<string> given_answers;
        vector<Result *> *results = new vector<Result *>;

        string whitespaces =  " \t\f\v\n\r";

        // reading in the questions:
        while (infile.good()) {
            // empty vectors:
            answer_options_vect.clear();
            given_answers.clear();

            //jump back to last read line if there is still left from the file:
            infile.seekg(oldpos);
            question_num = get_text_after(infile, oldpos, error_msg, "QUESTION");
            if (question_num == "NOT_FOUND") return file_corrupted<Result>(error_msg);

            // reading whether the answer was correct or not:
            correct_string = read_section(infile, oldpos, "correct", section_marker, error_msg);
            if (correct_string == "NOT_FOUND") return file_corrupted<Result>(error_msg);
            correct = stoi(correct_string);

            // reading the number of trials:
            num_of_trials = read_section(infile, oldpos, "trials", section_marker, error_msg);
            if (num_of_trials == "NOT_FOUND") return file_corrupted<Result>(error_msg);

            // reading the type of the question:
            type = read_section(infile, oldpos, "type", section_marker, error_msg);
            if (type != "text" && type != "multi")
            {
                error_msg = "type must be either \"text\" or \"multi\"\n";
                error_msg += "received" + type;
                return file_corrupted<Result>(error_msg);
            }

            // reading the question:
            question = read_section(infile, oldpos, "question", section_marker, error_msg);
            if (question == "NOT_FOUND") return file_corrupted<Result>(error_msg);

            if (type == "multi")
            {
                // check whether there is the header answer_options:
                answer_options_string =read_section(infile, oldpos, "answer_options", section_marker, error_msg);
                if (answer_options_string == "NOT_FOUND") return file_corrupted<Result>(error_msg);

                // reading in the answer options:
                answer_options_vect = vectorize_string(answer_options_string);
                if (answer_options_vect.empty()) return file_corrupted<Result>(error_msg);
            }

            // reading the real answer:
            real_answer = read_section(infile, oldpos, "real_answer", section_marker, error_msg);
            if (real_answer == "NOT_FOUND") return file_corrupted<Result>(error_msg);

            // finding the given answers header:
            given_answers_string = read_section(infile, oldpos, "given_answers", section_marker, error_msg);
            if (given_answers_string == "NOT_FOUND") return file_corrupted<Result>(error_msg);

            // reading the given answers:
            given_answers = vectorize_string(given_answers_string);
            if (given_answers.empty()) return file_corrupted<Result>(error_msg);

            // adding the new Result object to the vector:
            results->push_back(new Result(question_num, correct, num_of_trials, type,
                                          question, real_answer, answer_options_vect,
                                          given_answers));

            // jumping over empty lines:
            getline(infile, question_num);
            oldpos = infile.tellg();

            while (question_num.find_first_not_of(whitespaces) == string::npos && infile.good())
            {
                getline(infile, question_num);
            }
        }
        infile.close();
        return results;
    }
    else return new vector<Result *>;
}

