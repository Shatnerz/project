function [ actualPeriod ] = set_blink (handle,period)
% set_blink(handle,period) Sets period of blinking LED
% handle is from connect()
% period is in seconds
% returns actual period

  sendVector(handle,[4 1000*period]);
  vector = waitVector(handle);
  if vector(1) > 0
    error('Arduino apparently indicated a problem');
  end
  actualPeriod = 1e-3*vector(2);
end

