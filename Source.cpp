#include "body.h"
#include "func.h"
#include "music.h"
#include "video.h"

using namespace std;

int main()
{
	std::thread program(quest);
	std::thread music(playmusicX);
	program.join();
	music.join();
}