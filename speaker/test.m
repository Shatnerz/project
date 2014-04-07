analogFrequency = 400;
volume=0.5;
pin = 6;

%determine frequency
c = 0.0184;
d=0.0089;
digitalFrequency = (((1/analogFrequency)-c)./d);

length = digitalFrequency; %test-this is determined from freq
%x is the range; y is the function
x = 0:(2*pi)/(length-1):2*pi;
y=[];

y = sin(x+1)*volume*255;


set_pwm(h, pin, y);
%sendVector(handle,[1 pin value]);

%pause(1) %pause 1 sec
