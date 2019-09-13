#!/usr/bin/octave

clear all;
close all;

%load textfile
data2 = load('saida.txt');

%plot data
plot(data2(:,3),data2(:,4)  );   %,data2(:,3),data2(:,4)); 

printf('Pause. Press any key.\n');
pause;
