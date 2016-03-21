x = [0 0.05 0.2 0.4 0.6 0.8 1]; 
y = [1 0.95 0.6 0.2 0.04 0.02 0];
p = polyfit(x,y,5)
x2 = 0:.05:1;
y2 = polyval(p,x2);
plot(x,y,'o',x2,y2)
grid on