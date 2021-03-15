#ifndef ASTAR_H
#define ASTAR_H

#endif // ASTAR_H
#include"heap.h"
#include<QDebug>
#include<math.h>
#include<cmath>


class AStar
{
private:
    int Row;
    int Column;
    Heap* heap;
    int CurrentCost;
    int LeastCost;
    Step* Begin;
    int **Puzzle;
public:
    AStar(int row,int column,int **puzzle,int Beginx,int Beginy)
    {
        Row=row;
        Column=column;
        Begin=new Step(0,Row,Column,puzzle);
        Begin->From=0;                //之前的状态  1上，2，下，3，左，4右
        Begin->EmptyX = Beginx;
        Begin->EmptyY = Beginy;
        /*if(Row*Column==16)
        {
            Begin->EmptyX=0;
            Begin->EmptyY=0;
        }*/
        heap=new Heap(Begin);
        LeastCost=GetCost(puzzle,0);
    }

    Step* BFS()
    {
        int CurrentRow=Begin->EmptyX;                //空白格的行
        int CurrentColumn=Begin->EmptyY;          //空白格的列
        int exchange;                        //交换
        Step* CurrentStep=Begin;             //当前状态
        OutPut(CurrentStep->Puzzle);
        while(1)
        {
            if(IfWin(CurrentStep->Puzzle))
            {
                break;
            }

            exchange=CurrentStep->Puzzle[CurrentRow][CurrentColumn];                                  //存储空白格位置
            if(CurrentRow+1<=Row-1 &&CurrentStep->From!=1)                                        //下移
            {
                Step* NewNode = new Step(CurrentStep->Count + 1, Row, Column, CurrentStep->Puzzle, CurrentStep);
                NewNode->Puzzle[CurrentRow][CurrentColumn] = NewNode->Puzzle[CurrentRow + 1][CurrentColumn];
                NewNode->Puzzle[CurrentRow + 1][CurrentColumn] = exchange;
                NextStep(NewNode);

                NewNode->EmptyX = CurrentStep->EmptyX + 1;
                NewNode->EmptyY = CurrentStep->EmptyY;
                NewNode->From = 2;
                NewNode->Cost = GetCost(NewNode->Puzzle, NewNode->Count);
            }
            if(CurrentRow-1>=0 &&CurrentStep->From!=2)                                            //上移
            {
                Step* NewNode = new Step(CurrentStep->Count + 1, Row, Column, CurrentStep->Puzzle, CurrentStep);
                NewNode->Puzzle[CurrentRow][CurrentColumn] = NewNode->Puzzle[CurrentRow - 1][CurrentColumn];
                NewNode->Puzzle[CurrentRow - 1][CurrentColumn] = exchange;
                NextStep(NewNode);

                NewNode->EmptyX = CurrentStep->EmptyX -1;
                NewNode->EmptyY = CurrentStep->EmptyY;
                NewNode->From = 1;
                NewNode->Cost = GetCost(NewNode->Puzzle, NewNode->Count);
            }
            if(CurrentColumn+1<=Column-1&&CurrentStep->From!=3)                                   //右移
            {
                Step* NewNode = new Step(CurrentStep->Count + 1, Row, Column, CurrentStep->Puzzle, CurrentStep);
                NewNode->Puzzle[CurrentRow][CurrentColumn] = NewNode->Puzzle[CurrentRow][CurrentColumn + 1];
                NewNode->Puzzle[CurrentRow][CurrentColumn + 1] = exchange;
                NextStep(NewNode);

                NewNode->EmptyX = CurrentStep->EmptyX;
                NewNode->EmptyY = CurrentStep->EmptyY +1;
                NewNode->From = 4;
                NewNode->Cost = GetCost(NewNode->Puzzle, NewNode->Count);
            }
            if(CurrentColumn-1>=0&&CurrentStep->From!=4)                                          //左移
            {
                Step* NewNode = new Step(CurrentStep->Count + 1, Row, Column, CurrentStep->Puzzle, CurrentStep);
                NewNode->Puzzle[CurrentRow][CurrentColumn] = NewNode->Puzzle[CurrentRow][CurrentColumn - 1];
                NewNode->Puzzle[CurrentRow][CurrentColumn - 1] = exchange;
                NextStep(NewNode);

                NewNode->EmptyX = CurrentStep->EmptyX;
                NewNode->EmptyY = CurrentStep->EmptyY -1;
                NewNode->From = 3;
                NewNode->Cost = GetCost(NewNode->Puzzle, NewNode->Count);
            }

            CurrentStep=heap->GetTop();
            heap->PopTop();
            CurrentRow = CurrentStep->EmptyX;
            CurrentColumn = CurrentStep->EmptyY;
            //OutPut(CurrentStep->Puzzle);
        }

        return CurrentStep;
    }

    void NextStep(Step* &NewNode)
    {
        NewNode->Cost=GetCost(NewNode->Puzzle,NewNode->Count);
        int CurrentCost=NewNode->Cost;
        heap->Insert(NewNode);
        if(CurrentCost<LeastCost)
        {
            LeastCost=CurrentCost;
        }              
    }

    void OutPut(int **puzzle)
    {
        qDebug()<<endl;
        for(int i=0;i<Row;i++)
        {
            qDebug()<<puzzle[i][0]<<puzzle[i][1]<<puzzle[i][2];
        }
        qDebug()<<endl;
    }

private:
    int GetCost(int **puzzle,int Step)
    {       
        int Cost = 0;
        int different = 0;
        int Current = 0;
        for (int i = 0; i<Row; i++)
        {
            for (int j = 0; j<Column; j++)
            {
                if (puzzle[i][j] != Current)
                {
                    different+=pow( abs(puzzle[i][j]/Row - i),2)+ pow(abs(puzzle[i][j] % Column - j), 2);
                }
                Current++;
            }
        }
        Cost = different + Step;
        return Cost;
    }   
    bool IfWin(int **puzzle)
    {
        int Current=0;
        for(int i=0;i<Row;i++)
        {
            for(int j=0;j<Column;j++)
            {
                if(puzzle[i][j]!=Current)
                {
                    return false;
                }
                Current++;
            }

        }
        return true;
    }



};






