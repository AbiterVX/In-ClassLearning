#ifndef PRESSCLASS_H
#define PRESSCLASS_H
#endif // PRESSCLASS_H

#include<QFile>
#include <windows.h>
#include<QDebug>
#include<QVector>
#include<QStack>
class PressPicture
{
public:
    PressPicture()
    {
        Header3 = (RGBQUAD *)malloc(256*sizeof(RGBQUAD));//调色板的大小为1024字节
        for ( int i = 0; i < 256; i++ ){
            Header3[i].rgbRed = Header3[i].rgbGreen = Header3[i].rgbBlue = i;
        }
    }
    void ReadBitMap(QString PictureName) //解析8位图文件格式，获取信息，并存入内存
    {
        QFile BMPinformation(PictureName);
        BMPinformation.open(QIODevice::ReadOnly);
        BMPinformation.read((char*)&Header1 , sizeof(Header1));
        BMPinformation.read((char*)&Header2 , sizeof(Header2));

        int RGBQUADCount=(Header1.bfOffBits-54)/4;
        BMPinformation.read((char*)Header3 , sizeof(RGBQUAD)*RGBQUADCount);

        Height=Header2.biHeight;
        Width=Header2.biWidth;
        BitCount=Height*Width;
        BitS=new uchar[BitCount];

        bool reverse=0;
        uchar current;
        for(int i=0;i<Height;i++)
        {
            if(reverse==0)
            {
                for(int j=0;j<Width;j++)
                {
                    BMPinformation.read( (char*)&current, sizeof(uchar) );                    
                    BitS[i*Width+j]=current;

                }
                reverse=1;
            }
            else
            {
                for(int j=Width-1;j>=0;j--)
                {
                    BMPinformation.read( (char*)&current, sizeof(uchar) );
                    BitS[i*Width+j]=current;                    
                }
                reverse=0;
            }
        }        
    }   
    void WriteBitMap(QString FileName)   //内存的信息按格式写到文件
    {       
        QFile file(FileName);
        file.open(QIODevice::ReadWrite);
        file.write( (char*)&Header1,sizeof(Header1));
        file.write((char*)&Header2 , sizeof(Header2));
        int RGBQUADCount=(Header1.bfOffBits-54)/4;
        file.write((char*)Header3 , sizeof(RGBQUAD)*RGBQUADCount);

        bool reverse=0;
        for(int i=0;i<Height;i++)
        {           
            if(reverse==0)
            {
                for(int j=0;j<Width;j++)
                {
                    file.write((char*)&BitS[i*Width+j], sizeof(uchar) );
                }
                reverse=1;
            }
            else
            {
                for(int j=Width-1;j>=0;j--)
                {
                    file.write((char*)&BitS[i*Width+j], sizeof(uchar) );
                }
                reverse=0;
            }
        }

    }

