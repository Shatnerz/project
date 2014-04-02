function [ cm_distance ] = distance (handle)
% set_pwm(handle,pin,value) returns time between trigger and echo
  %sendVector(handle,[5]); % send command to Arduino
  %vector = waitVector(handle);
  %if vector(1) > 0
  %  error('Arduino apparently indicated a problem');
  %end
  %cm_distance = vector(2);
  t = echo_time(handle);
  %disp(t);
  speed = 343*10^-6;
  cm_distance = t*speed/2*100;
end