clc
clear all
close all

X = [1 0 1; 0 0 0; 0 0 0];
Y = [0 0 0; 1 0 1; 0 0 0];
Z = [0 1 0; 0 0 0; 1 0 1];

figure(1)
surf(X,Y,Z)
hold on
%mesh(X*0.5, Y*0.5, Z*0.5)



axis equal
axis([-1  2    -1  2    -1  2])

xlabel('x');
ylabel('y');
zlabel('z');