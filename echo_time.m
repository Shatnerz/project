function [ uS_time ] = echo_time (handle)
% set_pwm(handle,pin,value) returns time between trigger and echo
  sendVector(handle,[4]); % send command to Arduino
  vector = waitVector(handle);
  if vector(1) > 0
    error('Arduino apparently indicated a problem');
  end
  uS_time = vector(2);
end