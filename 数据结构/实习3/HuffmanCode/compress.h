#ifndef COMPRESS_H
#define COMPRESS_H
#endif // COMPRESS_H
#include<huffmantree.h>
#include<fstream>
#include<QFile>



class HufumanCompress
{
private:
    HuffmanTree tree;
    long long *WeightS;
    unsigned int *Code;  //编码
    int *Length;         //编码长度
public:
    HufumanCompress()
    {
        WeightS = new long long[256]; //频率
        for (int i = 0; i < 256; i++)
        {
            WeightS[i] = 0;
        }
    }




    void Compress(QString FilePath,QString FileSuffix)  //压缩
    {
        QString CompressFilePath=FilePath.mid(0,FilePath.size()-FileSuffix.size());
        CompressFilePath+="huf";


        QByteArray STRING=FileSuffix.toLatin1();
        char *suffix=STRING.data();
        int suffixSize=FileSuffix.size();


        unsigned char data[1024];  //读取数据
        long long SumCount = 0;    //字符总数
        QFile InFile(FilePath);
        InFile.open(QIODevice::ReadOnly);
        int GetNumber=0;
        while (!InFile.atEnd())
        {
            GetNumber=InFile.read((char*)data,sizeof(unsigned char)*1024);
            for (int i = 0; i < GetNumber; i++)
            {
                WeightS[data[i]]++;
            }
        }

        tree.BuildTree(WeightS);             //建立Huffman树
        SumCount = tree.GetRoot()->Weight;   //字符总数
        InFile.close();
        Code=tree.GetAllCode();              //编码
        Length=tree.GetAllCodeLength();      //各编码长度


        /*******************      压缩     ****************************/
        QFile OutFile3(CompressFilePath);
        OutFile3.open(QIODevice::WriteOnly);
        OutFile3.write((char*)&suffixSize, sizeof(int)*1);
        OutFile3.write((char*)suffix, sizeof(char) * suffixSize);
        for (int i = 0; i < 256; i++)
        {
            OutFile3.write((char*)&WeightS[i], sizeof(long long) * 1);
        }
        unsigned int *CodeData=new unsigned int[1024];   //压缩数据
        unsigned int *CodeData1=new unsigned int[1024];  //压缩数据
        for (int i = 0; i < 1024; i++)
        {
            CodeData[i] = 0;
            CodeData1[i] = 0;
        }
        int CodeDataLength = 32;    //一个unsigned int压缩数据长度
        int CodeDataNumber = 0;     //压缩数据当前位置
        int currentLength;          //当前字符 Huffman编码的长度
        unsigned int currentcode;   //当前字符 Huffman编码
        int difference;             //长度差值
        QFile OutFile1(FilePath);             //读取
        OutFile1.open(QIODevice::ReadOnly);

        while (!OutFile1.atEnd())
        {

            int GetNumber =OutFile1.read((char*)data, sizeof(unsigned char) * 1024);
            for (int i = 0; i < GetNumber; i++)
            {
                currentLength = Length[data[i]];
                currentcode = Code[data[i]];

                if (CodeDataLength > currentLength)
                {
                    CodeData[CodeDataNumber] <<= currentLength;
                    CodeDataLength -= currentLength;
                    CodeData[CodeDataNumber] |= currentcode;
                    SumCount--;
                    if (SumCount==0)
                    {
                        CodeData[CodeDataNumber] <<= (CodeDataLength);
                        OutFile3.write((char*)CodeData, sizeof(unsigned int) * (CodeDataNumber+1));
                        break;
                    }
                }
                else
                {
                    difference = currentLength - CodeDataLength;  //长度差值
                    CodeData[CodeDataNumber] <<= CodeDataLength;  //空出差值的长度
                    currentcode >>= difference;
                    CodeData[CodeDataNumber] |= currentcode;   //存入差值长度的数据   !!!!!
                    SumCount--;
                    CodeDataNumber++;
                    CodeDataLength = 32;
                    if (CodeDataNumber != 1024)               //!!!!!!
                    {
                        CodeData[CodeDataNumber] <<= difference;
                        currentcode <<= difference;
                        currentcode = Code[data[i]] ^ currentcode;
                        CodeData[CodeDataNumber] |= currentcode;
                        CodeDataLength -= difference;
                        if (SumCount == 0)
                        {
                            CodeData[CodeDataNumber] <<= (CodeDataLength );
                            OutFile3.write((char*)CodeData, sizeof(unsigned int) * (CodeDataNumber+1));
                            break;
                        }

                    }
                    else
                    {
                        CodeDataNumber = 0;
                        CodeData1[0] = 0;
                        CodeData1[CodeDataNumber] <<= difference;
                        currentcode <<= difference;
                        currentcode = Code[data[i]] ^ currentcode;
                        CodeData1[CodeDataNumber] |= currentcode;
                        CodeDataLength -= difference;
                        OutFile3.write((char*)CodeData, sizeof(unsigned int) * 1024);
                        CodeData[0] = CodeData1[0];
                        CodeData1[0] = 0;
                        if (SumCount == 0)
                        {
                            CodeData[CodeDataNumber] <<= (CodeDataLength);
                            OutFile3.write((char*)CodeData[0], sizeof(unsigned int) * 1);
                            break;
                        }
                    }
                }
            }
            if (SumCount == 0)
            {
                break;
            }
        }

    }