    void Compress(QString FileName)      //压缩
    {
        /*******************************-预处理，设置初始值-********************************/
        uchar* SegmentLength=new uchar[BitCount]{0};  //各个段长  减一
        for(int i=0;i<BitCount;i++)
        {            
            for(int j=7;j>=0;j--)
            {                
                if(BitS[i]>>j)
                {
                    SegmentLength[i]=j;
                    break;
                }                
            }           
        }

        /***********************动态规划*******************************/
        int* Map=new int[BitCount]{0};             //表格
        Map[0]=SegmentLength[0]+11;

        QVector<int> *CutS=new QVector<int>[BitCount];
        CutS[0].push_back(0);
        CutS[0].push_back(1);
        /*for(int i=0;i<BitCount;i++)
        {
            CutS[BitCount-1].push_back(i);
        }
        CutS[BitCount-1].push_back(BitCount);*/

        int Current=0;
        int CurrentCut=0;
        int MaxLength=0;

        for(int i=1;i<BitCount;i++)
        {
            Map[i]=Map[i-1]+11+SegmentLength[i]+1;  ////////////!!!!!!!!!!!!!1
            CurrentCut=i;
            MaxLength=SegmentLength[i];
            for(int j=i;j>=0;j--)
            {
                if(MaxLength<SegmentLength[j])
                {
                    MaxLength=SegmentLength[j];
                }
                MaxLength+=1;

                if(j>=1){
                    Current=Map[j-1]+MaxLength*(i-j+1)+11;
                }
                else{
                    Current=MaxLength*(i-j+1)+11;
                }

                if(Current<Map[i])
                {
                    Map[i]=Current;
                    CurrentCut=j;
                }

                MaxLength--;
                if(i-j+1>=256)  //!!!!!!!!!!!
                {
                    break;
                }
            }

            if(i!=CurrentCut)
            {
                if(CurrentCut==0){
                    CutS[i].push_back(0);
                }
                else{                  
                    CutS[i]=CutS[CurrentCut-1];
                }
            }
            else
            {              
                CutS[i]=CutS[i-1];
            }
            CutS[i].push_back(i+1);
            if(i>500)
            {
                QVector<int> null;                
                CutS[i-500].swap(null);
            }            
        }

        /*qDebug()<<CutS[BitCount-1].length();
        for(int i=0;i<CutS[BitCount-1].length();i++)
        {
            qDebug()<<CutS[BitCount-1][i];
        }*/

        /****************************************-压缩-******************************************/

        unsigned int *CompressData1=new unsigned int[1024]{0};   //压缩数据1
        unsigned int *CompressData2=new unsigned int[1024]{0};   //压缩数据2
        QFile CompressFile(FileName);
        CompressFile.open(QIODevice::WriteOnly);
        CompressFile.write((char*)&Header1 , sizeof(Header1)*1);
        CompressFile.write((char*)&Header2 , sizeof(Header2)*1);
        int RGBQUADCount=(Header1.bfOffBits-54)/4;
        CompressFile.write((char*)Header3 , sizeof(RGBQUAD)*RGBQUADCount);

        int Length=CutS[BitCount-1].size();
        uint CurrentLength=0;                   //段长
        uint CurrentSegmentLength=0;            //段数
        int CurrentPosition=0;                 //当前数组位置
        int CurrentIntPosition=0;              //int内的位置


        unsigned int CurrentBIT=0;
        int length=0;
        for(int i=1;i<Length;i++)
        {
            CurrentSegmentLength=CutS[BitCount-1][i]-CutS[BitCount-1][i-1];                 //段数
            CurrentSegmentLength--;
            CurrentLength=SegmentLength[CutS[BitCount-1][i-1]];                             //段长
            for(int k=CutS[BitCount-1][i-1];k<CutS[BitCount-1][i];k++)
            {
                if(CurrentLength<SegmentLength[k])
                {
                    CurrentLength=SegmentLength[k];
                }
            }         
            if(32-CurrentIntPosition>=8){
                CompressData1[CurrentPosition]|=(CurrentSegmentLength<<(32-CurrentIntPosition-8));
                CurrentIntPosition+=8;
                if(CurrentIntPosition==32)
                {
                    CurrentPosition++;
                    CurrentIntPosition=0;
                    if(CurrentPosition==1024)
                    {
                        CompressFile.write((char*)CompressData1,sizeof(unsigned int)*1024);
                        CompressData1=CompressData2;
                        CurrentPosition=0;
                    }
                    CompressData1[CurrentPosition]=0;
                }
            }
            else{
                CompressData1[CurrentPosition]|=(CurrentSegmentLength>>(CurrentIntPosition+8-32));
                CurrentPosition++;
                if(CurrentPosition==1024)
                {
                    CompressFile.write((char*)CompressData1,sizeof(unsigned int)*1024);
                    CompressData1=CompressData2;
                    CurrentPosition=0;
                }
                CompressData1[CurrentPosition]=0;
                CompressData1[CurrentPosition]|=(CurrentSegmentLength<<(32-(CurrentIntPosition+8-32)));
                CurrentIntPosition=CurrentIntPosition+8-32;
            }

            CurrentSegmentLength++;
            if(32-CurrentIntPosition>=3)
            {
                CompressData1[CurrentPosition]|=(CurrentLength<<(32-CurrentIntPosition-3));
                CurrentIntPosition+=3;
                if(CurrentIntPosition==32)
                {
                    CurrentPosition++;
                    CurrentIntPosition=0;
                    if(CurrentPosition==1024)
                    {
                        CompressFile.write((char*)CompressData1,sizeof(unsigned int)*1024);
                        CompressData1=CompressData2;
                        CurrentPosition=0;
                    }
                    CompressData1[CurrentPosition]=0;
                }
            }
            else
            {
                CompressData1[CurrentPosition]|=(CurrentLength>>(3-(32-CurrentIntPosition)) );
                CurrentPosition++;
                if(CurrentPosition==1024)
                {
                    CompressFile.write((char*)CompressData1,sizeof(unsigned int)*1024);
                    CompressData1=CompressData2;
                    CurrentPosition=0;
                }
                CompressData1[CurrentPosition]=0;
                CompressData1[CurrentPosition]|=(CurrentLength<<(29+(32-CurrentIntPosition)) );
                CurrentIntPosition=CurrentIntPosition+3-32;
            }

            length=CurrentLength+1;
            for(int j=CutS[BitCount-1][i-1];j<CutS[BitCount-1][i];j++)
            {               
                CurrentBIT=BitS[j];
                if(32-CurrentIntPosition>=length)
                {                  
                    CompressData1[CurrentPosition]|=(CurrentBIT<<(32-CurrentIntPosition-length));
                    CurrentIntPosition+=length;
                    if(CurrentIntPosition==32)
                    {
                        CurrentPosition++;
                        CurrentIntPosition=0;
                        if(CurrentPosition==1024)
                        {
                            CompressFile.write((char*)CompressData1,sizeof(unsigned int)*1024);
                            CompressData1=CompressData2;
                            CurrentPosition=0;
                        }
                        CompressData1[CurrentPosition]=0;
                    }
                }
                else
                {
                    CompressData1[CurrentPosition]|=(CurrentBIT>>(CurrentIntPosition+length-32));                    
                    CurrentPosition++;
                    if(CurrentPosition==1024)
                    {
                        CompressFile.write((char*)CompressData1,sizeof(unsigned int)*1024);
                        CompressData1=CompressData2;
                        CurrentPosition=0;
                    }
                    CompressData1[CurrentPosition]=0; //////////////////!!!!!!!!!!!!
                    CompressData1[CurrentPosition]|=(CurrentBIT<<(32-(CurrentIntPosition+length-32)));
                    CurrentIntPosition=CurrentIntPosition+length-32;
                }              
            }
        }
        if(CurrentIntPosition!=0)
        {
            CurrentPosition++;
            CompressFile.write((char*)CompressData1,sizeof(unsigned int)*CurrentPosition);
        }
        else
        {
            if(CurrentPosition!=0)
            {
                CompressFile.write((char*)CompressData1,sizeof(unsigned int)*CurrentPosition);
            }
        }

    }

