#ifndef SONG_H
#define SONG_H
#include <vector>
class song
{public:
	//enum songlib {first, second};
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
