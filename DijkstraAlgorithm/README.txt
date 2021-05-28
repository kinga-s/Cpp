@Kinga Syta
PL
Język: C++ 20

Algorytm Dijkstry
Program wyyszukujący najkrótsze ścieżki z jednym źródłem dla grafów skierowanych, ważonych z nieujemnymi wagami.
Z linii poleceń wywołujemy: my_program path_to_graph_file starting_vertex ed_v_1 end_v_2 
gdzie path_to_graph_file plik w formacie csv
starting_vertex wierzchołek startowy, dla którego uruchamiamy algorytm Dijkstry
ed_v_1 end_v_2 odległości od starting_vertex
Program zwraca odległości oraz czas swojego wykonania podany w ms.

W rozwiązaniu został zaimplementowany graf w postaci macierzy. Wybrałam tą implementację, ponieważ jest czytelna i łatwa,
lecz przez to czas wykonania jest większy niż byłby dla listy sąsiedztwa. Program wykorzystuje algorytm Dijkstry, by obliczyć
najktótszą ścieżkę pomiędzy wierzchołkiem startowym, a pozostałymi. Jako kolejkę dodałam tu drugi wymiar
dla listy sąsiedztwa. Przechowuje ona dla każdego wierzchołka wartości 0 - jeśli nie został jeszcze odwiedzony(white), 
1 - jeśli znajduje się w kolejce(gray) i 2 jeśli już został usunięty z kolejki(black). Nie jest to najwydajniesze rowiązanie,
ale z pewnością jedno z przyjemniejszych, bardziej przejrzystych i prostszych do zaimplementowania.

Uwaga! Zaimplementowanie grafu jako listy sąsiedztwa, a następnie wykorzystanie sortowania przez kopcowanie zauważalnie przyspieszy pracę programu.
Moim celem jest pokazanie różnych sposobów rozwiązań i implementacji algorytmów grafowych,
w tym konkretnym programie moim celem było pokazanie, że program tak zaimplementowany działa wolno i jest to zabieg celowy.
W pozostałych wybranych programach została użyta zarówno implementacja grafu jako listy sąsiedztwa jak i sortowanie przez kopcowanie.

Złożoność czasowa: O(V^2)
Najwięcej czasu zajmuje utworzenie macierzy sąsiedztwa. Algorytm Dijkstry też zajmuje tu O(V^2).

Złożoność pamięciowa: O(V^2)
Najwięcej pamięci zajmuje stworzenie macierzy sąsiedztwa.
