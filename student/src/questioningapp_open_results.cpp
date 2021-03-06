#include <questioningapp.h>
#include <results.h>


vector<Result *>* QuestioningApp::readResults(string filename,
                                              string& student_name,
                                              string& student_class)
{
    ifstream infile(filename, ios_base::binary);
    if (infile.is_open())
    {
        string chapter_marker = "QUESTION";
        string error_msg = "";
        streampos oldpos;
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

        // read the name of the student:
        student_name = read_section(infile, oldpos, "student_name", chapter_marker, error_msg);
        if (student_name == "NOT_FOUND") return file_corrupted<Result>(error_msg);

        // read the class of the student:
        student_class = read_section(infile, oldpos, "student_class", chapter_marker, error_msg);
        if (student_class == "NOT_FOUND") return file_corrupted<Result>(error_msg);

        // search until the first QUESTION line:
        do {
            question_num = get_text_after(infile, oldpos, error_msg, chapter_marker);
        }
        while ((question_num == "NOT_FOUND") && infile.good());

        // reading in the questions:
        while (infile.good()) {
            // empty vectors:
            answer_options_vect.clear();
            given_answers.clear();

            // reading whether the answer was correct or not:
            correct_string = read_section(infile, oldpos, "correct", chapter_marker, error_msg);
            if (correct_string == "NOT_FOUND") return file_corrupted<Result>(error_msg);
            correct = stoi(correct_string);

            // reading the number of trials:
            num_of_trials = read_section(infile, oldpos, "trials", chapter_marker, error_msg);
            if (num_of_trials == "NOT_FOUND") return file_corrupted<Result>(error_msg);

            // reading the type of the question:
            type = read_section(infile, oldpos, "type", chapter_marker, error_msg);
            if (type != "text" && type != "multi")
            {
                error_msg = "type must be either \"text\" or \"multi\"\n";
                error_msg += "received" + type;
                return file_corrupted<Result>(error_msg);
            }

            // reading the question:
            question = read_section(infile, oldpos, "question", chapter_marker, error_msg);
            if (question == "NOT_FOUND") return file_corrupted<Result>(error_msg);

            if (type == "multi")
            {
                // check whether there is the header answer_options:
                answer_options_string =read_section(infile, oldpos, "answer_options", chapter_marker, error_msg);
                if (answer_options_string == "NOT_FOUND") return file_corrupted<Result>(error_msg);

                // reading in the answer options:
                answer_options_vect = vectorize_string(answer_options_string);
                if (answer_options_vect.empty()) return file_corrupted<Result>(error_msg);
            }

            // reading the real answer:
            real_answer = read_section(infile, oldpos, "real_answer", chapter_marker, error_msg);
            if (real_answer == "NOT_FOUND") return file_corrupted<Result>(error_msg);

            // finding the given answers header:
            given_answers_string = read_section(infile, oldpos, "given_answers", chapter_marker, error_msg);
            if (given_answers_string == "NOT_FOUND") return file_corrupted<Result>(error_msg);

            // reading the given answers:
            given_answers = vectorize_string(given_answers_string);
            if (given_answers.empty()) return file_corrupted<Result>(error_msg);

            // adding the new Result object to the vector:
            results->push_back(new Result(question_num, correct, num_of_trials, type,
                                          question, real_answer, answer_options_vect,
                                          given_answers));

            // search for the next QUESTION line:
            do {
                question_num = get_text_after(infile, oldpos, error_msg, chapter_marker);
            }
            while ((question_num == "NOT_FOUND") && infile.good());
        }

        infile.close();
        return results;
    }
    else return new vector<Result *>;
}

