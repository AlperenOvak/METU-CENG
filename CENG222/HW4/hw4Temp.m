  N = 4148;
  lambdaA = 60;  % number of automobiles
  lambdaT = 8;  % number of trucks

  TotalWeight = zeros(1, N); % vector for Monte Carlo
  for k = 1:N;
    % generate # of vehicles for Poisson
    numA = 0;
    numT = 0;


    % number of automobiles
    F = exp(- lambdaA);
    U = rand;
    while(U>=F)
      numA = numA +1;
      F = F + exp(-lambdaA) * lambdaA^numA/gamma(numA+1);
    end;

    % number of trucks
    F = exp(- lambdaT);
    U = rand;
    while(U>=F)
      numT = numT +1;
      F = F + exp(-lambdaT)*lambdaT^numT/gamma(numT+1);
    end;

    weight = 0; % total weight of vehicles for this run

    % calculate the total weight of automobiles
    % weightA = sum(gamrnd(120, 10, 1, numA));

    weightA = 0;
    for i = 1:numA
      weightA = weightA + (-(log(rand(120,1)) * 10));
    end

    % calculate the total weight of trucks
    % weightT = sum(gamrnd(14, 1000, 1, numT));

    weightT = 0;
    for i = 1:numT
      weightT = weightT + (-(log(rand(14,1)) * 1000));
    end

    TotalWeight(k) = sum(weightA) + sum(weightT);

  end;

  p_est = mean(TotalWeight > 250000);
  expectedWeight = mean(TotalWeight);
  stdWeight = std(TotalWeight);

  fprintf('Estimated probability = %f\n',p_est);
  fprintf('Expected weight = %f\n',expectedWeight);
  fprintf('Standard deviation = %f\n',stdWeight);
