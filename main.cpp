//
//  main.cpp
//  LCS
//
//  Created by Hussein Jafarinia on 7/11/18.
//  Copyright © 2018 Hussein Jafarinia. All rights reserved.
//

// Lcs.cpp : Defines the entry point for the console application.
//


#include <iostream>
#include <time.h>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <random>
#include <cstring>

using namespace std;

#define T 20
#define iterate_No 20
#define Size 40
#define Ln 20

void mutation(bool a[], int length)
{
    srand(time(NULL));
    
    
    int i = rand() % length;
    
    
    if (a[i] == true)
    {
        a[i] == false;
    }
    else {
        a[i] == true;
    }
    return;
    
}

void crossOver(bool a[], bool b[], int Length)
{
    srand(time(NULL));
    int point = rand() % Length;
    
    
    bool temp;
    for (int i = point; i<Length; ++i)
    {
        
        temp = a[i];
        a[i] = b[i];
        b[i] = temp;
    }
    
}

int min(int a, int b)
{
    return a>b ? b : a;
}

int fitness(bool a[], string s1, string s2)
{
    string str;
    int counter = 0;
    
    for (int i = 0; i < s1.length(); ++i)
    {
        if (a[i])
        {
            str += s1[i];
            
        }
        
    }
    
    int j = 0;
    for (int i = 0; i<str.length() && j < s2.length(); ++i)
    {
        
        
        while (j<s2.length())
        {
            if (str[i] != s2[j])
            {
                ++j;
            }
            else {
                //++j;
                counter++;
                break;
            }
            
        }
        
    }
    return counter;
}

void createPopulation(bool  a[Size][Ln], int rows, int Length)
{
    srand(time(NULL));
    
    for (int i = 0; i<rows; ++i)
    {
        for (int j = 0; j < Length; ++j)
        {
            /*int Toss = rand() % 2;
             if (Toss == 1)
             {
             a[i][j] == true;
             }
             else {
             a[i][j] == false;
             }*/
            a[i][j] = rand() % 2;
        }
    }
    
}

void copyToOneD(bool a[], bool b[Size][Ln], int i, int Length)
{
    for (int j = 0; j<Length; ++j)
    {
        a[j] = b[i][j];
    }
}

int max(int a, int b);

/* Returns length of LCS for X[0..m-1], Y[0..n-1] */
int lcs(const char *X, const char *Y, int m, int n);

void randomSelect(bool a[])
{
    int gcount = 0;
    srand(time(NULL));
    for (int i = 0; gcount<T; ++i)
    {
        int index = rand() % Size;
        
        if (a[index] != true)
        {
            a[index] = true;
            gcount++;
        }
        /*    if (rand() % 2 == 0)
         {
         a[i%Size] = false;
         }
         else
         {
         if (a[i%Size] == false)
         {
         gcount++;
         a[i%Size] = true;
         }
         
         }*/
    }
}

void get_elits(bool tournoment[T][Ln], bool off[], bool off2[], string s1, string s2, int Length)
{
    
    
    bool *a = new bool[Length];
    bool *b = new bool[Length];
    
    copyToOneD(a, tournoment, 0, Length);
    copyToOneD(b, tournoment, 1, Length);
    int in1 = 0;
    int f1 = fitness(a, s1, s2);
    
    int in2 = 1;
    int f2 = fitness(b, s1, s2);
    
    int tmp;
    if (f2<f1)
    {
        in2 = 0;
        in1 = 1;
        
        tmp = f1;
        f1 = f2;
        f2 = tmp;
    }
    for (int i = 2; i<T; i++)
    {
        copyToOneD(a, tournoment, i, Length);
        
        //copyToOneD(b, tournoment, i + 1, Length);
        
        tmp = fitness(a, s1, s2);
        
        if (tmp >f2)
        {
            in1 = in2;
            in2 = i;
            
            f1 = f2;
            f2 = tmp;
            continue;
        }
        else {
            if (tmp>f1)
            {
                f1 = tmp;
                in1 = i;
            }
        }
        
    }
    for (int i = 0; i<Length; ++i)
    {
        off[i] = tournoment[in2][i];
        off2[i] = tournoment[in1][i];
        
    }
    delete[] a;
    delete[] b;
}

