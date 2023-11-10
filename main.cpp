#include <iostream>
#include <iomanip>
#include <vector>
#include <random>

// Function to print the diffusion grid
void printGrid(const std::vector<std::vector<double>>& grid) {
    for (const auto& row : grid) {
        for (double val : row) {
            std::cout << std::setw(6) << val << " ";
        }
        std::cout << std::endl;
    }
}

// Function to simulate diffusion using Markov systems
void simulateDiffusion(int gridSize, int timeSteps, double diffusionRate) {
    // Create a 2D grid for diffusion
    std::vector<std::vector<double>> grid(gridSize, std::vector<double>(gridSize, 0.0));

    // Set the initial concentration in the center of the grid
    int center = gridSize / 2;
    grid[center][center] = 1.0;

    // Define a random number generator for diffusion
    std::random_device rd;
    std::default_random_engine rng(rd());
    std::uniform_real_distribution<double> distribution(0.0, 1.0);

    // Perform diffusion for the given number of time steps
    for (int step = 0; step < timeSteps; ++step) {
        std::vector<std::vector<double>> newGrid(gridSize, std::vector<double>(gridSize, 0.0));

        for (int i = 1; i < gridSize - 1; ++i) {
            for (int j = 1; j < gridSize - 1; ++j) {
                // Calculate the diffusion to the neighbors
                double diffusedAmount = diffusionRate * grid[i][j] / 4.0;

                // Perform diffusion to the neighboring cells
                newGrid[i][j] += grid[i-1][j] + grid[i+1][j] + grid[i][j-1] + grid[i][j+1];
                newGrid[i][j] -= grid[i][j] * 4.0;

                // Update the current cell's concentration
                newGrid[i][j] += grid[i][j] * (1.0 - diffusionRate);

                // Perform random diffusion to the neighbors
                double randomDiffusion = diffusedAmount * distribution(rng);
                newGrid[i-1][j] += randomDiffusion;
                newGrid[i+1][j] += randomDiffusion;
                newGrid[i][j-1] += randomDiffusion;
                newGrid[i][j+1] += randomDiffusion;
            }
        }

        // Update the grid with the new concentrations
        grid = newGrid;
    }

    // Print the final diffusion grid
    printGrid(grid);
}

int main() {
    int gridSize = 10;
    int timeSteps = 100;
    double diffusionRate = 0.2;

    simulateDiffusion(gridSize, timeSteps, diffusionRate);

    return 0;
}
