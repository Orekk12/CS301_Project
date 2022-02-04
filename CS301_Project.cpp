//
//  main.cpp
//  cs301_greedy
//
//  Created by Batuhan Yıldırım on 24.12.2021.
//
#include <unordered_set>
#include <iostream>
#include <algorithm>
#include <vector>
#include <stdio.h>
//#include "/Users/batuhanyildirim/Desktop/Bits/stdc++.h" # you can use #include <Bits.h> instead of this line
#include <Bits.h>
#include <time.h>
#include <string>
#include <set>
#include <iterator>
#include <cstdlib>
#include <numeric>

using namespace std;
// maximum allowed value of K
#define K 41
  
// DP lookup table
vector<string> DP[K][K];



struct myStruct {
    int index;
    vector<int> v;
    myStruct(): index(-1), v(vector<int> (0)) {}
    myStruct(int i, vector<int> vec): index(i), v(vec) {}
};

vector< vector<int> > MATRIX;

vector<int> randomVectorGenerator() {
    int size = (rand() % 13) + 1;
    vector<int> v (size);
    for(int i = 0; i < size; i++) {
        v[i] = rand() % 50;
    }
    return v;
}



void vectorPrinter (vector<int> & v) {
    for(int i = 0; i < v.size(); i++) {
        cout << v[i] << "  ";
    }
    cout << endl;
}

void subsetPrinterNew(vector< myStruct> & v) {
    for(int i = 0; i < v.size(); i++) {
        vectorPrinter(v[i].v);
    }
    cout << "Cardinality = " << v.size() << endl;
}

void subsetPrinter(vector< vector<int> > & v) {
    for(int i = 0; i < v.size(); i++) {
        vectorPrinter(v[i]);
    }
    cout << "Cardinality = " << v.size() << endl;
}





vector<string> vectorTranslator(vector<vector<int>> &myvec){
    int maxel=0;
    int minel=INT_MAX;
    int maxlen=0;
    int el;
    string temp;
    vector<string> translated;
    
    for(int i = 0; i < myvec.size(); i++) {
        for(int j=0; j < myvec[i].size();j++){
            el = myvec[i][j];
            if(maxel<el) maxel=el;
            if(minel>el) minel=el;
        }
        if(maxlen<myvec[i].size())maxlen=myvec[i].size();
    }
    string dumstr = "";
    for(int i=0; i<maxel;i++){
        dumstr += "0";
    }
    
    
    for(int i = 0; i < myvec.size(); i++) {
        temp = dumstr;
        for(int j=0; j < myvec[i].size();j++){
            el = myvec[i][j];
            temp[el-1]='1';
        }
        translated.push_back(temp);
    }
    return translated;
}


bool isvalid(vector <string> chosen){
    int checkand=0;
    
    for(int i=0; i<chosen[0].size();i++){
        checkand=0;
        for(int j=0; j<chosen.size();j++){
            
            checkand += chosen[j][i] - '0';
        }
        if(checkand>1) return false;
    }
    return true;
}

double total_vtime = 0.0;
int vcount = 0;

int greedy_find(vector<vector<int>> myvec, vector<string> translated){
    
    vector<string> result;
    vector<vector<int>> check_result;
    
    
    if(translated.size() > 0){
        result.push_back(translated[0]);
        check_result.push_back(myvec[0]);
    }
    else return 0;
    


    for(int i=1 ; i<translated.size() ; i++){
        result.push_back(translated[i]);
        check_result.push_back(myvec[i]);

        time_t t2 = clock();
        bool flag = isvalid(result);
        //cout << "Running time : " << double(clock() - t2) / CLOCKS_PER_SEC << " seconds\n";
        total_vtime += double(clock() - t2) / CLOCKS_PER_SEC;
        vcount += 1;
        if(!flag){
            
            result.pop_back();
            check_result.pop_back();
        }
    }

    cout << "Total Time: " << total_vtime << endl;
    cout << "Avg time: " << total_vtime / vcount << endl;
    return result.size();
}


bool compare_interval(const vector<int> a, const vector<int> b){
    return (a.size() < b.size());
}

vector<vector<int>> createSample(int maxSetSize, int maxSetCount, int min_elem, int max_elem)
{
    //srand(randSeed);//set random number seed so that we can test the same seed if necessary, otherwise put time(NULL) for random seed
    vector<vector<int>> finalVector;//initalize the set that will be returned

    for (int i = 0; i < maxSetCount; i++)
    {
        unordered_set<int> tempSet;

        int randSetSize = rand() % maxSetSize + 2;//set the set size as random, min size = 2 because size = 1 sets are trivial
        //int randSetSize = maxSetSize;
        for (int i = 0; i < randSetSize; i++)
        {
            int randNum = rand() % max_elem + min_elem;
            tempSet.insert(randNum);
        }
        vector<int> tempVec(tempSet.begin(), tempSet.end());
        finalVector.push_back(tempVec);
    }

    return finalVector;
}

vector<vector<int>> createSampleNorand(int subsetSize, int subsetCount, int max_elem)
{
    vector<vector<int>> finalVector;//initalize the set that will be returned

    for (int i = 0; i < subsetCount; i++)
    {
        vector<int> tempSet;

        for (int a = 0; a < subsetSize; a++)
        {
            int randNum = rand() % max_elem + 1;
            tempSet.push_back(randNum);
        }
        finalVector.push_back(tempSet);
    }

    return finalVector;
}

