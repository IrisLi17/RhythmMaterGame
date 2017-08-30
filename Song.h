#ifndef SONG_H
#define SONG_H
#include <vector>
class song
{public:
	song(int);
	~song();
    std::vector<int>& getChannels();
    std::vector<double>& getLengths();
    int size();

private:
	std::vector<int> vChannels;
	std::vector<double> vLengths;
};

#endif
