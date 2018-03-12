#include<stdio.h>
#include<iostream>
#include<queue>
#include<vector>
#include<algorithm>
#include<stack>

#define sz 500
#define dim 3
#define inf 10000

int indexOfBoardArray=0;

int board[dim][dim];
int testUp[dim][dim];
int testDown[dim][dim];
int testLeft[dim][dim];
int testRight[dim][dim];

int goal[dim][dim] = { {1, 2, 3}, {4, 5, 6}, {7, 8, 0} };

int numberOfDisplacePosition(int arr[dim][dim]);
void getInput();
void solvingAgent();
void generateTest(int r, int c);
void printBoard();
bool isExistInBoardArray(int arr[dim][dim]);

struct boardArray
{
    int testBoard[dim][dim];
}object[sz];

using namespace std;

int main()
{
    getInput();
    solvingAgent();

    return 0;
}

void getInput()
{
    cout<<"Enter The initial State : \n";
    for(int i=0; i<dim; i++)
        for(int j=0; j<dim; j++)
            cin>>board[i][j];
}


void solvingAgent()
{
    int itteration=1;
    while(true)
    {
        int r, c;
        for(int i=0; i<dim; i++)
        {
            for(int j=0; j<dim; j++)
            {
                if(board[i][j]==0)
                {
                    r = i;
                    c = j;
                }
            }
        }

        generateTest(r, c);
        cout<<"\nItteration Number : "<<itteration++<<"\nCurrent Board : \n";

        printBoard();

        if(numberOfDisplacePosition(board) == 0)
            break;
    }
}


void printBoard()
{
    for(int i=0; i<dim; i++)
    {
        for(int j=0; j<dim; j++)
            cout<<board[i][j]<<" ";
        cout<<endl;
    }
}


void generateTest(int r, int c)
{
    int costU, costD, costL, costR;

    for(int i=0; i<dim; i++)
    {
        for(int j=0; j<dim; j++)
        {
            testUp[i][j] = board[i][j];
            testDown[i][j] = board[i][j];
            testLeft[i][j] = board[i][j];
            testRight[i][j] = board[i][j];
        }
    }
    if(r == 0) // for up
        costU = inf;
    else
    {
        swap(testUp[r][c], testUp[r-1][c]);
        costU = numberOfDisplacePosition(testUp);
    }

    if(r==2)
        costD = inf;
    else
    {
        swap(testDown[r][c], testDown[r+1][c]);
        costD = numberOfDisplacePosition(testDown);
    }

    if(c==0)
        costL = inf;
    else
    {
        swap(testLeft[r][c], testLeft[r][c-1]);
        costL = numberOfDisplacePosition(testLeft);
    }

    if(c==2)
        costR = inf;
    else
    {
        swap(testRight[r][c], testRight[r][c+1]);
        costR = numberOfDisplacePosition(testRight);
    }

    int cost[4];
    cost[0] = costU;
    cost[1] = costD;
    cost[2] = costL;
    cost[3] = costR;

    vector<int>cv; //current vector

    for(int i=0; i<4; i++)
    {
        if(cost[i] == inf)
            continue;

        if(i==0) //up
        {
            bool bl = isExistInBoardArray(testUp);
            if(!bl)
                cv.push_back(i);
        }
        if(i==1) //down
        {
            bool bl = isExistInBoardArray(testDown);
            if(!bl)
                cv.push_back(i);
        }
        if(i==2) // left
        {
            bool bl = isExistInBoardArray(testLeft);
            if(!bl)
                cv.push_back(i);
        }
        if(i==3)
        {
            bool bl = isExistInBoardArray(testRight);
            if(!bl)
                cv.push_back(i);
        }
    }

    vector<int>V; // V e cost
    int len = cv.size(); // cv te index

    for(int i=0; i<len; i++)
        V.push_back(cost[cv[i]]);

    sort(V.begin(), V.end());

    int idx = 0;
    int minimumCost = V[idx];

    if(minimumCost == costU)
    {
        for(int i=0; i<dim; i++)
            for(int j=0; j<dim; j++)
                board[i][j] = testUp[i][j];
        return;
    }

    else if(minimumCost == costD)
    {
        for(int i=0; i<dim; i++)
            for(int j=0; j<dim; j++)
                board[i][j] = testDown[i][j];
    }

    else if(minimumCost == costL)
    {
        for(int i=0; i<dim; i++)
            for(int j=0; j<dim; j++)
                board[i][j] = testLeft[i][j];
    }

    else if(minimumCost == costR)
    {
        for(int i=0; i<dim; i++)
            for(int j=0; j<dim; j++)
                board[i][j] = testRight[i][j];
    }
}


int numberOfDisplacePosition(int arr[dim][dim])
{
    int counter=0;
    for(int i=0; i<dim; i++)
    {
        for(int j=0; j<dim; j++)
            if(arr[i][j] != goal[i][j])
                counter++;
    }

    return counter;
}


bool isExistInBoardArray(int arr[dim][dim])
{
    for(int k=0; k<indexOfBoardArray; k++)
    {
        int count=0;
        for(int i=0; i<dim; i++)
        {
            for(int j=0; j<dim; j++)
            {
                if(object[k].testBoard[i][j] == arr[i][j])
                    count++;
            }
        }
        if(count == 9)
        {
            // thakle true
            return true;
        }
    }

    for(int i=0; i<dim; i++)
    {
        for(int j=0; j<dim; j++)
            object[indexOfBoardArray+1].testBoard[i][j] = arr[i][j];
    }
    indexOfBoardArray++;

    return false;
}

/*
valid :
 1 2 3 4 5 6 7 0 8
 1 2 3 4 5 6 0 7 8
 1 2 0 4 5 3 7 8 6
 1 2 3 0 8 5 4 7 6
 0 2 3 1 8 5 4 7 6
 2 0 3 1 8 5 4 7 6
 2 3 0 1 8 5 4 7 6
 2 3 0 1 8 5 4 7 6
 4 1 3 0 2 5 7 8 6
*/
