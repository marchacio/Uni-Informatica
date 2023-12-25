%%% ESERCIZIO 1 %%%

% Numero di matricola dell'ultimo componente del gruppo: MARCO ZORATTI, 5562866
d1 = 6;
d0 = 6;

n = 10*(d1 + 1) + d0;

% Creazione matrice A
A = diag(ones(1, n - 1), 1) + eye(n);

% Creazione matrice E
E = zeros(n);
E(n,1) = 2^(-n);

% Creazione matrice B
B = A + E;


% Punto a %

% Autovalori di A
autovalori_A = eig(A);

% Autovalori di B
autovalori_B = eig(B); 

% Errore relativo in input
errIn_a = norm(B - A)/norm(A);

% Errore relativo in output
errOut_a = norm(autovalori_B - autovalori_A)/norm(autovalori_A);


% Punto b %

% Creazione di AT * A
ATA = A' * A;

% Autovalori di ATA
autovalori_ATA = eig(ATA);

% Creazione di BT * B
BTB = B' * B;

% Autovalori di BTB
autovalori_BTB = eig(BTB); 

% Errore relativo in input
errIn_b = norm(BTB - ATA)/norm(ATA);

% Errore relativo in output
errOut_b = norm(autovalori_BTB - autovalori_ATA)/norm(autovalori_ATA);