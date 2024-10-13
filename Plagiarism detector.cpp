#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <regex>
using namespace std;
vector<string> readFile(char *filename);
int detect(vector<string> &f1, vector<string> &f2);
vector<string> lcs;
bool isSourceCode(vector<string> &result);
int main(int argc, char **argv)
{
    if (argc != 3)
    {
        cout << "-1" << endl;
        return -1;
    }
    vector<string> f1 = readFile(argv[1]);
    //  for(string s : f1)
    //   cout <<"\n" << s ;
    vector<string> f2 = readFile(argv[2]);
    //  for(string s : f2)
    //    cout <<"\n" <<s;
    detect(f1, f2);
    return 0;
}
vector<string> readFile(char *fname)
{
    vector<string> result;
    ifstream file(fname);
    cout << "\nReading file:" << fname << endl;
    string str;
    while (file >> str)
    {
        result.push_back(str);
    }
    if (isSourceCode(result))
    {
        cout << "\n if part of it";
        for (string str : result)
            cout << "\n"
                 << str;
        return result;
    }
    else
    {
        cout << "\n else part of it";
        for (string &s : result)
        {
            string new_str = regex_replace(s, regex(R"([^A-Za-z\d])"), "");
            s = new_str;
        }
        for (string str : result)
            cout << "\n"
                 << str;
        return result;
    }
}
bool isSourceCode(vector<string> &res)
{
    for (string &s : res)
    {
        // cout << "\n"<< s;
        if (s == "import" || s == "#include")
        {
            cout << "\nSource code!!";
            return 1;
            // break;
        }
    }
    return 0;
}
int detect(vector<string> &f1, vector<string> &f2)
{
    int container1, container2;
    float percentage = 0.0;
    container1 = f1.size();
    container2 = f2.size();   
    int count = 0;
    int row, col;
    //matrix initialization
    int **matrix = new int *[container1 + 1];
    for (int i = 0; i < container1 + 1; i++)
    {
        matrix[i] = new int[container2];
    }
    cout << "\nPrinting 1 2:" << container1 << "," << container2;
    for (int i = 0; i <= container1; i++)
    {
        for (int j = 0; j <= container2; j++)
        {
            if (i == 0 || j == 0)
            {
                matrix[i][j] = 0;
            }
            else if (f1[i - 1] == f2[j - 1])
            {
                // cout << "\nf1:" << f1.at(i - 1) << "\t\t\tf2:" << f2[j - 1];
                // cout<< "\n-------------------------------------------";
                matrix[i][j] = 1 + matrix[i - 1][j - 1];
            }
            else
            {
                matrix[i][j] = 0;
            }
        }
    }
    /*  cout << "Printing matrix after lcs\n";
     for (int i = 0; i <= container1; i++)
     {
         for (int j = 0; j <= container2; j++)
         {
             cout << matrix[i][j];
         }
         cout << "\n";
     } */
    for (int i = container1; i >= 0; i--)
    {
        for (int j = container2; j >= 0; j--)
        {
            if (matrix[i][j] > 3)
            {
                row = i;
                col = j;
                // cout << "\n=============NEXT=============";
                while (matrix[row][col] != 0)
                {
                    //cout << "\n" << matrix[row][col];                  
                    lcs.push_back(f1[row - 1]);
                    row--;
                    col--;
                    
                }
                i = row;
                j = col;
            }
        }
    }
    count = lcs.size();
    cout << "\nCommon words: count and length: " << count << "," << len << "\n";
    for (auto it = lcs.rbegin(); it != lcs.rend(); it++)
    {
        cout << *it << " ";
    }
    float divisor = max(container1, container2);
    // char percentagesymbol = '%';
    if (count == 0)
    {
        cout << "Nothing is the same";
    }
    else
    {
        percentage = (float)count / divisor;
        float total = percentage * 100;      
        printf("\n=======================Percentage of similarity = %.2f====================", total);
    }
    return 1;
}
