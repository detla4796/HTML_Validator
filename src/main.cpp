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
    int tags = 0;
    
    while (getline(f, line))
    {
        lineNumber++;
        for (size_t i = 0; i < line.length(); i++)
        {
            if (line[i] == '<')
            {
                brackets++;
                if (i + 1 < line.length() && line[i + 1] == '/') 
                {
                    tags--;
                } 
                else 
                {
                    tags++;
                }
            }
            else if (line[i] == '>')
            {
                brackets--;
                if (brackets < 0)
                {
                    cout << "Unmatched closing bracket at line " << lineNumber << endl;
                    f.close();
                    return false;
                }
            }
        }
        if (brackets > 0)
        {
            cout << "Unmatched opening bracket at line " << lineNumber << endl;
            f.close();
            return false;
        }
    }
    
    if (tags != 0)
    {
        cout << "Unmatched tags found" << endl;
        f.close();
        return false;
    }
    
    f.close();
    cout << "File " << fname << " is valid HTML" << endl;
    return true;
}

int main()
{
    string fname;
    cout << "Enter HTML filename: ";
    cin >> fname;
    isValidHTML(fname);
    return 0;
}