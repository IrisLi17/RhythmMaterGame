#include "Song.h"
#include <fstream>

song::song(int order)
{
    switch(order)
    {
        case 1:
        {
            std::ifstream infile1("channel1.txt",std::ios::in);
            int temp;
            while(!infile1.eof())
            {
                infile1>>temp;
				vChannels.push_back(temp);
            }
            infile1.close();
            std::ifstream infile2("length1.txt",std::ios::in);
            while(!infile2.eof())
            {
                infile2>>temp;
				vLengths.push_back(temp);
            }
            infile2.close();
                      
            break;
        }
        case 2:
        {
            std::ifstream infile1("channel2.txt",std::ios::in);
            int temp;
            while(!infile1.eof())
            {
                infile1>>temp;
				vChannels.push_back(temp);
            }
            infile1.close();
            std::ifstream infile2("length2.txt",std::ios::in);
            while(!infile2.eof())
            {
                infile2>>temp;
				vLengths.push_back(temp);
            }
            infile2.close();
                      
            break;
        }
        case 3:
        {
            std::ifstream infile1("channel3.txt",std::ios::in);
            int temp;
            while(!infile1.eof())
            {
                infile1>>temp;
				vChannels.push_back(temp);
            }
            infile1.close();
            std::ifstream infile2("length3.txt",std::ios::in);
            while(!infile2.eof())
            {
                infile2>>temp;
				vLengths.push_back(temp);
            }
            infile2.close();
                      
            break;
        }
        default:break;

    }
    
}

song::~song(){}


std::vector<int>& song::getChannels()
{
    return vChannels;
}

std::vector<double>& song::getLengths()
{
    return vLengths;
}


int song::size()
{
	return vChannels.size()>vLengths.size()?vLengths.size():vChannels.size();
}