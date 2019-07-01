#ifndef _GA_H
#define _GA_H

#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <ctime>
#include <functional>
#include <vector>
#include <set>
#include <cstdlib>

using namespace std;

const ulong population_number = 20; 
const ulong times = 100;
const ulong N = 200;

int machine;          //机器数量
int job;              //工件数量
int process;          //任务总数
int chromosome_size;  //染色体长度


const class Probability {        //概率
	public:
		const double cross = 0.95;   //交叉概率
		const double mutation = 0.05;//变异概率
} probability;

class Matrix {              //矩阵
	public:
		int Machine[N][N] = {}; //job process => machine
		int Time[N][N] = {};    //job process => time
		int Process[N][N] = {}; //job machine => process
		Matrix() {
			fill(Machine[0], Machine[0] + N * N, -1);
			fill(Process[0], Process[0] + N * N, -1);
		}
} matrix;

class Gene {     //基因
	public:
		string chromosome = string(static_cast<ulong>(job * machine), '0'); //染色体
		int fitness = 0;                                                    //适应度

		explicit Gene(int fitness) { this->fitness = fitness; };

		Gene() = default;

		Gene(const Gene &other) {
			chromosome = other.chromosome;
			fitness = other.fitness;
		}

		Gene &operator=(const Gene &other) = default;

		bool operator==(const Gene &other) const {
			return chromosome == other.chromosome && fitness == other.fitness;
		}

		bool operator<(const Gene &other) const {
			return chromosome < other.chromosome;
		}
};

vector<Gene> populations;       //种群

class Store {
	public:
		int machineWorkTime[N] = {}; //机器工作时间
		int processIds[N] = {};      //对应任务的工序
		int endTime[N][N] = {};      //job process => endtime
		int startTime[N][N] = {};    //job process => starttime
		Store() = default;

		Store(const Store &other) {
			copy(begin(other.machineWorkTime), end(other.machineWorkTime), begin(machineWorkTime));
			copy(begin(other.processIds), end(other.processIds), begin(processIds));
			copy(other.endTime[0], other.endTime[0] + N * N, endTime[0]);
			copy(other.startTime[0], other.startTime[0] + N * N, startTime[0]);
		}

		Store &operator=(const Store &other) {
			copy(begin(other.machineWorkTime), end(other.machineWorkTime), begin(machineWorkTime));
			copy(begin(other.processIds), end(other.processIds), begin(processIds));
			copy(other.endTime[0], other.endTime[0] + N * N, endTime[0]);
			copy(other.startTime[0], other.startTime[0] + N * N, startTime[0]);
			return *this;
		}
};

/**
 * 产生 start到end的随机整数
 * @param start
 * @param end
 * @return
 */
ulong randint(ulong start, ulong end) {
	return rand() % (end - start + 1) + start;
}

/**
 * 产生 0 到 end的随机整数
 * @param end
 * @return
 */
ulong randint(ulong end) {
	return rand() % (end + 1);
}

/**
 * char => int
 * @param ch
 * @return
 */
int Int(char ch) {
	return ch - '0';
}

/**
 *int => char
 * @param i
 * @return
 */
char Char(int i) {
	return static_cast<char>(i + '0');
}

/**
 * 将vector填充整数
 * @param v
 * @param length
 * @param except
 */
void generateVector(vector<int> &v, int length, int except = -1) {
	for (int i = 0; i < length; i++) {
		if (except != -1 && i == except) continue;
		v.push_back(i);
	}
}

/**
 * 计算适应度
 * @param gene
 * @param store
 */
void calculateFitness(Gene &gene, Store &store) {
	int fulfillTime = 0;
	for (char i : gene.chromosome) {
		int jobId = Int(i) - 1,
			processId = store.processIds[jobId],
			machineId = matrix.Machine[jobId][processId],
			time = matrix.Time[jobId][processId];
			store.processIds[jobId]++;
			store.startTime[jobId][processId] = processId == 0 ? store.machineWorkTime[machineId] : max(store.endTime[jobId][processId - 1],       store.machineWorkTime[machineId]);
			store.machineWorkTime[machineId] = store.startTime[jobId][processId] + time;
			store.endTime[jobId][processId] = store.machineWorkTime[machineId];
			if (store.machineWorkTime[machineId] > fulfillTime) {
				fulfillTime = store.machineWorkTime[machineId];
			}
	}
	gene.fitness = fulfillTime;
}

/**
 * 初始化种群
 * @param genes 
 * @param population 
 */
void initializePopulation(vector<Gene> &genes, int population) {
	set<Gene> gs;
	for (int i = 0; i < population; i++) {
		vector<int> index_list;
		generateVector(index_list, job * machine);
		Gene gene;
		for (int j = 1; j <= job; j++) {
			for (int k = 0; k < machine; k++) {
				ulong index = randint(index_list.size() - 1);
				int value = index_list[index];
				index_list.erase(index_list.begin() + index);
				if (matrix.Process[j - 1][k] != -1)
					gene.chromosome[value] = Char(j);
			}
		}
		remove_if(gene.chromosome.begin(), gene.chromosome.end(), [](char v) -> bool { return v == '0'; });
		gene.chromosome.resize(static_cast<ulong>(chromosome_size));
		Store store;
		calculateFitness(gene, store);
		gs.insert(gene);
	}
	insert_iterator<vector<Gene>> insert_vector(genes, genes.begin());
	copy(gs.begin(), gs.end(), insert_vector);
}

