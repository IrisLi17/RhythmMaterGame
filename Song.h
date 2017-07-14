#ifndef SONG_H
#define SONG_H
#include <vector>
class song
{public:
	enum songlib {first, second};
	song(int);
	~song();
	//int getCurChannel(int inum);
	//double getCurLength(int inum);
    std::vector<int>& getChannels();
    std::vector<double>& getLengths();
    //vector<double>& getYpos();
    int size();
private:
	std::vector<int> vChannels;
	std::vector<double> vLengths;
    //std::vector<double> vYpos;
};

#endif

//文件读入vChannels,vLengths,vYpos
//初始化存到数据成员里面，根据传入参数决定读哪首曲子
//getNext接口获取
//GameControl里面调用