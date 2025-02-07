function output  = duty2output(duty, Ts, t)

tRelative = mod(t, Ts);

T1 = Ts * duty;

if(tRelative < T1)
    output = 1;
else
    output = 0;
end

end