void vectorPrinter(vector<vector<int>> & vec)
{
    int i = 0;
    int j = 0;
    for (i = 0; i < vec.size(); i++)
    {
        cout << "Vector " << i + 1 << ": ";
        for (j = 0; j < vec[i].size(); j++)
        {
            cout << vec[i][j] << " ";
        }
        cout << endl;
    }
    
}

vector<vector<int>> edgeCase1()
{
    
    vector<int> vec1{ 1,2,3,4 };
    vector<int> vec2{ 2,5,6,7 };
    vector<int> vec3{ 3,8,9,10 };
    vector<int> vec4{ 4,11,12,13 };

    vector<vector<int>>  finalVec{vec1,vec2,vec3,vec4};
    return finalVec;
}
vector<vector<int>> edgeCase2()
{

    vector<int> vec1{ 1,2,3,4,5 };
    vector<int> vec2{ 6,7,2,9 };
    vector<int> vec3{ 10,11,12 };
    vector<int> vec4{ 13 };
    vector<int> vec5{ 14,15,32 };

    vector<vector<int>>  finalVec{ vec1,vec2,vec3,vec4,vec5 };
    return finalVec;
}
vector<vector<int>> edgeCase3()
{
    vector<vector<int>>  finalVec;
    return finalVec;
}

void timeVecPrinter(vector<double> & timeVector)
{
    cout << "Vector: ";
    for (int i = 0; i < timeVector.size(); i++)
    {
        cout << timeVector[i] << " ";
    }
    cout << endl;
}

double calculateSD(vector<double> & data)
{
    double sum = 0.0, mean, standardDeviation = 0.0;
    for (int i = 0; i < data.size(); i++)
    {
        sum += data[i];
    }
    mean = sum / data.size();
    for (int j = 0; j < data.size(); j++)
    {
        standardDeviation += pow(data[j] - mean, 2);
    }
    standardDeviation = sqrt(standardDeviation / data.size());

    return standardDeviation;
}

double calculateStandardError(double sd, int N)
{
    return sd / sqrt(N);
}

void getRunningTime(vector<double> runningTimes)
{
    double totalTime = 0.0;
    int N = runningTimes.size();
    for (int i = 0; i < N; i++)
    {
        totalTime += runningTimes[i];
    }

    double standardDeviation = calculateSD(runningTimes);
    
    double m = totalTime / N;

    //const double tval90 = 1.660;
    //const double tval95 = 1.904;
    //const double tval90 = 1.676;//N=50
    //const double tval95 = 2.009;

    const double tval90 = 1.372;//
    const double tval95 = 1.812;

    double sm = calculateStandardError(standardDeviation, N);

    double upperMean90 = m + tval90 * sm;
    double lowerMean90 = m - tval90 * sm;

    double upperMean95 = m + tval95 * sm;
    double lowerMean95 = m - tval95 * sm;

    cout << "Mean Time: " << m << " ms" << endl;
    cout << "SD: " << standardDeviation << endl;
    cout << "Standard Error: " << sm << endl;
    cout << "%90-CL: " << upperMean90 << " - " << lowerMean90 << endl;
    cout << "%95-CL: " << upperMean95 << " - " << lowerMean95 << endl;
    runningTimes.clear();
}

vector<int> randomVector_size(int size_v) {
    int size = size_v;
    vector<int> v(size);
    for (int i = 0; i < size; i++) {
        v[i] = rand() % 50;
    }
    return v;
}

int main(int argc, const char * argv[]) {
    int srandTest = 12;
    srand(srandTest);
    vector<int> res;
    int count = 0;
    vector<double> timeVector;
    while (count <1)
    {
        int c_size = K - 1;

        /*vector<vector<int>> c;

        for (int a = 0;  a < c_size;  a++)
        {
            c.push_back(randomVector_size(15));
        }*/

        //vector<vector<int> > a (c_size);//initalized at line 203
        vector<string> translated;
       
        vector<vector<int>> c = createSampleNorand(150, c_size, 100000000);//New version, can use paramereters | keep minimu elemnent bigger than 0, or it crashes

        //vector<vector<int>> c = edgeCase1();
        vectorPrinter(c);

        time_t t1 = clock();
        //sorting vectors
        cout << endl;
        sort(c.begin(), c.end(), compare_interval);
        cout << endl;

        //Translating vectors
        translated = vectorTranslator(c);
        int a = greedy_find(c, translated);
        res.push_back(a);
        cout << a << endl;
        cout << "Running time : " << double(clock() - t1) / CLOCKS_PER_SEC << " seconds\n";
        timeVector.push_back(double(clock() - t1) / CLOCKS_PER_SEC);
        count++;
    }

    timeVecPrinter(timeVector);
    getRunningTime(timeVector);

    for (int i = 0; i < res.size(); i++)
    {
        cout << res[i] << " ";
    }
    return 0;
}

//Creating and printing vectors
       /*for(int i = 0; i < c.size(); i++) {
           c[i] = randomVectorGenerator();
           cout << "vector " << i + 1 << ":  ";
           vectorPrinter(c[i]);
       }*/