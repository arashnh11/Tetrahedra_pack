clc
clear all
close all

%X = [1 0 1; 0 0 0; 0 0 0];
%Y = [0 0 0; 1 0 1; 0 0 0];
%Z = [0 1 0; 0 0 0; 1 0 1];
data = load('data.txt');
s = size(data);
col = s(2);
figure(1);
for i = 1: length(data)
    x = data(i, 1:3:s(2));
    y = data(i, 2:3:s(2));
    z = data(i, 3:3:s(2));
    plot3(x,y,z,'*-','MarkerSize',5)
    hold on
end
%mesh(X*0.5, Y*0.5, Z*0.5)



axis equal
axis([-1  2    -1  2    -1  2])

xlabel('x');
ylabel('y');
zlabel('z');
