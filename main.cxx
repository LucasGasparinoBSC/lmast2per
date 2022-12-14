/**
 * @file main.cxx
 * @author Lucas Gasparino (lucas.gasparino@bsc.es)
 * @brief Small program to reverse the columns of the *.per.dat generated by pyAlya.
 * @details Since SOD2D requires a *.per file with a master/slave ordering, this program
 * converts the output of pyAlya (slave/master) to the required format. Takes as argument
 * the name of the case file to convert. pyAlya output file must be a *.per.dat file.
 * @version 0.1
 * @date 2022-11-24
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cstdint>

/**
 * @brief Flips the ordering on *.per.dat from S/M to M/S, and stores it in a new file.
 * 
 * @param argc Number of arguments, including the program name.
 * @param argv Array of arguments, including the program name.
 * @return int After execution, returns 0.
 */
int main(int argc, char const *argv[])
{
    // Check number of arguments
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <case name>" << std::endl;
        return -11;
    }

    // Create var with number of periodic nodes
    uint64_t nPer = 0;

    // Create vectors for master and slave nodes
    std::vector<uint64_t> master_nodes;
    std::vector<uint64_t> slave_nodes;

    // Assign argument 1 to the inpFile and out file
    std::string inpFile = argv[1];
    std::string outFile = inpFile;

    // Append .per.dat to the inpFile
    inpFile.append(".per.dat");

    // Append .perto the outFile
    outFile.append(".per");

    // Open the file inpFile
    std::ifstream file(inpFile);

    // If the file is open, read every line
    // Create a vector of strings to store the lines
    std::vector<std::string> lines;
    if (file.is_open())
    {

        // Create a string to store the line
        std::string line;

        // Read the file line by line
        while (std::getline(file, line))
        {
            // Append the line to the vector
            lines.push_back(line);
        }

        // Message at end
        std::cout << "Succesfully read " << lines.size() << " lines from " << inpFile << std::endl;
        nPer = lines.size();

        // Close the file
        file.close();
    }
    else
    {
        // Print error message
        std::cerr << "Error: Could not open " << inpFile << std::endl;

        // Return error code
        return -13;
    }

    // Try to allocate memory for the vectors using nPer
    try
    {
        master_nodes.reserve(nPer);
        slave_nodes.reserve(nPer);
    }
    catch (const std::bad_alloc &e)
    {
        // Print error message
        std::cerr << "Error: Could not allocate memory for vectors" << std::endl;

        // Return error code
        return -14;
    }
    std::cout << "Succesfully allocated " << 2*nPer*sizeof(uint64_t)/1e9 << " GBs for vectors" << std::endl;

    // Convert entries in lines to arrays of ints
    for (uint64_t i = 0; i < nPer; i++)
    {
        // Create a stringstream from the line
        std::stringstream ss(lines[i]);

        // Create a vector of strings to store the entries
        std::vector<std::string> entries;

        // Create a string to store the entry
        std::string entry;

        // Read the line entry by entry
        while (std::getline(ss, entry, ' '))
        {
            // Append the entry to the vector
            entries.push_back(entry);
        }

        // Convert the entries to ints
        master_nodes.push_back(std::stoull(entries[1]));
        slave_nodes.push_back(std::stoull(entries[0]));
    }
    std::cout << "Succesfully converted all lines to vector<uint64_t>!" << std::endl;

    // Open the outFile, and write the vectors to it
    std::ofstream out(outFile);
    if (out.is_open())
    {
        // Write the master and slave nodes on each line
        for (uint64_t i = 0; i < nPer; i++)
        {
            out << master_nodes[i] << " " << slave_nodes[i] << std::endl;
        }

        // Close the file
        out.close();
        std::cout << "Succesfully wrote " << nPer << " lines to " << outFile << std::endl;
    }
    else
    {
        // Print error message
        std::cerr << "Error: Could not open " << outFile << std::endl;

        // Return error code
        return -15;
    }

    // Exit the program normally
    return 0;
}