num_nodes=1000
pr_adj=0.42
pr_src=0.01
output_file=bfs.out

make clean
make
./bin/bfs -f $output_file $num_nodes $pr_adj $pr_src
