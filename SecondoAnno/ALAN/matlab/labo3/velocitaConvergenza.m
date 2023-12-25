% Funzione per il calcolo della velocità di convergenza
function v = velocitaConvergenza(w)
    
    % Tutti gli autovalori vengono resi positivi per poterli ordinare
    w = abs(w);

    % Vengonno riordinati gli autovalori dal maggiore al minore
    w = sort(w, 'descend');
    
    % Viene calcolata la velocità di convergenza
    v = abs(w(2)/w(1)); % ^k
end