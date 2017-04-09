function [intersect_1,intersect_2] = CircIntersect(A,B,a,b)
%A - center of the first circle
%B = center of the second circle
%a = radius of the SECOND circle
%b = radius of the FIRST circle
c = norm(A-B); %# distance between circles
c
cosAlpha = (b^2+c^2-a^2)/(2*b*c);
cosAlpha 
u_AB = (B - A)/c; % unit vector from first to second center
u_AB
pu_AB = [u_AB(2), -u_AB(1)]; % perpendicular vector to unit vector
pu_AB
% use the cosine of alpha to calculate the length of the
% vector along and perpendicular to AB that leads to the
% intersection point
intersect_1 = A + u_AB * (b*cosAlpha) + pu_AB * (b*sqrt(1-cosAlpha^2));
intersect_2 = A + u_AB * (b*cosAlpha) - pu_AB * (b*sqrt(1-cosAlpha^2));