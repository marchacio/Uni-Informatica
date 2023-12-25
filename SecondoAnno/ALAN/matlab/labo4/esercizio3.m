%%% ESERCIZIO 3 %%%

% Numero di matricola del primo componente del gruppo: ANNA DELLEPIANE 5565836 
d1 = 3;
d0 = 6;

% Creazione matrice A con i parametri specificati prima e y
A = creaMatrice(d0, d1);
y = sin(A(:, 2));

% Primo punto
% Decomposizione ai valori singolari
[svd_sinistra_A, svd_A, svd_destra_A] = svd(A);

% Inizializzazione di c
c_svd = zeros(3, 1);

% Calcolo di c tramite i valori ricavati sopra
for i = 1:3
    c_svd = c_svd + ((svd_sinistra_A(:, i)'*y)/svd_A(i,i))*svd_destra_A(:, i);
end

% Secondo punto
% Decomposizione QR
[Q, R] = qr(A);

% Calcolo di c tramite i valori ricavati sopra
c_qr = R\(Q'*y);


% Terzo punto
% A trasposta
AT = A';

% Calcolo di c tramite la risoluzione del sistema lineare AT*A*c = AT*y
c_eq = linsolve(AT*A, AT*y);


% Quarto punto
% Calcolo di c tramite l'operatore \
c = A\y;