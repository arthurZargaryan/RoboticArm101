function [theta0, theta1, theta2, theta3] = ikine4( x, y, z) %implementing a trigonometric appraoch, thinking much about transfromation matrices and so on....
l0 = 6;
l1 = 6.7;
l2 = 5.7;
l3 = 3.4;

%---------Calculating theta0, base angle of manipulator--------------------
theta0 = atan2(y, x);

%---------Calculating the position of the coordinates of frame that holds the tool----------

p0 = [0, 0]; %frame 0 origin
p1 = [0, l0]; %frame 1 origin

%--------Frame 3 origin ---------------------------------------------------
w0 = sqrt(x^2 + y ^2)-l3; %length compnent of the cooridnate for frame 3
p3 = [w0, z]; %coordinate 3

%--------calculating coordinate 2------------------------------------------

%--------------------------------------------- (note that if values below
%become imaginary then the circles do not intersect)
if isequal(p3, p1) 
    p2 = [0, l2];
else
    [p2d, p2u] = CircIntersect(p1, p3, l1, l2); %the robot arm can always assume 2 positions for p2, upper p2u and lower p2l
    if p2u(2)>p2d(2)
        p2 = p2u;
    else
        p2 = p2d;
    end
end

%--------Calculating theta1-------------------------------------------------
p2adj = [p2(1), p2(2)-l0]; %adjusting the frame of reference from frame0 to frame 1
theta1 = atan2(p2adj(1), p2adj(2));

%--------Calculating theta2------------------------------------------------
p3adj = p3-p2; %%adjusting the frame of reference from frame0 to frame 2
theta2 = atan2(p3adj(2), p3adj(1)) - theta1 ; %you have to adjust for the existing rotation in the reference frame of 2, notice we use mod: because of special conditions need to extract the component relative to 90deg (straight vertical line from base)
%--------calculating theta3------------------------------------------------


%p4adj is always [1. 0], hence atan2 = 0

theta3 = -theta1 - theta2;
end

