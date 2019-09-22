#!/usr/bin/octave

clear all;
close all;

%load textfile
data2 = load('saida.txt');

%plot data
x = data2(:,1);
y = data2(:,2);
z = data2(:,3);
w = data2(:,4);
a = data2(:,5);
b = data2(:,6);
c = data2(:,7);
d = data2(:,8);
e = data2(:,9);
f = data2(:,10);
g = data2(:,11);
h = data2(:,12);
%scatter(x,y)
plot(x,y,';ship 1;',z,w,';ship 2;',a,b,';projectile 1;',c,d,';projectile 2;',e,f,';projectile 3;',g,h,';projectile 4;');
hold on;
scatter(0,0,'r');
printf('Pause. Press any key.\n');
pause;
