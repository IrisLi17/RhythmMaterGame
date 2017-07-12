#include "Song.h"
song::song(int ch[],double len[])
{
	vChannels.assign(ch,ch+sizeof(ch)/sizeof(int));
	vLengths.assign(len,len+sizeof(len)/sizeof(double);
}
song::~song(){}
int song::getCurChannel(int inum)
{
	return vChannels[inum];
}
double song::getCurLength(int inum)
{
	return vLengths[inum];
}