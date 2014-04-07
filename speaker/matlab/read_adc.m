function [ value ] = read_adc (handle,pin)
% read_adc(handle,pin) Reads ADC on pin
% handle must be vector returned by connect()
% Valid pins are 0...5
% returns a value 0...1023 mapping to 0...5V
  sendVector(handle,[2 pin]); % send command to Arduino
  vector = waitVector(handle);
  if vector(1) > 0
    error('Arduino apparently indicated a problem');
  end
  value = vector(2);
end