    void UnCompress(QString FileName ,QString CompressPath="unpress.bmp")    //解压缩
    {
        QFile ReadFile(FileName);
        ReadFile.open(QIODevice::ReadOnly);
        ReadFile.read((char*)&Header1 , sizeof(Header1));
        ReadFile.read((char*)&Header2 , sizeof(Header2));
        ReadFile.read((char*)Header3 , sizeof(RGBQUAD)*256);

        QFile WriteFile(CompressPath);
        WriteFile.open(QIODevice::WriteOnly);
        WriteFile.write((char*)&Header1 , sizeof(Header1));
        WriteFile.write((char*)&Header2 , sizeof(Header2));
        int RGBQUADCount=(Header1.bfOffBits-54)/4;
        WriteFile.write((char*)Header3 , sizeof(RGBQUAD)*RGBQUADCount);

        Height=Header2.biHeight;
        Width=Header2.biWidth;
        BitCount=Height*Width;
        BitS=new uchar[BitCount];
        uchar *WriteData=new uchar[Width];
        bool reverse=0;
        int WriteCount=0;

        uint Count=0;                        //本段个数
        unsigned int SegmentLength=0;       //本段每段长度
        unsigned int data[1024];            //数据读取

        int CurrentPosition=0;     //数据data的位置
        int CurrentIntPosition=0;  //int中的位置
        int DataCount=0;
        uchar CurrentBit=0;
        uint CurrentBIT=0;
        int CurrentBitCount=0;
        DataCount=ReadFile.read((char*)&data,sizeof(unsigned int)*1024);

        while(CurrentBitCount!=BitCount)
        {
            if(32-CurrentIntPosition>=8){               //////////////!!!!!!!!!!!!!!!
                Count=data[CurrentPosition]<<CurrentIntPosition;
                Count>>=(32-8);
                CurrentIntPosition+=8;
                if(CurrentIntPosition==32)
                {
                    CurrentIntPosition=0;
                    CurrentPosition++;
                    if(CurrentPosition==1024)
                    {
                        DataCount=ReadFile.read((char*)&data,sizeof(unsigned int)*1024);
                        CurrentPosition=0;
                    }
                }
            }
            else{
                Count=data[CurrentPosition]<<(CurrentIntPosition);
                CurrentPosition++;
                if(CurrentPosition==1024)
                {
                    DataCount=ReadFile.read((char*)&data,sizeof(unsigned int)*1024);
                    CurrentPosition=0;
                }

                Count|=(data[CurrentPosition]>>(32-CurrentIntPosition));
                Count>>=(32-8);
                CurrentIntPosition=CurrentIntPosition+8-32;
            }
            Count++;


            if(32-CurrentIntPosition>=3)
            {
                SegmentLength=data[CurrentPosition]<<CurrentIntPosition;
                SegmentLength>>=(32-3);
                SegmentLength++;
                CurrentIntPosition+=3;
                if(CurrentIntPosition==32)
                {
                    CurrentIntPosition=0;
                    CurrentPosition++;
                    if(CurrentPosition==1024)
                    {
                        DataCount=ReadFile.read((char*)&data,sizeof(unsigned int)*1024);
                        CurrentPosition=0;
                    }
                }
            }
            else
            {
                SegmentLength=data[CurrentPosition]<<CurrentIntPosition;
                CurrentPosition++;
                if(CurrentPosition==1024)
                {
                    DataCount=ReadFile.read((char*)&data,sizeof(unsigned int)*1024);
                    CurrentPosition=0;
                }
                SegmentLength|= (data[CurrentPosition]>>(32-CurrentIntPosition) );
                SegmentLength>>=(32-3);
                SegmentLength++;
                CurrentIntPosition=CurrentIntPosition+3-32; /////!!!
            }

            for(int j=0;j<Count;j++)
            {              
                if(32-CurrentIntPosition>=SegmentLength)
                {
                    CurrentBIT=data[CurrentPosition]<<CurrentIntPosition;
                    CurrentBIT>>=(32-SegmentLength);
                    CurrentIntPosition+=SegmentLength;
                    if(CurrentIntPosition==32)
                    {
                        CurrentIntPosition=0;
                        CurrentPosition++;
                        if(CurrentPosition==1024)
                        {
                            DataCount=ReadFile.read((char*)&data,sizeof(unsigned int)*1024);
                            CurrentPosition=0;
                        }
                    }
                }
                else
                {
                    CurrentBIT=data[CurrentPosition]<<CurrentIntPosition;
                    CurrentPosition++;
                    if(CurrentPosition==1024)
                    {
                        DataCount=ReadFile.read((char*)&data,sizeof(unsigned int)*1024);
                        CurrentPosition=0;
                    }

                    CurrentBIT|= (data[CurrentPosition]>>(32-CurrentIntPosition) );   //*****
                    CurrentBIT>>=(32-SegmentLength);
                    CurrentIntPosition=CurrentIntPosition+SegmentLength-32;
                }
                CurrentBit=CurrentBIT;
                if(!reverse){
                    WriteData[WriteCount]=CurrentBit;
                    WriteCount++;
                }
                else{
                    WriteData[Width-1-WriteCount]=CurrentBit;
                    WriteCount++;
                }
                if(WriteCount==Width){
                    WriteFile.write((char*)WriteData , sizeof(uchar)*Width);
                    WriteCount=0;
                    if(reverse==0){
                        reverse=1;
                    }
                    else{
                        reverse=0;
                    }
                }

                CurrentBitCount++;              
                if(CurrentBitCount==BitCount)
                {
                    break;
                }
            }
        }
    }   

private:
    uchar *BitS;
    int BitCount;
    int Height;
    int Width;
    BITMAPFILEHEADER Header1;
    BITMAPINFOHEADER Header2;
    RGBQUAD *Header3;
};










