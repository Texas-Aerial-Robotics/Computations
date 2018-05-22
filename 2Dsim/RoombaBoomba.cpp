#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
using namespace std;

class TargetRoomba
{
private:
	double speed = .33;
	double theta;
	double xpos;
	double ypos;
	bool xRight;
	bool yUp;
public:
	TargetRoomba(double t, double x, double y)
	{
		theta = t;
		xpos = x;
		ypos = y;
	}
	void move()
	{
		xpos += speed * cos(theta);
		ypos += speed * sin(theta);

	}
	void setTheta(double t)
	{
		theta = t;
		if(theta > 2*M_PI)
			theta -= 2*M_PI;
		if(theta < 0.0)
			theta += 2*M_PI;
		if(theta > 0.0 && theta < M_PI)
			yUp = true;
		else
			yUp = false;
		if(theta < M_PI_2 || theta > 3 * M_PI_2)
			xRight = true;
		else
			xRight = false;
	}
	void setx(double x)
	{
		xpos = x;
	}
	void sety(double y)
	{
		ypos = y;
	}
	double getTheta()
	{
		return theta;
	}
	double getx()
	{
		return xpos;
	}
	double gety()
	{
		return ypos;
	}
	bool getxRight()
	{
		return xRight;
	}
	bool getyUp()
	{
		return yUp;
	}
};

class ObstacleRoomba
{ 
private:
	double speed = .33;
	double theta;
	double xpos;
	double ypos;
public:
	ObstacleRoomba(double t, double x, double y)
	{
		theta = t;
		xpos = x;
		ypos = y;
	}
	void setTheta(double t)
	{
		theta = t;
	}
	void setx(double x)
	{
		xpos = x;
	}
	void sety(double y)
	{
		ypos = y;
	}
	void move()
	{
		xpos = 5 * cos(theta);
		ypos = 5 * sin(theta);
	}
	double getTheta()
	{
		return theta;
	}
	double getx()
	{
		return xpos;
	}
	double gety()
	{
		return ypos;
	}
};

