#include <questioningapp.h>


vector<Question *>* QuestioningApp::readQuestions(string filename)
{
    ifstream infile(filename, ios_base::binary);
    if (infile.is_open())
    {
        string chapter_marker = "QUESTION";
        string line;
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
        string answer_options_string;
        vector<string> answer_options_vect;
        vector<int> multi_answers_vect;
        vector<Question *> *questions_vect = new vector<Question *>;

        string whitespaces =  " \t\f\v\n\r";

        // reading the timestamp:
        timestamp = get_text_after(infile, oldpos, error_msg, "timestamp:");
        if (timestamp == "NOT_FOUND") return file_corrupted<Question>(error_msg);

        // search until the first QUESTION line:
        do getline(infile, line);
        while ((line.find(chapter_marker) == string::npos) && infile.good());

        // reading in the questions:
        while (infile.good()) {
            // empty vectors:
            answer_options_vect.clear();
            multi_answers_vect.clear();

            // reading the number of trials:
            num_of_trials_string = read_section(infile, oldpos, "trials", chapter_marker, error_msg);
            if (num_of_trials_string == "NOT_FOUND") return file_corrupted<Question>(error_msg);
            num_of_trials = stoi(num_of_trials_string);

            // reading the type of the question:
            type_string = read_section(infile, oldpos, "type", chapter_marker, error_msg);
            if (type_string != "text" && type_string != "multi")
            {
                error_msg = "type must be either \"text\" or \"multi\"\n";
                error_msg += "received" + type_string;
                return file_corrupted<Question>(error_msg);
            }

            // reading the question:
            question_string = read_section(infile, oldpos, "question", chapter_marker, error_msg);
            if (question_string == "NOT_FOUND") return file_corrupted<Question>(error_msg);

            if (type_string == "text")
            {
                // reading the answer:
                answer_string = read_section(infile, oldpos, "answer", chapter_marker, error_msg);
                if (answer_string == "NOT_FOUND") return file_corrupted<Question>(error_msg);

                // adding the new question to the vector:
                questions_vect->push_back(new TextQuestion(question_string, type_string,
                                                           question_num, num_of_trials, answer_string));
            }
            else
            {
                answer_options_string = read_section(infile, oldpos, "answer_options", chapter_marker, error_msg);
                if (answer_options_string == "NOT_FOUND") return file_corrupted<Question>(error_msg);

                // reading in the answer options:
                answer_options_vect = vectorize_string(answer_options_string);
                if (answer_options_vect.empty()) return file_corrupted<Question>("Error reading the answer options.");

                // reading the answers:
                answer_string = read_section(infile, oldpos, "answers", chapter_marker, error_msg);
                if (answer_string == "NOT_FOUND") return file_corrupted<Question>(error_msg);
                multi_answers_vect = get_multi_answers_from_string(answer_string);

                // adding the new question to the vector:
                questions_vect->push_back(new MultiChoiceQuestion(question_string, type_string, question_num,
                                                                  num_of_trials, answer_options_vect, multi_answers_vect));
            }

            // search until the next QUESTION line:
            do getline(infile, line);
            while ((line.find(chapter_marker) == string::npos) && infile.good());

            question_num++;
        }
        infile.close();
        return questions_vect;
    }
    else return new vector<Question *>;
}
