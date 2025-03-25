#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <string>
#include <bitset>

void printValue(const std::string &text, const std::vector<uint8_t> &value) {
    std::cout << text << ": ";

    for (const auto &byte : value) {
        std::cout << std::bitset<8>(byte) << " ";
    }
    
    std::cout << std::endl;
}

std::vector<uint8_t> convertToBinary(const std::string &plaintext) {
    std::vector<uint8_t> binaryText;
    
    for (char c : plaintext) {
        binaryText.push_back(static_cast<uint8_t>(c));
    }
    
    return binaryText;
}

std::vector<uint8_t> generateRandomKey(size_t length) {
    std::vector<uint8_t> key;
    std::mt19937 rng(std::time(0)); 
    std::uniform_int_distribution<int> dist(0, 255); 
    
    for (size_t i = 0; i < length; ++i) {
        key.push_back(static_cast<uint8_t>(dist(rng)));
    }
    
    return key;
}

std::vector<uint8_t> xorOperation(const std::vector<uint8_t>& input, const std::vector<uint8_t>& key) {
    std::vector<uint8_t> output;
    
    for (size_t i = 0; i < input.size(); ++i) {
        output.push_back(input[i] ^ key[i]); 
    }

    return output;
}

std::string convertToString(const std::vector<uint8_t>& binaryText) {
    std::string text;
    
    for (const auto &byte : binaryText) {
        text += static_cast<char>(byte);
    }

    return text;
}

bool isValidInput(const std::string& input) {
    return !input.empty(); 
}

int main() {
    std::string plaintext;

    while (true) {
        std::cout << "Enter your plaintext (or type 'exit' to quit): ";
        std::getline(std::cin, plaintext);

        if (plaintext == "exit") {
            std::cout << "Exiting program..." << std::endl;
            break;
        }

        if (!isValidInput(plaintext)) {
            std::cout << "Error: Input cannot be empty. Please try again." << std::endl;
            continue;
        }

        // Convert plaintext to binary
        std::vector<uint8_t> binaryText = convertToBinary(plaintext);
        std::vector<uint8_t> key = generateRandomKey(binaryText.size());

        // Print values
        printValue("Plaintext in binary", binaryText);
        printValue("Random key", key);

        // Perform XOR encryption
        std::vector<uint8_t> ciphertext = xorOperation(binaryText, key);
        printValue("Ciphertext in binary", ciphertext);

        // Perform XOR decryption
        std::vector<uint8_t> decryptedPlaintext = xorOperation(ciphertext, key);
        std::string decryptedText = convertToString(decryptedPlaintext);

        // Display decrypted text
        std::cout << "Decrypted text: " << decryptedText << std::endl;
        std::cout << std::endl;
    }

    return 0;
}
