%% Initialise variables
% Timing variables
reps = 10;
time = zeros(1,10);

% Vectors for multiplications
dimension = 100000;
A = 1.5 * ones(1, dimension);
B = 3.5 * ones(1, dimension);

C  = zeros(1, dimension);

% Versions
V = ["Vectorisation", "MATLAB function", "MEX function"];

% Ask which version of the multiplication needs to be run
prompt = 'Press the corresponding button \n 1: Vectorised \n 2: MATLAB Function \n 3: MEX file \n';
version = input(prompt);

%% Run the experiment
for i = 1:reps
    tic;

    for r = 1:1000
        switch V(version)
            case "Vectorisation"
                C = A .* B;
            case "MATLAB function"
                C = multiply_matlab(A, B, dimension);
            case "MEX function"
                C = multiply_mex(A, B, dimension);
        end
    end

   time(i) = toc;
end

mean_time = mean(time);

%% Display results
result = sprintf('On average it took %f seconds using the %s method to multiply the vectors.', mean_time, V(version));
disp(result)


