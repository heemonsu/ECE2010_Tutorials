function output = multiply_matlab(vector_1, vector_2, N)
    %TODO Error handling for mismatched dimensions

    output = zeros(1, N);

    for i = 1:N
        output(i) = vector_1(i) * vector_2(i);
    end

end
