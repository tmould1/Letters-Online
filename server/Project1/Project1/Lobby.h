#pragma once
class Lobby
{
private:
	vector<Player *> players;
	vector<Player *>::iterator playerIterator;
	vector<Game *> games;
	vector<Game *> gameIterator;
public:
	Lobby();
	~Lobby();
};

