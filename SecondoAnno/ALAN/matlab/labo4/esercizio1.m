%%% ESERCIZIO 1 %%%

% Numero di matricola del primo componente del gruppo: ANNA DELLEPIANE 5565836 
d1 = 3;
d0 = 6;

% Creazione matrice A con i parametri specificati prima e trasposta
A = creaMatrice(d0, d1);
AT = A';


% Primo punto
% Decomposizione ai valori singolari di A e AT
[svd_sinistra_A, svd_A, svd_destra_A] = svd(A);
[svd_sinistra_AT, svd_AT, svd_destra_AT] = svd(AT);


% Secondo punto
% Autovalori di A * AT 
AAT_eig = eig(A * AT);

% Autovalori di AT * A
ATA_eig = eig(AT * A);


% Terzo punto
% Immagine di A e AT
immagine_A = orth(A);
immagine_AT = orth(AT);


% Quarto punto
% Nucleo di A e AT
nucleo_A = null(A);
nucleo_AT = null(AT);