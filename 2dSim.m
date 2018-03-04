%the purpose of this script is to calculate the robots positions overtime
% last modified 5/18/2016 2:48pm by Eric Johnson
clc; clear all
RT = 5; %radius for troll bots
t = 0; %time variable
h = .5; %step size for time 
v = .33; %m/s
rVector =0;% distance travled
direction = -1*ones(1,10); % simulates 180 turns
R=1; %starting radius for normal bots
objective = 0; %logical variable that shows if the quad copter has an objective
xquad = 0; %starting x position for quad
yquad = 10; %starting y position for quad
botsInGame = ones(1,10);

%loops 10 times
%   the body of the for loop set the intial postiotions of the bots
dtheta0 = 2*pi / 10;
for i=1:10
    x0Bot(i) = R*cos(dtheta0*i);
    y0Bot(i) = R*sin(dtheta0*i);
    yBots(1,i) =y0Bot(i);
    xBots(1,i) =x0Bot(i);
    thetaBot(i) = dtheta0*i;
end

% loops at h interval to ten mins
%   body of loop calculates the positions of bots
for t=0:h:600
    %decide what bot to fly to
    if objective == 0
        %calculate which bot to fly to
        
    end
    %testa if the time is a multiple of 20
    %    if true the directions of the bots are reversed 
    if mod(t,20) == 0
        disp('time')
        direction = direction * -1;
    end
    %tests if time is a multiple of time
    %   if true noise is added to the trjectory 
    if mod(t,5) == 0
        disp('rng');
        %loops 10times
        %   adds noise to the angle of the bot's trajectory 
        for i=1:10
           thetaBot(i) = thetaBot(i) + (randi([-20,20])*(pi/180)); 
        end
    end
    %troll bots positions
    theta = (v*t)/RT;
    theta0 = (2*pi/4);
    for n=1:4
        theta = -(v*t)/RT;
        theta0 = (2*pi/4);
        yt1((1/h)*t + 2,n) = RT*sin(theta + theta0*n);
        xt1((1/h)*t + 2,n) = RT*cos(theta+ theta0*n);
    end
    
    %loops ten times 
    %   body of loop calculates the position for the ten bots at the
    %   specific t value
    rVector = v*h ;
    for k=1:10
        %tests if bot is still in the game
        %   if true the new position is calculated
        if botsInGame(k) == 1
        yBots((1/h)*t + 2,k) = direction(k)*rVector*sin(thetaBot(k)) + yBots((1/h)*t+1,k);
        xBots((1/h)*t + 2,k) = direction(k)*rVector*cos(thetaBot(k)) + xBots((1/h)*t+1,k);
        end
        %if bot is no longer in the arena the bots are given a postiton
        %   outside the arena
        if botsInGame(k) == 0
            yBots((1/h)*t + 2,k) = 100;
            xBots((1/h)*t + 2,k) = 100;
        end
    end
    %loops 10 times for the 10 bots
    %   body of the loop decides if the bot has gone out of bounds
    for k=1:10
        %tests if the position has gone out of the domain of the arena
        %   if true the logical variable is set to false
        if abs(yBots((1/h)*t + 2,k)) >= 10 || abs(xBots((1/h)*t + 2,k)) > 10
            botsInGame(k) = 0;
        end
    end
    
    %loops 4 time sfor the 4 troll bots
    %   the body of the loop calculates the distance between the bots and
    %   the obstical troll bots
    for ii=1:4
        %loops ten for ten bots
        %   body of the loop cheks for collisions between bots
        for i=1:10
            deltaRy(i) = yBots((1/h)*t + 2, i)-yt1((1/h)*t + 1,ii);
            deltaRx(i) = xBots((1/h)*t + 2, i)-xt1((1/h)*t + 1,ii);
            collision(i) = sqrt((deltaRy(i)^2) + (deltaRx(i)^2));
            if collision(i) < .68
                direction(i) = direction(i) * -1;
                disp('collision')
                t
                i
                ii
            end
        end
    end
    
    %%% bot to bot needs algo to account for direction
    
    %check for bot to bot collisions 
    %loops ten times to incriment the 10 bors
    %   body of loop calculates the distance between the 10 bots
    for ii=1:10
        %loops ten times to incriment the 10 bors
        %   body of loop calculates the distance between the 10 bots
        for i=1:10
            if ii~=i
                deltaRy(i) = yBots((1/h)*t + 2, i)-yBots((1/h)*t + 2,ii);
                deltaRx(i) = xBots((1/h)*t + 2, i)-xBots((1/h)*t + 2,ii);
            end
            if collision(i) < .68
                direction(i) = direction(i) * -1;
                disp('collision')
            end
        end
    end
    
end


%plot
figure(1)
axis([-10,10,-10,10,]);
hold on
i=0;
strTime = num2str(i*h);
 a=annotation('textbox','String',strTime,'FitBoxToText','on');
for i=1:length(xt1)
    for k=1:4
        plot(xt1(i,k),yt1(i,k),'ro','markersize', 6) 
    end
    for n=1:10
        plot(xBots(i,n),yBots(i,n),'bo','markersize', 6)
    end
    strTime = num2str((i*h)-1);
    a.String = strTime;
    hold on
    drawnow
    cla
end
hold off
