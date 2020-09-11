#pragma once

/*
struct Icon
{
	Icon(int _w, int _h, ColRGBA** _col);
	int width;
	int height;
	ColRGBA** colors;
};

Icon::Icon(int _w, int _h, ColRGBA** _col)
{
	width = _w;
	height = _h;
	colors = _col;
}

struct DMIcon
{

};

struct IconContextCallback
{

};

struct iobuf
{

};

struct ColRGBA
{
	ColRGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
};

ColRGBA::ColRGBA(uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a) 
{
	r = _a;
	g = _g;
	b = _b;
	a = _r;
}

struct DungClient
{
public:
	DungClient* ptr;
	GetCurrentLoginKey getCurrentLoginKey;

	DungClient();
	DungClient(DungClient* _p);

	const char* GetCurrentLoginKey()
	{
		return getCurrentLoginKey(ptr);
	}
};

DungClient::DungClient() {}

DungClient::DungClient(DungClient* _p)
{
	ptr = _p;
}

struct MapIcon
{
	// size = 0xCC
	// 1st word: 0xAA00BB00 AA counts up, BB counts down by 0x20 when AA is width of list * 0x20 and AA resets to 0x00
	// 2nd word: 0xXX00YY00 seems to be 2D indexers
	// 3rd and 4th word: empty?
	// 5th word: same as first word?
	// 6th word: sorta same-ish as first word?
	// 7th word: empty?
	// 8th word: full
	// 9th word and 10th: 0x20002000
	// 10th,11th,12th: empty?
	// 13th: same as 9th and 10th?
	// 
	
};
*/