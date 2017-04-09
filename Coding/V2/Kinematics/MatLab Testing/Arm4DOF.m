clearvars
clear all
clear variables

startup_rvc

%Setting up Arm
%--------------------------------------------------
L(1) = Link([0 6 0 pi/2]);
%L(1).qlim = [-3.4 2.104];

L(2) = Link([pi/2 0 6.7 0]);
%L(2).qlim = [-1.952 -1.190];

%L(3) = Link([0 0 0 pi/2]);
%L(3).qlim = [-0.8  1.667];

L(3) = Link([-pi/2 0 5.7 0 ]);
%L(4).qlim = [-2.792 2.786];

L(4) = Link([pi/2 0 0 pi/2]);
%L(5).qlim = [-2.092 2.201];

set(gca,'Ydir','reverse')


R = SerialLink(L, 'name', '4 DOF Test'); % joing arm links
R.tool = transl(3.4, 0, 0); % adding tool at the end of the arm

%---------------------------------------------

%set(gca,'Ydir','reverse');
[theta0, theta1, theta2, theta3] = ikine4(10, 7, 8)
%R.plot([pi, pi/2, 0, pi/4])
R.plot([theta0, theta1, theta2, theta3])
%R.plot([theta0-pi/2, theta1+pi/2, theta2, theta3])
%offsets, theta0 -pi/2,  theta1 +pi/2, theta2 0, theta3 0
R.getpos()



