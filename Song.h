#ifndef SONG_H
#define SONG_H
#include <vector>
class song
{public:
	enum songlib {first, second};
	song(int[],double[]);
	~song();
	int getCurChannel(int inum);
	double getCurLength(int inum);
private:
	std::vector<int> vChannels;
	std::vector<double> vLengths;
};

#endif