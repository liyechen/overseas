#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_SIZE 1000

void output_cell(int state) {
	switch(state) {
		case 0:
			printf(". ");
			break;
		case 1:
			printf("^ ");
			break;
		case 2:
			printf("* ");
			break;
		case 3:
			printf("! ");
			break;
		default:
			printf("  ");
			break;
	}
}

void output_wind(int wind) {
	printf("Wind ");
	switch(wind) {
		case 0:
			printf("NORTH\n");
			break;
		case 1:
			printf("EAST\n");
			break;
		case 2:
			printf("SOUTH\n");
			break;
		case 3:
			printf("WEST\n");
			break;
		default:
			printf("\n");
			break;
	}
}

void output_forest(int forest[MAX_SIZE][MAX_SIZE], int n) {
	int i, j;
	for (i = 0; i < n + 3; i++) {
		for (j = 0; j < n + 3; j++) {
			if (i == 0) {
				if (j > 1 && j < n + 2) {
					int c_i = j + 95;
					char c = c_i; 
					printf("%c ", c);	
				} else {
					printf("  ");
				}
			} else if (i == 1 || i == n + 2) {
				if (j > 0) {
					printf("# ");
				} else {
					printf("  ");
				}
			} else if (i < n + 2) {
				if (j == 0) {
					printf("%i ", i - 2);
				} else if (j == 1 || j == n + 2) {
					printf("# ");
				} else {
					output_cell(forest[i - 2][j - 2]);
				}
			}
		}
		printf("\n");
	}
}

void input_forest(int forest[][MAX_SIZE], int n) {
    int i, j;
    i = 0;
    while (i < n) {
        j = 0;
        while (j < n) {
            scanf("%d", &forest[i][j]);
            j++;
        }
        i++;
    }  
}

void input_wind_info(int wind[MAX_SIZE][2], int wis) {
    int i, j;
    i = 0;
    while (i < wis) {
        j = 0;
        while (j < 2) {
            scanf("%d", &wind[i][j]);
            j++;
        }
        i++;
    }  
}

int get_wind_by_step(int wind[MAX_SIZE][2], int wind_size, int step) {
	int i, j;
	int last_wind = 0;
	for (i = 0; i < wind_size; i++) {
		if (step < wind[i][0]) {
			return last_wind;
		} else {
			last_wind = wind[i][1];
		}
	}
	return last_wind;
}

int tree_in_forest(int forest[MAX_SIZE][MAX_SIZE], int n) {
	int count = 0;
	int i, j;
	for (i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (forest[i][j] != 0) {
				count++;
			}	
		}
	}
	return count;
}

void output_summary(int init_tree_amount, int tree_burned_down) {
	printf("Number of cells containing tree in initial forest = %i\n", init_tree_amount);
	printf("Number of cells that have burned down = %i\n", tree_burned_down);
	float percent = (float)tree_burned_down / (float)init_tree_amount;
	printf("Percentage of forest burned down = %.2f\n", percent * 100);
}

void simulate_step(int forest[MAX_SIZE][MAX_SIZE], int n, int wind_dir, int* burned_down, double lightning) {
	int i, j;
	int next_forest[MAX_SIZE][MAX_SIZE];
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			next_forest[i][j] = forest[i][j];
			switch(forest[i][j]) {
				case 1:
					switch(wind_dir) {
						case 0:
							if (i + 1 < n) {
								if (j - 1 >= 0) {
									if (forest[i + 1][j - 1] == 2) {
										next_forest[i][j] = 2;
									}
								}
								if (forest[i + 1][j] == 2) {
									next_forest[i][j] = 2;
								}
								if (j + 1 < n) {
									if (forest[i + 1][j + 1] == 2) {
										next_forest[i][j] = 2;
									}
								}
							}
							break;
						case 1:
							if (j - 1 >= 0) {
								if (i - 1 >= 0) {
									if (forest[i - 1][j - 1] == 2) {
										next_forest[i][j] = 2;
									}
								}
								if (forest[i][j - 1] == 2) {
									next_forest[i][j] = 2;
								}
								if (i + 1 < n) {
									if (forest[i + 1][j - 1] == 2) {
										next_forest[i][j] = 2;
									}
								}
							}
							break;
						case 2:
							if (i - 1 >= 0) {
								if (j - 1 >= 0) {
									if (forest[i - 1][j - 1] == 2) {
										next_forest[i][j] = 2;
									}
								}
								if (forest[i - 1][j] == 2) {
									next_forest[i][j] = 2;
								}
								if (j + 1 < n) {
									if (forest[i - 1][j + 1] == 2) {
										next_forest[i][j] = 2;
									}
								}
							}
							break;
						case 3:
							if (j + 1 < n) {
								if (i - 1 >= 0) {
									if (forest[i - 1][j + 1] == 2) {
										next_forest[i][j] = 2;
									}
								}
								if (forest[i][j + 1] == 2) {
									next_forest[i][j] = 2;
								}
								if (i + 1 < n) {
									if (forest[i + 1][j + 1] == 2) {
										next_forest[i][j] = 2;
									}
								}
							}
							break;
						default:
							break;
					}	
					break;
				case 2:
					*burned_down = *burned_down + 1;
					next_forest[i][j] = 0;
					break;
				case 3:
					next_forest[i][j] = 2;
					break;
				default:
					break;
			}
		}
	}
	int rand_value = rand();
	if (rand_value < lightning * RAND_MAX) {
		int x = rand() % (n * n);
		int rand_i = (x - x % n) / n;
		int rand_j = x % n;
		if (next_forest[rand_i][rand_j] == 1) {
			next_forest[rand_i][rand_j] = 3;
		}
	}
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			forest[i][j] = next_forest[i][j];
		}
	}
}

int main(void) {
	char ch;
	int t = 0, n; 
	int wis, wdi, li;
	int forest[MAX_SIZE][MAX_SIZE];
	int wind[MAX_SIZE][2];
	double lightning;
	int random_seed;

	int can_continue = 1;

	printf("Enter t: ");
 
	while((ch = getchar()) != '\n') {
		if (isdigit(ch)) t = t * 10 + ch - 48;
		else can_continue = 0;
	}

    if (t < 0 || t > 1000 || can_continue == 0)
    {
        printf("Incorrect Input: t must be 0..1000\n"); 
        return EXIT_FAILURE;
    } else {
        printf("Enter n: ");
        scanf("%d", &n);
        if (n < 3 || n > 25)
        {
            printf("Incorrect Input: n must be 3..25\n");
            return EXIT_FAILURE;
        }
    }

    printf("Enter %d by %d forset:\n", n, n);

    input_forest(forest, n);
	int init_tree_amount = tree_in_forest(forest, n);

    printf("Enter wind information size: ");

    scanf("%d", &wis);

    printf("Enter wind direction information:\n");

    input_wind_info(wind, wis);

	printf("Enter lightning information:\n");
	scanf("%lf", &lightning);
	scanf("%i", &random_seed);

	srand(random_seed);

	int step;
	int burned_down = 0;
	printf("\n");
	for (step = 0; step <= t; step++) {
		printf("Time step: %i: ", step);
		int wind_dir = get_wind_by_step(wind, wis, step);
		output_wind(wind_dir);
		output_forest(forest, n);
		if (step < t) {
			simulate_step(forest, n, wind_dir, &burned_down, lightning);
		}
		printf("\n");
	}

	output_summary(init_tree_amount, burned_down);

	return 0;
}

