% Funzione che crea la matrice A dando in input i due valori per il calcolo di m 
function A = creaMatrice(d0, d1)
    m = 10*(d0 + 1) + d1;
    
    A = ones(m,3);
    
    for i = 1:m
        A(i, 2) = i/m;
        A(i, 3) = (i/m)^2;
    end