iterations = 16000000;
reps = 10;
sum = 0.0;
time = zeros(1,10);


for i = 1:reps
    tic;

    for r = 1:1000
        for c = 1:iterations
            sum = sum + c * 3.14159;
        end
    end

   time(i) = toc;
end

mean_time = mean(time)
