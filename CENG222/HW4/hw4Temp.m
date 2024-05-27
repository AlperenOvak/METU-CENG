N = 4148;
lambdaA = 60;  % number of automobiles
lambdaT = 12;  % number of trucks

TotalWeight = zeros(1, N); % a vector that keeps the total weight for each Monte Carlo run
for k = 1:N;
  % first generate the number of passed vehicles for each type from Poisson
  numA = poissrnd(lambdaA);
  numT = poissrnd(lambdaT);

  % number of automobiles
  U = rand;

  % number of trucks
  U = rand;

	weight = 0; % total weight of vehicles for this run

  % calculate the total weight of automobiles
  weightA = sum(gamrnd(120, 10, 1, numA));

  % calculate the total weight of trucks
  weightT = sum(gamrnd(14, 1000, 1, numT));

  TotalWeight(k) = weightA + weightT;


end;

p_est = sum(TotalWeight > 250000) / N;
expectedWeight = mean(TotalWeight);
stdWeight = std(TotalWeight);

fprintf('Estimated probability = %f\n',p_est);
fprintf('Expected weight = %f\n',expectedWeight);
fprintf('Standard deviation = %f\n',stdWeight);