/**
 * 基因突变
 * @param gene 
 * @param n 
 */
void geneticMutation(Gene &gene, int n = 2) {
	vector<int> index_list;
	generateVector(index_list, chromosome_size);
	for (int i = 0; i < n; i++) {
		ulong first = randint(0, index_list.size() - 1);
		index_list.erase(index_list.begin() + first);
		ulong second = randint(0, index_list.size() - 1);
		swap(gene.chromosome[first], gene.chromosome[second]);
	}
	Store store;
	calculateFitness(gene, store);
}

/**
 * 基因交叉
 * @param first 
 * @param second 
 * @return 
 */
pair<Gene, Gene> orderCrossover(Gene &first, Gene &second) {
	function<Gene(Gene &, Gene &)> generateChild = [](Gene &first, Gene &second) -> Gene {
		vector<int> index_list;
		generateVector(index_list, chromosome_size);

		ulong start = randint(0, index_list.size() - 1);
		index_list.erase(index_list.begin() + start);
		ulong end = randint(0, index_list.size() - 1);

		string middle = first.chromosome.substr(start, end - start),
			   t = middle,
			   k = second.chromosome;
		for (char &it : t) {
			for (int i = 0; i < k.size(); i++) {
				if (k[i] == it) {
					k.erase(k.begin() + i);
					break;
				}
			}
		}
		Gene child;
		child.chromosome = k.substr(0, start) + middle + k.substr(start, k.length() - start);
		Store store;
		calculateFitness(child, store);
		return child;
	};
	pair<Gene, Gene> child;
	child.first = generateChild(first, second);
	child.second = generateChild(second, first);
	return child;
}

/**
 * 选择个体
 * @param n 
 * @return 
 */
Gene selectIndividual(int n = 3) {
	vector<int> index_list;
	generateVector(index_list, population_number);
	vector<Gene> simple;
	for (int i = 0; i < n; i++) {
		ulong index = randint(index_list.size() - 1);
		index_list.erase(index_list.begin() + index);
		simple.push_back(populations[index]);
	}
	Gene best_gene(0xffffff);
	for (int i = 1; i < n; i++) {
		if (simple[i].fitness < best_gene.fitness) {
			best_gene = simple[i];
		}
	}
	return best_gene;
}

#endif*/

/*
int main() {
	srand(static_cast<uint>(time(nullptr)));

	chromosome_size = 0;
	cout << "input job and machine:" << endl;
	cin >> job >> machine;
	for (int i = 0; i < job; i++) {
		int p;
		cout << "input job" << i << " process:" << endl;
		cin >> p;
		chromosome_size += p;
		if (process < p) process = p;
		cout << "input machine and time:" << endl;
		for (int j = 0; j < p; j++) {
			int m, t;
			cin >> m >> t;
			matrix.Machine[i][j] = m;
			matrix.Time[i][j] = t;
		}
	}

	for (int i = 0; i < job; i++) {
		for (int j = 0; j < process; j++) {
			if (matrix.Machine[i][j] != -1)
				matrix.Process[i][matrix.Machine[i][j]] = j;
		}
	}

	initializePopulation(populations, population_number);    //初始化种群
	ulong n = times;
	while (n-- > 0) {
		cout << "n = " << n << endl;
		double P = randint(0, 100) / 100.0;
		if (P < probability.mutation) {
			ulong index = randint(populations.size() - 1);
			geneticMutation(populations[index]);
		} else {
			ulong size = populations.size();
			ulong m = size / 4;
			set<Gene> children;
			while (m-- > 0) {
				Gene father = selectIndividual();
				Gene mother = selectIndividual();
				pair<Gene, Gene> child = orderCrossover(father, mother);
				children.insert(child.first);
				children.insert(child.second);
			}
			sort(populations.begin(), populations.end(),
					[](const Gene &a, const Gene &b) -> bool { return a.fitness < b.fitness; });
			populations.resize(size - size / 4);
			for (const auto &it : children) {
				populations.push_back(it);
			}
			sort(populations.begin(), populations.end());
			auto iter = unique(populations.begin(), populations.end());
			populations.resize(static_cast<ulong>(distance(populations.begin(), iter)));
		}
	}

	Gene best_gene(0xffffff);
	for (const auto &it : populations) {
		cout << "chromosome = " << it.chromosome << " " << it.fitness << endl;
		if (best_gene.fitness > it.fitness) {
			best_gene = it;
		}
	}

	Store store;
	cout << "result = " << best_gene.chromosome << " time = " << best_gene.fitness << endl;
	calculateFitness(best_gene, store);
	for (int i = 0; i < machine; i++) {
		cout << "machine" << i << " work time " << store.machineWorkTime[i] << endl;
	}

	for (int j = 0; j < job; j++) {
		for (int k = 0; k < process; k++) {
			if (matrix.Machine[j][k] != -1)
				cout << "job" << j << " process" << k << " machine" << matrix.Machine[j][k] << " start time="
					<< store.startTime[j][k] << " end time=" << store.endTime[j][k] << endl;
		}
	}
	return 0;
}*/
