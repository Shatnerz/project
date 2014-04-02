clear dist
dist=[];

for i=1:50;
    dist(i)=distance(h);
    pause(0.1)
end

avg=mean(dist)
low=min(dist)
high=max(dist)
med=median(dist)
std=sqrt(var(dist))