%%% ESERCIZIO 3 %%%

A = [1 -1 2;-2 0 5; 6 -3 6];

% Punto a %
v1 = [1; 1; 1];
v2 = [3; 10; 4];

% Calcolo autovalori di A
autoVal_A = eig(A);

% Viene la chiamata la funzione metodoPotenze per l'esecuzione del metodo delle 
% potenze usando A e v1 
lmbd1 = metodoPotenze(A, v1);

% Viene la chiamata la funzione metodoPotenze per l'esecuzione del metodo delle 
% potenze usando A e v2 
lmbd2 = metodoPotenze(A, v2);


% Punto b %
% autovalore di massimo modulo
p = 6;

% Viene la chiamata la funzione metodoPotenzeInv per l'esecuzione del metodo
% delle potenze inverso sulla matrice A usando come vettore iniziale v1 e
% come valore dello shift 6
lmbd3 = metodoPotenzeInv(A, v1, p);

% Viene la chiamata la funzione metodoPotenze per l'esecuzione del metodo delle potenze 
% inverso sulla matrice A usando come vettore iniziale v2 e
% come valore dello shift 6
lmbd4 = metodoPotenzeInv(A, v2, p);

% Calcolo velocità di convergenza %
autoVal_B = zeros(size(A));

for i = 1:size(A)
    autoVal_B(i) = 1/(autoVal_A(i)-p);
end

% Calcolo velocità di convergenza del metodo delle potenze
v_powMethod = velocitaConvergenza(autoVal_A);

% Calcolo velocità di convergenza del metodo delle potenze inverso
v_invPowMethod = velocitaConvergenza(autoVal_B);
