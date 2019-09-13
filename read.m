#!/usr/bin/octave

clear all;
close all;

%load textfile
data2 = load('saida.txt');

%plot data
x = data2(:,3)
y = data2(:,4)
scatter(x,y );   %,data2(:,3),data2(:,4)); 

printf('Pause. Press any key.\n');
pause;
