function [output] = SV_Modulation(Valpha, Vbeta, Ts, t)
% Takes Va and Vb as inputs, outpus Signals for the high side gates.
% The low side gates can be obtained by inverting the high side signals.
% The Ts input is the period of the PWM, the t input is the current time

    % First step: determine the angle of the reference
    theta = atan(abs(Vbeta/Valpha));

    if(and(Valpha < 0, Vbeta < 0))
        theta = theta + pi;
    elseif(and(Valpha < 0, Vbeta > 0))
        theta = theta + pi/2;
    elseif(and(Valpha > 0, Vbeta < 0))
        theta = theta + (3/2) * pi;
    end

    
    % Determine which quadrant, since there are 6 quadrants
    % each quadrant is (2 * pi)/6 = pi / 3
    piThird = (pi/3);
    quadrant = mod(theta, piThird);
    
    % Detrmine percentage for left/right vectors
    perc = (theta - piThird * mod)/piThird;
    
    vectors = [0,0,1;0,1,1;0,1,0;1,1,0;1,0,0;1,0,1;0,0,1]; %Add last one equal to first
        
    output = vectors(:,quadrant) * duty2output(perc, Ts, t) + vectors(:,quadrant+1) * duty2output(perc, Ts, t);

end

