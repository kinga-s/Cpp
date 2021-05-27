@Kinga Syta
PL
Język: C++ 20

Sortowanie topologiczne grafu
Program implementujący algorytm DFS w celu posortowania topologicznego zadanego grafu.
Z linii poleceń wywołujemy: my_program path_to_graph_file 
gdzie path_to_graph_file plik w formacie csv
Program zwraca porządek zwrócony przez sortowanie topologicznege.

Proponowany zestaw danych testowych: graf składający się z 20 wierzchołków. Aby zastosować sortowanie topologiczne
graf nie może posiać cykli. Zestaw danych testowych ich nie posiada. 

W rozwiązaniu zaimplementowałam algorytm dfs, który przeszukuje wgłąb wierzchołki. W strukturze Vertex każdy
wierzchołek ma zapisywaną informację o jego poprzednim rodzicu, czasie wejścia i wyjścia, przez co ten sam
wierzchołek nie zostanie odwiedzony dwukrotnie. Na początku zostaje utworzona odwrócona lista sąsiedztwa grafu, 
która będzie nam potrzebna, by sprawdzać, czy nasz wierzchołek ma rodzica, czy już sam został rodzicem, a także tablica
mówiąca które wierzchołki w naszym grafie na wejściu już nie mają żadnego rodzica.

Złożoność czasowa: O(V+E)

Złożoność pamięciowa: O(V+E)