int main()
{
	srand(time(NULL));

	TargetRoomba roomba1(0,0,0);
	TargetRoomba roomba2(0,0,0);
	TargetRoomba roomba3(0,0,0);
	TargetRoomba roomba4(0,0,0);
	TargetRoomba roomba5(0,0,0);
	TargetRoomba roomba6(0,0,0);
	TargetRoomba roomba7(0,0,0);
	TargetRoomba roomba8(0,0,0);
	TargetRoomba roomba9(0,0,0);
	TargetRoomba roomba10(0,0,0);
	vector<TargetRoomba> roombas;
	roombas.push_back(roomba1);
	roombas.push_back(roomba2);
	roombas.push_back(roomba3);
	roombas.push_back(roomba4);
	roombas.push_back(roomba5);
	roombas.push_back(roomba6);
	roombas.push_back(roomba7);
	roombas.push_back(roomba8);
	roombas.push_back(roomba9);
	roombas.push_back(roomba10);

	double targetSeparation = M_PI / 5;

	double theta = 0;
	for (int i = 0; i < 10; i++)
	{
		roombas[i].setTheta(theta);
		roombas[i].setx(cos(theta));
		roombas[i].sety(sin(theta));
		theta += targetSeparation;
	}

	ObstacleRoomba obstacle1(0,0,0);
	ObstacleRoomba obstacle2(0,0,0);
	ObstacleRoomba obstacle3(0,0,0);
	ObstacleRoomba obstacle4(0,0,0);
	vector<ObstacleRoomba> obstacles;
	obstacles.push_back(obstacle1);
	obstacles.push_back(obstacle2);
	obstacles.push_back(obstacle3);
	obstacles.push_back(obstacle4);

	double obstacleSeparation = M_PI_2;

	theta = 0;
	for (int i = 0; i < 4; i++)
	{
		obstacles[i].setTheta(theta);
		obstacles[i].setx(5*cos(theta));
		obstacles[i].sety(5*sin(theta));
		theta += obstacleSeparation;
	}


	for(int t = 0; t < 600; t++)
	{
		if(t%20 == 0 && t != 0)
		{
			for(TargetRoomba &r : roombas)
			{
				r.setTheta(r.getTheta()+M_PI);
			}
		}
		else if(t%5 == 0 && t != 0)
		{
			for(TargetRoomba &r : roombas)
			{
				double rando = rand() % 41 - 20;
				rando = rando * M_PI / 180;
				r.setTheta(r.getTheta()+rando);
			}
		}
		//Collisions


		for(int i = 0; i<10; i++)
		{
			bool collision = false;
			bool flip = false;
			for(int j = 0; j<10; j++)
			{
				if(j<5)
				{
					double xSeperation = obstacles[j].getx() - roombas[i].getx();
					double ySeperation = obstacles[j].gety() - roombas[i].getx();
					double seperationMagnitude = sqrt(pow(xSeperation, 2.0)+ pow(ySeperation, 2.0));
					double seperationAngle = asin(ySeperation / seperationMagnitude);

					if(seperationMagnitude <= 0.35)
					{
						if (seperationAngle <= (obstacles[j].getTheta + 90) && seperationAngle >= (obstacles[j].getTheta-90))
						{
							flip = false;
						}
						else if (obstacles[j].getTheta >= -90 && obstacles[j].getTheta <= 0)
						{
							if (seperationAngle >= obstacles[j].getTheta - 90 || seperationAngle <= obstacles[j].getTheta + 90)
							{
								flip = true;
							}
						}
						else if (obstacles[j].getTheta <= 90 && obstacles[j].getTheta >= 0)
						{
							if (seperationAngle <= obstacles[j].getTheta+90 || seperationAngle >= obstacles[j].getTheta - 90)
							{
								flip = true;
							}
						}
						else if (obstacles[j].getTheta + 90 <= seperationAngle && obstacles[j].getTheta - 90 >= seperationAngle)
						{
							flip = true;
						}


						//test section

		/*if{
			(sqrt((roombas[i].getx() - roombas[i+1].getx())^2 + (roombas[i].gety()-roombas[i+1].gety())^2) <= .35)
			vecAngle = atan((roombas[i].gety()-roombas[i+1].gety())/(roombas[i].getx() - roombas[i+1].getx()));
			if (vecAngle <= roombas[i].getTheta() + M_PI_2 && vecAngle >= roombas[i].getTheta() - M_PI_2){
				//flip roomba
			}
		}

					}
					if(abs(ySeperation)<=.35&&abs(xSeperation)<=.35)
						collision = true;
					bool xdir = roombas[i].getxRight();
					bool ydir = roombas[i].getyUp();
					if(collision)
					{
						if(xdir && ydir && xSeperation > 0.0 && ySeperation > 0.0)
							flip = true;
						if(xdir && !ydir && xSeperation > 0.0 && ySeperation < 0.0)
							flip = true;
						if(!xdir && ydir && xSeperation < 0.0 && ySeperation > 0.0)
							flip = true;
						if(!xdir && !ydir && xSeperation < 0.0 && ySeperation < 0.0)
							flip = true;
					}
				}
				if(i == j)
					continue;
				double xSeperation = roombas[j].getx() - roombas[i].getx();
				double ySeperation = roombas[j].gety() - roombas[i].getx();
				if(abs(ySeperation)<=.35&&abs(xSeperation)<=.35)
					collision = true;
				bool xdir = roombas[i].getxRight();
				bool ydir = roombas[i].getyUp();
				if(collision)
				{
					if(xdir && ydir && xSeperation > 0.0 && ySeperation > 0.0)
						flip = true;
					if(xdir && !ydir && xSeperation > 0.0 && ySeperation < 0.0)
						flip = true;
					if(!xdir && ydir && xSeperation < 0.0 && ySeperation > 0.0)
						flip = true;
					if(!xdir && !ydir && xSeperation < 0.0 && ySeperation < 0.0)
						flip = true;
				}
			}
			if(flip)
				roombas[i].setTheta(roombas[i].getTheta()+ 2*M_PI);
		}*/
		for(ObstacleRoomba &r : obstacles)
		{
			r.setTheta(r.getTheta()+.066);
		}
		cout<<"t = "<<t<<" r1 ("<<roombas[0].getx()<<","<<roombas[0].gety()<<") r2 ("<<roombas[1].getx()<<","<<roombas[1].gety()<<")"<<endl;
		for(TargetRoomba &r : roombas)
		{
			r.move();
		}
		for(ObstacleRoomba &r : obstacles)
		{
			r.move();
		}
	}
};