% Funzione per l'esecuzione del metodo delle potenze inverse data la matrice su cui
% applicarlo, il vettore iniziale e il valore dello shift
function lmbd  = metodoPotenzeInv(A, v, p)
    n = 100;
    lmbd = zeros(n, 1);

    B = A - (p*eye(size(A)));

    for k = 1:n
        w = linsolve(B, v);

        vT = v';
        mu_k = (vT * w)/(vT * v);  
        lmbd(k) = p + 1/mu_k;

        v = w/norm(w); 
    end
end