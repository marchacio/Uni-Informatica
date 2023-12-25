%%% ESERCIZIO 2 %%%

% Dimensione massima della matrice
N = 10;

% Inizializzazione vettori finali, contenenti i dati ricavati in ogni iterazione
maxs = zeros(N-1, 1);
mins = zeros(N-1, 1);
condsB = zeros(N-1, 1);

% n sarà al massimo N, partendo da un minimo di 2
for n = 2:N
    % Inizializzazione di B come matrice identità di dimensione nxn
    B = eye(n);
    
    for i = 1:n
        for j = i+1:n
            B(i,j) = -1;
        end
    end
    
    % Primo punto 
    % Valori singolari di B
    valoriSingolari = svd(B);
    
    % Secondo punto 
    % Valore singolare massimo di B
    maxs(n-1) = max(valoriSingolari);
    
    % Valore singolare minimo di B
    mins(n-1) = min(valoriSingolari);
    
    % Condizionamento di B
    condsB(n-1) = cond(B);

    % Terzo punto
    % Il valore B(n, 1) viene perturbato di una quantità pari a -2^(2-n)
    B(n,1) = B(n,1) + (-2^(2-n));
    
    % Autovalori di B (solamente la parte reale (no complessa) grazie alla funzione real)
    autovalori_B = real(eig(B));
end