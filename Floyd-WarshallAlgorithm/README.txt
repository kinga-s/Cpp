@Kinga Syta
PL
Język: C++ 20

Algorytm Floyda-Warshalla

Z linii poleceń wywołujemy: my_program path_to_graph_file 'starting_vertex,ending_vertex' 'starting_vertex,ending_vertex'
gdzie path_to_graph_file plik w formacie csv
'starting_vertex,ending_vertex' wierzchołki dla których poszukujemy najkrótszej ścieżki

Program odnajduje najkrótsze ścieżki między wszystkimi wierzchołkami w skierowanym grafie ważonym dzięki algorytmowi Floyda-Warshalla.
Dopuszczalne są wagi ujemne, ale zakłada się brak cyklów z ujemną wagą.
Program dodatkowo wypisuje informacje o cyklu ujemnym (czy jest i wypisuje ten cykl).
Cykl ujemny jest gdy wartość jakiegoś wierzchołka do siebie samego jest mniejsza od 0.
Program również wypisuje macierz poprzedników(jeśli nie ma poprzedników to wartość -1).

Złożoność czasowa: O(V^3)
Program jest zdominowany przez algorytm Floyda-Warshalla.

Złożoność pamięciowa: O(V^2)
Najwięcej pamięci zajmuje macierz odległość i macierz poprzedników.

Plik testowy z grafem:
100.csv