    void DeCompress(QString FilePath,QString FileSuffix)
    {      
        QFile InFile(FilePath);
        InFile.open(QIODevice::ReadOnly);


        int suffixSize=FileSuffix.size();
        InFile.read((char*)&suffixSize, sizeof(int)*1);
        char *suffix=new char[suffixSize+1];

        InFile.read((char*)suffix, sizeof(char) * suffixSize);
        suffix[suffixSize]='\0';
        QString CompressFileSuffix=QString(QLatin1String(suffix));
        QString CompressFilePath=FilePath.mid(0,FilePath.size()-FileSuffix.size()-1);
        CompressFilePath+="解压.";
        CompressFilePath+=CompressFileSuffix;

        long long SumCount = 0;    //字符总数
        long long *RebuildWeightS = new long long[256];
        for (int i = 0; i < 256; i++)
        {
            InFile.read((char*)&RebuildWeightS[i], sizeof(long long) * 1);
        }
        HuffmanTree tree1;
        tree1.BuildTree(RebuildWeightS);
        SumCount = tree1.GetRoot()->Weight;       
        QFile OutFile(CompressFilePath);
        OutFile.open(QIODevice::WriteOnly);
        unsigned int *CodeData = new unsigned int[1024];  //压缩数据
        unsigned char *data = new unsigned char[1024];
        for (int i = 0; i < 1024; i++)
        {
            CodeData[i] = 0;
        }
        int InPutNumber = 0;                              //写入的当前位置
        int CodeDataLength = 31;
        unsigned int CurrentCode = 0;
        TreeNode *CurrentTreeNode = tree1.GetRoot();
        do
        {
            int GetNumber =InFile.read((char*)CodeData, sizeof(unsigned int) * 1024);

            for (int i = 0; i < GetNumber/4; i++)
            {
                for (int j = 0; j < 32; j++)
                {
                    CurrentCode = CodeData[i] >> CodeDataLength;
                    CurrentCode = CurrentCode << 31;
                    CurrentCode = CurrentCode >> 31;
                    if (CurrentCode==0)
                    {
                        CurrentTreeNode= CurrentTreeNode->LeftChild;
                    }
                    else
                    {
                        CurrentTreeNode = CurrentTreeNode->RightChild;
                    }
                    if (CurrentTreeNode->LeftChild == NULL && CurrentTreeNode->RightChild == NULL)
                    {
                        SumCount--;
                        data[InPutNumber] = CurrentTreeNode->Data;
                        CurrentTreeNode= tree1.GetRoot();
                        InPutNumber++;

                        if (SumCount == 0)
                        {
                            OutFile.write((char*)data, sizeof(unsigned char) * (InPutNumber));
                            break;
                        }
                        else
                        {
                            if (InPutNumber == 1024)
                            {
                                OutFile.write((char*)data, sizeof(unsigned char) * (InPutNumber));
                                InPutNumber = 0;
                            }
                        }
                    }
                    CodeDataLength--;
                }
                if (SumCount == 0)
                {
                    break;
                }
                CodeDataLength = 31;
            }
            if (SumCount == 0)
            {
                break;
            }
        }while (!InFile.atEnd());

    }

};

