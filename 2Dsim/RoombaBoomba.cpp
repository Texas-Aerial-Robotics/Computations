#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include "matplotlibcpp.h"
#include <string>
#include <map>

using namespace std;

std::vector<double> roombax, obstaclex, roombay, obstacley;

class TargetRoomba
{
private:
	double speed = .33;
	double theta;
	double xpos;
	double ypos;
	bool xRight;
	bool yUp;
	int status=0;
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
	void setStatus(int i){

		status=i;
		//0=in play
		//1 = scored
		//-1 = out of bounds
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
	int getStatus()
	{
		return status;
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
		if(t%20 == 0 && t != 0) //rotate 180 every 20 seconds
		{
			for(TargetRoomba &r : roombas)
			{
				r.setTheta(r.getTheta()+M_PI);
			}
		}
		else if(t%5 == 0 && t != 0) //add random trajectory every 5 seconds
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
			for(int j = 0; j<5; j++)
			{		flip=false;
					double xSeperation = obstacles[j].getx() - roombas[i].getx();
					double ySeperation = obstacles[j].gety() - roombas[i].gety();
					double seperationMagnitude = sqrt(pow(xSeperation, 2.0)+ pow(ySeperation, 2.0));
					double seperationAngle = atan2(ySeperation,xSeperation);

					if(seperationMagnitude <= 0.35)
					{
					// {
					// 	if (seperationAngle <= (obstacles[j].getTheta() + 90) && seperationAngle >= (obstacles[j].getTheta()-90))
					// 	{	cout<<"GAY"<<endl;
					// 		flip = false;
					// 	}
					// 	else if (obstacles[j].getTheta() >= -90 && obstacles[j].getTheta() <= 0)
					// 	{
					// 		if (seperationAngle >= obstacles[j].getTheta() - 90 || seperationAngle <= obstacles[j].getTheta() + 90)
					// 		{	cout<<"GAY"<<endl;
					// 			flip = true;
					// 		}
					// 	}
					// 	else if (obstacles[j].getTheta() <= 90 && obstacles[j].getTheta() >= 0)
					// 	{
					// 		if (seperationAngle <= obstacles[j].getTheta()+90 || seperationAngle >= obstacles[j].getTheta() - 90)
					// 		{	cout<<"TRUEE"<<endl;
					// 			flip = true;
					// 		}
					// 	}
					// 	else if (obstacles[j].getTheta() + 90 <= seperationAngle && obstacles[j].getTheta() - 90 >= seperationAngle)
					// 	{	
					// 		cout<<"TRUEEE"<<endl;
					// 		flip = true;
					// 	}
					// }
						if (seperationAngle <= (roombas[i].getTheta()+M_PI/2) && seperationAngle>= (roombas[i].getTheta()-M_PI/2)){

								flip=true;

							}


				
			


					}
				if(flip){
							roombas[i].setTheta(roombas[i].getTheta()+M_PI)	;
							cout<<"COLIDETH"<<endl;				
				}	


			}
		}

		for(int i=0; i<9;i++){
			for(int j=i+1;j<10;j++){

					bool flip=false;
				    double xSeperation = roombas[i].getx() - roombas[j].getx();
					double ySeperation = roombas[i].gety() - roombas[j].gety();
					double seperationMagnitude = sqrt(pow(xSeperation, 2.0)+ pow(ySeperation, 2.0));
					double seperationAngle = atan2(ySeperation,xSeperation);

					if(seperationMagnitude <= 0.35)
					{
						if (seperationAngle <= (roombas[j].getTheta()+M_PI/2) && seperationAngle>= (roombas[j].getTheta()-M_PI/2)){

								flip=true;

							}


					}		if(flip){
							roombas[i].setTheta(roombas[i].getTheta()+M_PI)	;
							cout<<"COLIDETH ONTO EACHOTHER"<<endl;		
							roombas[j].setTheta(roombas[i].getTheta()+M_PI)	;
								}

			}
		}

		



		for(ObstacleRoomba &r : obstacles)
		{
			r.setTheta(r.getTheta()+.066);
		}
		//cout<<"t = "<<t<<" r1 ("<<roombas[0].getx()<<","<<roombas[0].gety()<<") r2 ("<<roombas[1].getx()<<","<<roombas[1].gety()<<")"<<endl;

		for (int i = 0; i < 10; ++i)
		{
			roombax.push_back(roombas[i].getx());
			roombay.push_back(roombas[i].gety());


		}

		for (int i = 0; i < 4; ++i)
		{
			obstaclex.push_back(obstacles[i].getx());
			obstacley.push_back(obstacles[i].gety());
		}

		for(TargetRoomba &r : roombas)
		{	if(r.getStatus()==0){ 
				r.move();
				if(abs(r.getx())<10 && r.gety()>10){
					r.setStatus(1);
					cout<<"ROOMBA SCORED!!!"<<endl;}
				else if(abs(r.getx())>10 || abs(r.gety())>10){
					r.setStatus(-1);
					cout<<"ROOMBA LOST :("<<endl;
				}	

				
			}


		}
		for(ObstacleRoomba &r : obstacles)
		{
			r.move();
		}
	}

	matplotlibcpp::xlim(-10, 10);
	matplotlibcpp::ylim(-10, 10);
	double alpha = 1;

	std::map<std::string, std::string> obstacleKeywords;
	obstacleKeywords["color"] = "blue";
	obstacleKeywords["marker"] = "o";
	obstacleKeywords["linestyle"] = "none";

	std::map<std::string, std::string> roombaKeywords;
	roombaKeywords["color"] = "red";
	roombaKeywords["marker"] = "o";
	roombaKeywords["linestyle"] = "none";

	std::vector<double> stagingx(10);
	std::vector<double> stagingy(10);
	std::vector<double> stagingx2(4);
	std::vector<double> stagingy2(4);
	for (int i = 0; i < 599; i++)
	{
		 if ((i % 10 == 0) && alpha > 0)
		 {
		 	alpha += 0.002;
		 }
		 for(int j=0;j<10;j++){
		 	stagingx[j] = roombax[i*10+j];


		 	stagingy[j] = roombay[i*10+j];

		 	if(j<4){
		 		stagingx2[j] = obstaclex[i*4+j];


		 		stagingy2[j] = obstacley[i*4+j];
		 	}
		 
			 }
			 
			      matplotlibcpp::clf();
			     matplotlibcpp::xlim(-10, 10);
				 matplotlibcpp::ylim(-10, 10);
				 // matplotlibcpp::title('t=%d' i);
			     matplotlibcpp::plot(stagingx, stagingy, roombaKeywords, .2);
			     matplotlibcpp::plot(stagingx2, stagingy2, obstacleKeywords, 0.2);
		 		 matplotlibcpp::draw();
		 		 matplotlibcpp::pause(0.01);

	}
			

	while(1) {
		matplotlibcpp::pause(0.001);
	 }
};
