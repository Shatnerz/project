%Inputs: handle -- vector from connect() command
%        distance -- distance between ultrasonic sensor and object
%Outputs: speed -- speed of sound in m/s
%         error_Speed -- measurement error on speed of sound
%         time -- data of time between trigger and echo

function [speed,error_Speed,avg_Time,error_Time]=sosound(handle,distance)
clear time
n=50; %number of data points

time=[];

for i=1:n;
    time(i)=echo_time(handle);
    pause(.1);
end

avg_Time=mean(time);
error_Time=sqrt(var(time));

speed=2*distance/avg_Time*10000;
error_Speed=2*distance/avg_Time^2*error_Time*10000;
