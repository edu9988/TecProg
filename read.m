#!/usr/bin/octave

clear all;
close all;

%load textfile
data2 = load('saida.txt');

%plot data
x = data2(:,1)
y = data2(:,2)
z = data2(:,3);
w = data2(:,4);
%scatter(x,y)
plot(x,y,';ship 1;',z,w,';ship 2;');
hold on;
scatter(0,0);
printf('Pause. Press any key.\n');
pause;
