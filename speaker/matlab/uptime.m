function [ time ] = uptime (handle)
% uptime(handle) returns number of seconds since Arduino rebooted
  sendVector(handle,[3]); % send command to Arduino
  vector = waitVector(handle);
  if vector(1) > 0
    error('Arduino apparently indicated a problem');
  end
  time = 1e-3*(vector(2) + 2^16*vector(3));
end
