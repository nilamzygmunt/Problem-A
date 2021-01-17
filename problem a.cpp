#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;


string add(string numberOne, string numberTwo)
{
    int numberOneLength = numberOne.length();
    int numberTwoLength = numberTwo.length();

    if (numberOneLength > numberTwoLength) swap(numberOne, numberTwo);

    reverse(numberOne.begin(), numberOne.end());
    reverse(numberTwo.begin(), numberTwo.end());

    int carry = 0;
    string result = "";

    for (int i=0; i<numberOneLength; i++)
    {
        int sum = (numberOne[i] - '0') + (numberTwo[i] - '0') + carry;
        result.push_back(sum % 10 + '0');
        carry = sum / 10;
    }

    for (int i=numberOneLength; i<numberTwoLength; i++)
    {
        int sum = (numberTwo[i] -'0') + carry;
        result.push_back(sum % 10 + '0');
        carry = sum / 10;
    }

    if (carry) result.push_back(carry + '0');

    reverse(result.begin(), result.end());

    return result;
}
string subtract(string a, string b) //column subtraction
{
    int pa = a.length() - 1;            //we find the position of the last digit in the strings a and b
    int pb = b.length() - 1;
    string result = "";                //empty string that will be the result
    int c = 0;                         //'c' - carrying ,the digit that we will carry to the next column
    int A, B;
    if (a.length() < b.length())        //we compare the strings a and b to find which number is smaller
    {
        A = 0;
        B = 1;                         //if the string a is shorter than string b the first number is smaller
    }
    else if (a.length() == b.length()) //if the strings a and b are ofthe same size then we compare their digits successively
    {
        int i = 0;
        while (unsigned(i) < a.length())
        {
            if (a[i] - 48 < b[i] - 48)
            {
                A = 0;
                B = 1;
                break;
            }
            else if (a[i] - 48 > b[i] - 48)
            {
                A = 1;
                B = 0;
                break;
            }
            else if (a[i] - 48 == b[i] - 48)
            {
                A = 1;
                B = 1;
                i++;
            }
        }
    }
    else                             //otherwise the first number is bigger than the second
    {
        A = 1; B = 0;
    }
    if (A > B)                          //we subtract the second number from the first one
    {
        while (pa >= 0 || pb >= 0)     //the loop to successively subtract the digits of stringb b from string a
        {
            int r, ca, cb;
            if (pa >= 0)               //we calculate the values of the digits
                ca = a[pa] - 48 - c;
            else
                ca = 0;

            if (pb >= 0)
                cb = b[pb] - 48;
            else
                cb = 0;

            if (ca < cb)              //if the digit from string a is smaller than the digit from string b
            {
                ca = ca + 10;          //we add 10 to its value and carry '1' to the value of the next digit
                c = 1;
                r = ca - cb;
            }
            else
            {
                r = ca - cb;
                c = 0;
            }
            result = "0" + result;       // to the result string we add the result from the previous loop
            result[0] = 48 + r % 10;       // we put the last digit of 'r' to the 0th index of the result


            pa--; pb--;              //we decrement the position of the last digit
        }
    }
    else if (B > A)                     //if the number two is bigger than the number one we subtract string a from string b
    {
        while (pa >= 0 || pb >= 0)     //we repeat the steps as in the previous case
        {
            int r, ca, cb;
            if (pa >= 0)
                ca = a[pa] - 48;
            else
                ca = 0;

            if (pb >= 0)
                cb = b[pb] - 48 - c;
            else
                cb = 0;

            if (cb < ca)
            {
                cb = cb + 10;
                c = 1;
                r = cb - ca;
            }
            else
            {
                r = cb - ca;
                c = 0;
            }
            result = "0" + result;
            result[0] = 48 + r % 10;

            pa--; pb--;
        }
    }
    else if (A == B)                       //if the numbers are equal the result is 0
        result = "0";
    for (int i = 0; unsigned(i) < result.length();)   //we erase the zeros if there are any from the beggining of the string
    {
        if (result[i] == '0' && A != B)      //if A=B both numbers are the same so we want the result to be zero
            result.erase(i, 1);
        else
            break;
    }
    if (B > A)                             //if the second number is bigger than the first one we have to add '-' at the beggining of the result string
        result = "-" + result;
    return result;
}
string multiply(string a, string b)
{
    if (a[0] == '0' || b[0] == '0') return "0";                 //if any of the numbers is equal to 0 the result is 0
    int n1(a.length()), n2(b.length()), n(n1 + n2);             //we find the length of both strings we calculate the sum of their length - 'n'
    vector<int> r(n, 0);                                            // we create a vector of the size of 'n' filled with zeros
    string      result(n, '0');
    for (size_t i = 0; i < n1; ++i)                             //the loop to successively multiply the digits
    {
        for (size_t j = 0; j < n2; ++j)
        {
            r[i + j + 1] += (a[i] - '0') * (b[j] - '0');
        }
    }
    for (size_t i = n - 1; i > 0; --i)
    {
        if (r[i] > 9)
            r[i - 1] += r[i] / 10;
        result[i] += r[i] % 10;
    }
    result[0] += r[0];
    if (result[0] == '0')
    {
        result = result.substr(1, result.length());                 //if there is a zero in the 0th index of the result string we subtract the result without it
    }
    return result;
}
string divide(string a, string b)       //long division
{
    if (b[0] == '0')                        //the divisor can't be equal to 0
    {
        return "You can't divide by 0";
    }
    int n1 = a.length();                   //we find the length of both numbers
    int n2 = b.length();
    string result = "";                    //empty string that will be the result
    string s;                            //string that will be the substring of the dividend
    string h;                            //string that will be the difference between two strings
    int A, B;                            //variables to help to determine which number is greater (the number in string s or the number in string b)
    int r = 0;                             //variable to count how many times are we able to subtract string b from string s
    int p = 1;                             //variable to operate the loop
    if (n1 == n2)                           //the case when the strings a and b are of equal length
    {
        while (p)                         //loop until p=0
        {
            h = subtract(a, b);
            a = h;
            r++;
            if (a.length() < b.length())    //we check which string a or b holds a greater number to know if we should continue subtracting or stop
            {
                A = 0;
                B = 1;
            }
            else if (a.length() == b.length())
            {
                int i = 0;
                while (unsigned(i) < a.length())
                {
                    if (a[i] - 48 < b[i] - 48)
                    {
                        A = 0;
                        B = 1;
                        break;
                    }
                    else if (a[i] - 48 > b[i] - 48)
                    {
                        A = 1;
                        B = 0;
                        break;
                    }
                    else if (a[i] - 48 == b[i] - 48)
                    {
                        A = 1;
                        B = 1;
                        i++;
                    }
                }
            }
            else
            {
                A = 1;
                B = 0;
            }
            if (h == "0" || A < B)                           //if string h="0" or string a is smaller than string b the loop ends
            {
                p = 0;
            }
        }
        result = r + 48;                                    //result is equal to r the number of how many times the loop was carried out (how many times we subtracted string b from a
    }
    else                                                //the case where string b is shorter than string a
    {
        s = a.substr(0, b.length());                       //'s' - the substring of a is of the length of string b
        a.erase(0, n2);                                  //we erase the length of b from string a
        int r = 0;
        for (int t = 0; t <= n1 - n2; t++)
        {
            if (s.length() < b.length())
            {
                A = 0;
                B = 1;
            }
            else if (s.length() == b.length())
            {
                int i = 0;
                while (unsigned(i) < s.length())
                {
                    if (s[i] - 48 < b[i] - 48)
                    {
                        A = 0;
                        B = 1;
                        break;
                    }
                    else if (s[i] - 48 > b[i] - 48)
                    {
                        A = 1;
                        B = 0;
                        break;
                    }
                    else if (s[i] - 48 == b[i] - 48)
                    {
                        A = 1;
                        B = 1;
                        i++;
                    }
                }
            }
            else
            {
                A = 1;
                B = 0;
            }
            if (A < B && t == 0)                                     //the case if in the first iteration of the loop when t=0 string s is smaller than string b
            {
                s = s + a.substr(0, 1);                              //we add the element of 0th index of string a to the string s
                a = a.erase(0, 1);                                 //we erase this element from string a
                n1--;                                        //because now there will be one less iteration
                A = 1; B = 0;                                       //because now string as is greater than string b
            }
            int p = 1;
            while (p)
            {

                if (s.length() < b.length())                       //we check which string is greater
                {
                    A = 0;
                    B = 1;
                }
                else if (s.length() == b.length())
                {
                    int i = 0;
                    while (unsigned(i) < s.length())
                    {

                        if (s[i] - 48 < b[i] - 48)
                        {
                            A = 0;
                            B = 1;
                            break;
                        }
                        else if (s[i] - 48 > b[i] - 48)
                        {
                            A = 1;
                            B = 0;
                            break;
                        }
                        else if (s[i] - 48 == b[i] - 48)
                        {
                            A = 1;
                            B = 1;
                            i++;
                        }
                    }
                }
                else
                {
                    A = 1;
                    B = 0;
                }
                if (A < B)                                           //if string s is smaller than string b we end the loop
                {
                    result = result + "0";
                    result[t] = r + 48;                               //the result is equal to the number of how many times the loop was carried out
                    p = 0;
                    break;
                }
                if (A >= B)                                          //if string s is greater than string b we can subtract
                {
                    h = subtract(s, b);                             //we subtract string b from s
                    s = h;
                }
                r++;
            }
            r = 0;                                                    //r becomes 0 because the next iteration will begin
            s = s + a.substr(0, 1);                                      //we add the element of 0th index of string a to the string s
            if (s[0] == '0')
            {
                s = s.substr(1, s.length());                 //if there is a zero in the 0th index of the result string we subtract the result without it
            }
            a = a.erase(0, 1);                                         //we erase this element from string a
        }
    }
    return result;
}
int main()
{
    string s, a, b;
    short n;                                             //variable for the number of tests
    cin >> n;                                            //enter how many tests will be carried out
    while (n)                                           //loop to carry out 'n' tests
    {
        int A;                                         // variable for the position of the operator
        cin >> s;                                        //enter the math formula
        if (s.find('+') != string::npos)                  //we find the operator
        {
            A = s.find('+');                             //we find the position of the operator
        }
        else if (s.find('-') != string::npos)
        {
            A = s.find('-');
        }
        else if (s.find('*') != string::npos)
        {
            A = s.find('*');
        }
        else if (s.find('/') != string::npos)
        {
            A = s.find('/');
        }
        a = s.substr(0, A);                                //knowing the position of the operator we determine the first number
        int B = s.length();
        b = s.substr(A + 1, B - A - 1);                          //we determine the second number
        if (s.find('+') != string::npos)                   //depending on the operator we call the right function to calculate the math problem
        {
            cout << add(a, b);
        }
        if (s.find('-') != string::npos)
        {
            cout << subtract(a, b);
        }
        if (s.find('*') != string::npos)
        {
            cout << multiply(a, b);

        }
        if (s.find('/') != string::npos)
        {
            cout << divide(a, b);
        }
        cout << endl;
        a = ""; b = ""; s = "";                                 //we empty the strings
        n--;                                              //we decrement 'n'
    }
    return 0;
}
