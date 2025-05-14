#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool isValidHTML(const string& fname)
{
    ifstream f(fname);
    if (!f.is_open())
    {
        cout << "Error: Could not open file " << fname << endl;
        return false;
    }
    int brackets = 0;
    int lineNumber = 0;
    string line;
    while (getline(f, line))
    {
        lineNumber++;
        for (char l : line)
        {
            if (l == '<')
            {
                brackets++;
            }
            else if (l == '>')
            {
                brackets--;
                if (brackets < 0)
                {
                    cout << "Unmatched closing bracket at line " << lineNumber << endl;
                    return false;
                }
            }
        }
        if (brackets > 0)
        {
            cout << "Unmatched opening bracket at line " << lineNumber << endl;
            return false;
        }
    }
    f.close();
    cout << "File " << fname << " is valid HTML" << endl;
    return true;
}

int main()
{
    string fname("html.txt");
    isValidHTML(fname);
    return 0;
}