exp_name=bfs_small
num_nodes=(100 200 300 400 500 600 700 800 900 1000)
pr_adj=(0.01 0.25 0.5 0.75 0.9)
pr_src=(0.01 0.01 0.01 0.01 0.01)

cd ..
cd ..
cd project
make clean
make

for p in {0..4}
do
	output_file=${exp_name}_${pr_adj[p]}_${pr_src[p]}.out
	for n in {0..9}
	do
		./bin/bfs -f $output_file ${num_nodes[n]} ${pr_adj[p]} ${pr_src[p]}
	done
	cp output/$output_file ../experimentos/$exp_name
	rm output/$output_file
done
