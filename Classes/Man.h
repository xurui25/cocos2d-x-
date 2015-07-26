#ifndef __MAN_H__
#define __MAN_H__

class Man 
{
private:
	int blood_for_man;
	int speed_for_man;
	int power_of_man;
	int dis_of_man;

public:
	Man();
	~Man();

	virtual int getBlood();
	virtual int getSpeed();
	virtual int getPower();
	virtual int getDis();

	virtual void setBlood(int i);
	virtual void setSpeed(int i);
	virtual void setPower(int i);
	virtual void setDis(int i);
};

#endif