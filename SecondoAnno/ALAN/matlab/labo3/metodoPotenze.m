% Funzione per l'esecuzione del metodo delle potenze data la matrice su cui
% applicarlo e il vettore iniziale
function lmbd = metodoPotenze(A, v)
    n = 100;
    lmbd = zeros(n, 1);

    for k = 1:n
        w = A * v;
        v = w/norm(w);
        vT = v';
        lmbd(k) = (vT * w)/(vT * v);
        
    end

end