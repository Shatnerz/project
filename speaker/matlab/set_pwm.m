function [ ] = set_pwm (handle,pin,value)
% set_pwm(handle,pin,value) Sets PWM value on a pin.
% Valid pins are 3,5,6,9,10,11, value should be in range 0...255
  sendVector(handle,[1 pin value]); % send command to Arduino
  vector = waitVector(handle);
  if vector[1] > 0
    error('Arduino apparently indicated a problem');
  end
end

