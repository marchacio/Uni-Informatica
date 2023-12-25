%%% ESERCIZIO 2 %%%

% Punto a %

%numero stazioni lombarde
n = 11; 

% Costruzione matrice A in base alle ferrovie lombarde
A = zeros(n);

A(1, 2:7) = 1;
A(2, 1) = 1;
A(3, 1) = 1;
A(3, 10) = 1;
A(10, 11) = 1;
A(10, 3) = 1;
A(10, 4) = 1;
A(11, 10) = 1;
A(4, 1) = 1;
A(4, 5) = 1;
A(4, 10) = 1;
A(5, 1) = 1;
A(5, 4) = 1;
A(5, 6) = 1;
A(5, 8) = 1;
A(6, 1) = 1;
A(6, 5) = 1;
A(6, 8) = 1;
A(7, 1) = 1;
A(8, 6) = 1;
A(8, 5) = 1;
A(8, 9) = 1;
A(9, 8) = 1;


% Punto b %
% Creazione matrice D
% sum(A == 1) ritorna un vettore riga, contenente per ogni colonna di A il numero di 1 presenti in questa 
D = diag(sum(A == 1)); 

% Calcolo matrice G 
G = A/D; 

% Autovettori e autovalori di G
[autovettori, autovalori] = eig(G);

% Con la funzione real, prendiamo solo la parte immaginaria dei numeri
% complessi
autovalori = real(autovalori);
autovettori = real(autovettori);

autovettori(:, 1) = autovettori(:, 1)*-1;