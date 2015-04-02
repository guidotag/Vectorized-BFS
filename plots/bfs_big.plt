reset	#resetea configuraciones previas

exp_name = "bfs_big"
pr_adj = "0.1 0.25 0.5 0.75 1"
pr_src = "0.01 0.01 0.01 0.01 0.01"
nosch = "010 025 050 075 100" #names without special characters like dots (Latex does not like them)

set terminal epslatex size 12.5cm, 7cm dashed #formato de salida

set style line 1 lc rgb "red" lt 1
set style line 2 lc rgb "blue" lt 2
set style line 3 lc rgb "dark-green" lt 4

set ylabel "TSC"
set xlabel "Cantidad de nodos ($n$)"
#set logscale y

i = 1
input_file = exp_name.'_'.word(pr_adj, i).'_'.word(pr_src, i).'.out'
output_file =exp_name.'_'.word(nosch, i).'.tex'
set output output_file	#archivo de salida
plot input_file using 1:4 with lines ls 1 title '\textsc{BFS}', \
	input_file using 1:5 with lines ls 2 title '\textsc{Vectorized-BFS-Branching}'#, \
	#input_file using 1:6 with lines ls 3 title '\textsc{Vectorized-BFS-No-Branching}'
unset output

i = 2
input_file = exp_name.'_'.word(pr_adj, i).'_'.word(pr_src, i).'.out'
output_file =exp_name.'_'.word(nosch, i).'.tex'
set output output_file	#archivo de salida
plot input_file using 1:4 with lines ls 1 title '\textsc{BFS}', \
	input_file using 1:5 with lines ls 2 title '\textsc{Vectorized-BFS-Branching}'#, \
	#input_file using 1:6 with lines ls 3 title '\textsc{Vectorized-BFS-No-Branching}'
unset output

i = 3
input_file = exp_name.'_'.word(pr_adj, i).'_'.word(pr_src, i).'.out'
output_file =exp_name.'_'.word(nosch, i).'.tex'
set output output_file	#archivo de salida
plot input_file using 1:4 with lines ls 1 title '\textsc{BFS}', \
	input_file using 1:5 with lines ls 2 title '\textsc{Vectorized-BFS-Branching}'#, \
	#input_file using 1:6 with lines ls 3 title '\textsc{Vectorized-BFS-No-Branching}'
unset output

i = 4
input_file = exp_name.'_'.word(pr_adj, i).'_'.word(pr_src, i).'.out'
output_file =exp_name.'_'.word(nosch, i).'.tex'
set output output_file	#archivo de salida
plot input_file using 1:4 with lines ls 1 title '\textsc{BFS}', \
	input_file using 1:5 with lines ls 2 title '\textsc{Vectorized-BFS-Branching}'#, \
	#input_file using 1:6 with lines ls 3 title '\textsc{Vectorized-BFS-No-Branching}'
unset output

i = 5
input_file = exp_name.'_'.word(pr_adj, i).'_'.word(pr_src, i).'.out'
output_file =exp_name.'_'.word(nosch, i).'.tex'
set output output_file	#archivo de salida
plot input_file using 1:4 with lines ls 1 title '\textsc{BFS}', \
	input_file using 1:5 with lines ls 2 title '\textsc{Vectorized-BFS-Branching}'#, \
	#input_file using 1:6 with lines ls 3 title '\textsc{Vectorized-BFS-No-Branching}'
unset output
