#ifndef SCORE_H
#define SCORE_H

class Score
{
private:

public:
	Score();
	~Score();

	void setPatenteEffect();

	void sendAlert();

	bool draw();
	bool drawZone();
	bool drawScore();
	bool drawModoBot();
	bool drawImgPVP();
	bool drawBoss(int);
};

#endif