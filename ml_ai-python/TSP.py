from random import randint

INT_MAX = 2147483647

class Individual:
    def __init__(self) -> None:
        self.gnome = ""
        self.fitness = 0

    def __lt__(self, other):
        return self.fitness < other.fitness

    def __gt__(self, other):
        return self.fitness > other.fitness

def rand_num(start, end):
    return randint(start, end - 1)

def repeat(s, ch):
    return ch in s

def mutated_gene(gnome, num_cities):
    gnome = list(gnome)
    while True:
        r = rand_num(1, num_cities)
        r1 = rand_num(1, num_cities)
        if r1 != r:
            gnome[r], gnome[r1] = gnome[r1], gnome[r]
            break
    return ''.join(gnome)

def create_gnome(num_cities):
    gnome = "0"
    while True:
        if len(gnome) == num_cities:
            gnome += gnome[0]
            break
        temp = rand_num(1, num_cities)
        if not repeat(gnome, chr(temp + 48)):
            gnome += chr(temp + 48)
    return gnome

def cal_fitness(gnome, mp):
    f = 0
    for i in range(len(gnome) - 1):
        if mp[ord(gnome[i]) - 48][ord(gnome[i + 1]) - 48] == INT_MAX:
            return INT_MAX
        f += mp[ord(gnome[i]) - 48][ord(gnome[i + 1]) - 48]
    return f

def cooldown(temp):
    return (90 * temp) / 100

def TSP():
    num_cities = int(input("Enter the number of cities: "))
    print("Enter the distance matrix (use 0 for self-loops, large values for no connections):")
    mp = []
    for i in range(num_cities):
        row = list(map(int, input(f"Row {i + 1}: ").split()))
        mp.append(row)

    population_size = int(input("Enter the population size: "))
    max_generations = int(input("Enter the maximum number of generations: "))

    gen = 1
    population = []

    for _ in range(population_size):
        temp = Individual()
        temp.gnome = create_gnome(num_cities)
        temp.fitness = cal_fitness(temp.gnome, mp)
        population.append(temp)

    print("\nInitial population:")
    print("GNOME     FITNESS VALUE")
    for ind in population:
        print(ind.gnome, ind.fitness)

    temperature = 10000
    while temperature > 1000 and gen <= max_generations:
        population.sort()
        print(f"\nGeneration {gen}, Current Temperature: {temperature:.2f}")
        new_population = []

        for i in range(population_size):
            p1 = population[i]

            while True:
                new_g = mutated_gene(p1.gnome, num_cities)
                new_gnome = Individual()
                new_gnome.gnome = new_g
                new_gnome.fitness = cal_fitness(new_gnome.gnome, mp)

                if new_gnome.fitness <= population[i].fitness:
                    new_population.append(new_gnome)
                    break
                else:
                    prob = pow(2.7, -1 * ((new_gnome.fitness - population[i].fitness) / temperature))
                    if prob > 0.5:
                        new_population.append(new_gnome)
                        break

        temperature = cooldown(temperature)
        population = new_population

        print("GNOME     FITNESS VALUE")
        for ind in population:
            print(ind.gnome, ind.fitness)

        gen += 1

    best_solution = min(population, key=lambda x: x.fitness)
    print("\nBest solution found:")
    print("Path:", best_solution.gnome)
    print("Fitness value (total distance):", best_solution.fitness)

if __name__ == "__main__":
    TSP()
