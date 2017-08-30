#include "Song.h"
#include <qfile.h>
#include <qtextstream.h>
#include <qdebug.h>

//构造函数，根据级别将对应通道和长度数据序列读入程序
song::song(int order)
{
    switch(order)
    {
        case 1:
        {
            QFile file1(":/data/channel1.txt");
			if(!file1.open(QIODevice::ReadOnly |QIODevice::Text))
			{
				qDebug()<<"Can't open file!"<<endl;
			}
			QTextStream in1(&file1);
			int temp;
			while(!in1.atEnd())
			{
				in1>>temp;
				vChannels.push_back(temp);
			}
			file1.close();

			QFile file2(":/data/length1.txt");
			if(!file2.open(QIODevice::ReadOnly | QIODevice::Text))
			{
				qDebug()<<"Can't open file!"<<endl;
			}
			QTextStream in2(&file2);
			while(!in2.atEnd())
			{
				in2>>temp;
				vLengths.push_back(temp);
			}
            file2.close();
                      
            break;
        }
        case 2:
        {
            QFile file1(":/data/channel2.txt");
			if(!file1.open(QIODevice::ReadOnly |QIODevice::Text))
			{
				qDebug()<<"Can't open file!"<<endl;
			}
			QTextStream in1(&file1);
			int temp;
			while(!in1.atEnd())
			{
				in1>>temp;
				vChannels.push_back(temp);
			}
			file1.close();

			QFile file2(":/data/length2.txt");
			if(!file2.open(QIODevice::ReadOnly | QIODevice::Text))
			{
				qDebug()<<"Can't open file!"<<endl;
			}
			QTextStream in2(&file2);
			while(!in2.atEnd())
			{
				in2>>temp;
				vLengths.push_back(temp);
			}
            file2.close();
                      
            break;
        }
        case 3:
        {
            QFile file1(":/data/channel3.txt");
			if(!file1.open(QIODevice::ReadOnly |QIODevice::Text))
			{
				qDebug()<<"Can't open file!"<<endl;
			}
			QTextStream in1(&file1);
			int temp;
			while(!in1.atEnd())
			{
				in1>>temp;
				vChannels.push_back(temp);
			}
			file1.close();

			QFile file2(":/data/length3.txt");
			if(!file2.open(QIODevice::ReadOnly | QIODevice::Text))
			{
				qDebug()<<"Can't open file!"<<endl;
			}
			QTextStream in2(&file2);
			while(!in2.atEnd())
			{
				in2>>temp;
				vLengths.push_back(temp);
			}
            file2.close();
                      
            break;
        }
        default:break;

    }
    
}

song::~song(){}

//返回通道序列
std::vector<int>& song::getChannels()
{
    return vChannels;
}

//返回长度序列
std::vector<double>& song::getLengths()
{
    return vLengths;
}

//歌曲有效长度
int song::size()
{
	return vChannels.size()>vLengths.size()?vLengths.size():vChannels.size();
}