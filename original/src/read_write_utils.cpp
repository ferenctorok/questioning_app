# include <utils.h>


void write_section(ofstream &outfile,
                   string header,
                   string content)
{
    outfile << "<" << header << ">" << endl;
    outfile << content << endl;
    outfile << "</" << header << ">" << endl;
}


string read_section(ifstream &infile,
                    streampos &oldpos,
                    const string header,
                    string &error_msg)
{
    oldpos = infile.tellg();
    string line;
    getline(infile, line);

    // jumping over empty lines
    string whitespaces =  " \t\f\v\n\r";
    while (line.find_first_not_of(whitespaces) == string::npos && !infile.eof())
    {
        getline(infile, line);
    }

    size_t pos = line.find("<" + header + ">");
    size_t pos_q;
    if (pos != string::npos)
    {
        string return_string = "";
        while (infile.good())
        {
            getline(infile, line);
            pos = line.find("</" + header + ">");
            pos_q = line.find("QUESTION");
            if (pos_q == string::npos)
            {
                if (pos == string::npos) return_string += (line + "\n");
                else
                {
                    // 2 has to be devided, because there is already \r at the end of the lines
                    // and we add an extra \n to it.
                    return return_string.substr(0, return_string.length() - 2);
                }
            }
            else break;
        }
        error_msg = "Reached end of QUESTION \n without finding </" + header + ">";
    }
    else
    {
        error_msg = "expected header: <" + header + ">\n";
        error_msg += "received line: \" " + line + " \"";
    }

    return "NOT_FOUND";
}


vector<string> get_options(string options_string)
{
    vector<string> options;
    size_t pos;

    while (!options_string.empty())
    {
        // finding the beginning of an option and cut the * from the string:
        pos = options_string.find("*");
        if (pos != string::npos) options_string = options_string.substr(pos + 1);
        else options_string = "";

        // reading out the option and cutting it from the string:
        pos = options_string.find("*");
        if (pos != string::npos)
        {
            // in this case pos - 1, since the /r also has to be deleted.
            options.push_back(options_string.substr(0, pos - 1));
            options_string = options_string.substr(pos);
        }
        else
        {
            options.push_back(options_string.substr(0, pos));
            options_string = "";
        }
    }

    return options;
}