int main()
{
    string s1, s2;
    
    while (1)
    {
        cout << endl << "Enter first string of length "<<Ln<<" or change LN parameter In Code\n";
        cin >> s1;
        if (s1.length() != Ln)
        {
            cout << endl << "length is not equal to Ln parameter";
        }
        else
        {
            break;
        }
    }
    
    while (1)
    {
        cout << endl << "Enter second string of length "<<Ln<<" or change LN parameter In Code\n";
        cin >> s2;
        if (s2.length() != Ln)
        {
            cout << endl << "length is not equal to Ln parameter";
        }
        else
        {
            break;
        }
    }
    //s1 = "qwertyuiop";
    //s2 = "asdfghjklm";
    
    /*  Random string generation
     srand(time(NULL));
     for (int i = 0; i<Ln; ++i)
     {
     s1 += (char)((rand() % 10) + 97);
     s2 += (char)((rand() % 10) + 97);
     } */
    
    bool a[Ln] = { false };
    bool b[Ln] = { false };
    bool best[Ln] = { false };
    bool tournoment[T][Ln] = {false};
    bool arrSelection[Size] = { false };
    bool p1[Ln] = { false };
    bool p2[Ln] = { false };
    
    int maxL = 0;//holds the max length found
    
    cout << "\n s1 String " << " : " << s1 << "\n S2 string  : " << s2 << endl << endl;
    
    cout << endl << "-----------------------------------------------------------------" << endl;
    
    bool generation[Size][Ln] = { false };
    
    createPopulation(generation, Size, Ln);
    //cout << "first generation is below " << endl << endl;;
    
    //for (int i = 0; i<Size; ++i)
    //{
    //    for (int j = 0; j<Ln; ++j)
    //    {
    //        cout << generation[i][j] << " ";
    //    }
    //    cout << endl;
    //}
    
    //cout << endl << "-----------------------------------------------------------------" << endl;
    
    bool new_generation[Size][Ln] = { false };
    
    for (int i = 0; i<Size; i++)
    {
        copyToOneD(a, generation, i, Ln);
        
        int tmp = fitness(a, s1, s2);
        if (tmp>maxL)
        {
            maxL = tmp;
            for (int s = 0; s<Ln; ++s)
            {
                best[s] = a[s];
                
                
            }
        }
    }
    
    for (int iterate = 0; iterate<iterate_No; ++iterate)
    {
        for (int k = 0, off = 0; k<Size / 2; ++k, off += 2)
        {
            randomSelect(arrSelection);
            int index = 0;
            
            for (int i = 0; i<Size && index<T; ++i)
            {
                if (arrSelection[i] == true)
                {
                    for (int j = 0; j<Ln; ++j)
                    {
                        tournoment[index][j] = generation[index][j];
                    }
                    index++;
                }
                
            }
            
            get_elits(tournoment, p1, p2, s1, s2, Ln);
            
            int L = fitness(p1, s1, s2);
            
            if (L > maxL)
            {
                maxL = L;
                for (int s = 0; s<Ln; ++s)
                {
                    best[s] = p1[s];
                    
                }
                
            }
            
            L = fitness(p2, s1, s2);
            
            if (L > maxL)
            {
                maxL = L;
                for (int s = 0; s<Ln; ++s)
                {
                    best[s] = p2[s];
                    
                }
                
            }
            
            crossOver(p1, p2, Ln);
            
            if (rand() % 1000 == 100)
            {
                mutation(p1, Ln);
                
            }
            
            if (rand() % 1000 == 100)
            {
                mutation(p2, Ln);
            }
            
            for (int in = 0; in<Ln; ++in)
            {
                new_generation[off][in] = p1[in];
                new_generation[off + 1][in] = p2[in];
                
            }
            
            for (int i = 0; i < Size; ++i)
            {
                arrSelection[i] = { false };
            }
            
        }
        
        for (int i = 0; i<Size; ++i)
        {
            for (int j = 0; j<Ln; ++j)
            {
                generation[i][j] = new_generation[i][j];
            }
        }
    }
    
    createPopulation(generation, Size, Ln);
    //cout << "first generation is below " << endl << endl;;
    
    //for (int i = 0; i<Size; ++i)
    //{
    //    for (int j = 0; j<Ln; ++j)
    //    {
    //        cout << generation[i][j] << " ";
    //    }
    //    cout << endl;
    //}
    
    //cout << endl << "-----------------------------------------------------------------" << endl;
    
    new_generation[Size][Ln] = { false };
    
    for (int i = 0; i<Size; i++)
    {
        copyToOneD(a, generation, i, Ln);
        
        int tmp = fitness(a, s2, s1);
        if (tmp>maxL)
        {
            maxL = tmp;
            for (int s = 0; s<Ln; ++s)
            {
                best[s] = a[s];
                
                
            }
        }
    }
    
    for (int iterate = 0; iterate<iterate_No; ++iterate)
    {
        for (int k = 0, off = 0; k<Size / 2; ++k, off += 2)
        {
            randomSelect(arrSelection);
            int index = 0;
            
            for (int i = 0; i<Size && index<T; ++i)
            {
                if (arrSelection[i] == true)
                {
                    for (int j = 0; j<Ln; ++j)
                    {
                        tournoment[index][j] = generation[index][j];
                    }
                    index++;
                }
                
            }
            
            get_elits(tournoment, p1, p2, s2, s1, Ln);
            
            int L = fitness(p1, s2, s1);
            
            if (L > maxL)
            {
                maxL = L;
                for (int s = 0; s<Ln; ++s)
                {
                    best[s] = p1[s];
                    
                }
                
            }
            
            L = fitness(p2, s2, s1);
            
            if (L > maxL)
            {
                maxL = L;
                for (int s = 0; s<Ln; ++s)
                {
                    best[s] = p2[s];
                    
                }
                
            }
            
            crossOver(p1, p2, Ln);
            
            if (rand() % 1000 == 100)
            {
                mutation(p1, Ln);
                
            }
            
            if (rand() % 1000 == 100)
            {
                mutation(p2, Ln);
            }
            
            for (int in = 0; in<Ln; ++in)
            {
                new_generation[off][in] = p1[in];
                new_generation[off + 1][in] = p2[in];
                
            }
            
            for (int i = 0; i < Size; ++i)
            {
                arrSelection[i] = { false };
            }
        }
        
        for (int i = 0; i<Size; ++i)
        {
            for (int j = 0; j<Ln; ++j)
            {
                generation[i][j] = new_generation[i][j];
            }
        }
    }
    
    cout << endl << endl;
    cout << "Genetic Algorithm Lcs  is : " << maxL << endl;
    cout << endl << "-----------------------------------------------------------------" << endl;
    
    cout << "best chromosome is :" << endl;
    for (int i = 0; i<Ln; ++i)
        cout << best[i] << " ";
    
    cout << endl << "-----------------------------------------------------------------" << endl;
    cout << endl;
    
    int m = strlen(s1.c_str());
    int n = strlen(s2.c_str());
    
    printf("Exact Length of LCS is %d", lcs(s1.c_str(), s2.c_str(), m, n));
    
    cout << endl;
    
    return 0;
}

int lcs(const char *X, const char *Y, int m, int n)
{
    //int L[m + 1][n + 1];
    int ** L = new int *[m + 1];
    
    for (int i = 0; i < m + 1; ++i)
    {
        L[i] = new int[n + 1];
    }
    
    int i, j;
    
    /* Following steps build L[m+1][n+1] in bottom up fashion. Note
     that L[i][j] contains length of LCS of X[0..i-1] and Y[0..j-1] */
    
    for (i = 0; i <= m; i++)
    {
        for (j = 0; j <= n; j++)
        {
            if (i == 0 || j == 0)
                L[i][j] = 0;
            
            else if (X[i - 1] == Y[j - 1])
                L[i][j] = L[i - 1][j - 1] + 1;
            
            else
                L[i][j] = max(L[i - 1][j], L[i][j - 1]);
        }
    }
    
    /* L[m][n] contains length of LCS for X[0..n-1] and Y[0..m-1] */
    
    int ret = L[m][n];
    
    for (int i = 0; i < m + 1; ++i)
    {
        delete[] L[i];
    }
    delete[] L;
    
    return ret;
}

/* Utility function to get max of 2 integers */
int max(int a, int b)
{
    return (a > b) ? a : b;
}
