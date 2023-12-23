#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <map>

#pragma pack(push, 1)
struct BMPHeader {
    uint16_t signature;
    uint32_t fileSize;
    uint32_t reserved;
    uint32_t dataOffset;
    uint32_t headerSize;
    int32_t width;
    int32_t height;
    uint16_t planes;
    uint16_t bitsPerPixel;
    uint32_t compression;
    uint32_t dataSize;
    int32_t horizontalResolution;
    int32_t verticalResolution;
    uint32_t colors;
    uint32_t importantColors;
};
#pragma pack(pop)

struct HuffmanNode {
    uint8_t data;
    int frequency;
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(uint8_t d, int freq) : data(d), frequency(freq), left(nullptr), right(nullptr) {}
};

struct CompareNodes {
    bool operator()(HuffmanNode* left, HuffmanNode* right) const {
        return left->frequency > right->frequency;
    }
};

BMPHeader readBMPHeader(std::ifstream& file) {
    BMPHeader header;
    file.read(reinterpret_cast<char*>(&header), sizeof(header));
    return header;
}

std::vector<uint8_t> readBMPData(std::ifstream& file, const BMPHeader& header) {
    std::vector<uint8_t> data(header.dataSize);
    file.read(reinterpret_cast<char*>(data.data()), header.dataSize);
     if (file.fail()) {
        std::cerr << "Error reading BMP data." << std::endl;
    } else {
        std::cout << "Successfully read " << file.gcount() << " bytes of BMP data." << std::endl;
    }

    return data;
}

HuffmanNode* buildHuffmanTree(const std::map<uint8_t, int>& frequencies) {
    std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, CompareNodes> priorityQueue;

    for (const auto& pair : frequencies) {
        priorityQueue.push(new HuffmanNode(pair.first, pair.second));
    }

    while (priorityQueue.size() > 1) {
        HuffmanNode* left = priorityQueue.top();
        priorityQueue.pop();

        HuffmanNode* right = priorityQueue.top();
        priorityQueue.pop();

        HuffmanNode* newNode = new HuffmanNode(0, left->frequency + right->frequency);
        newNode->left = left;
        newNode->right = right;

        priorityQueue.push(newNode);
    }

    return priorityQueue.top();
}

void buildHuffmanCodes(HuffmanNode* root, const std::vector<bool>& currentCode, std::map<uint8_t, std::vector<bool>>& huffmanCodes) {
    if (root->left == nullptr && root->right == nullptr) {
        huffmanCodes[root->data] = currentCode;
        return;
    }

    std::vector<bool> leftCode = currentCode;
    leftCode.push_back(false);
    buildHuffmanCodes(root->left, leftCode, huffmanCodes);

    std::vector<bool> rightCode = currentCode;
    rightCode.push_back(true);
    buildHuffmanCodes(root->right, rightCode, huffmanCodes);
}

void writeHuffmanEncodedData(std::ofstream& outputFile, const BMPHeader& bmpHeader, const std::map<uint8_t, std::vector<bool>>& huffmanCodes, const std::vector<uint8_t>& originalData) {
    outputFile.write(reinterpret_cast<const char*>(&bmpHeader), sizeof(bmpHeader));
    for (const auto& code : huffmanCodes) {
        outputFile << static_cast<int>(code.first) << " ";
        for (bool bit : code.second) {
            outputFile << bit; // 写入哈夫曼编码比特流
        }
        outputFile << " "; // 用空格分隔不同的哈夫曼编码
    }
    outputFile << std::endl; // 用换行符标志哈夫曼编码表结束

    std::vector<bool> encodedData;
    for (uint8_t byte : originalData) {
        auto it = huffmanCodes.find(byte);
        if (it != huffmanCodes.end()) {
            encodedData.insert(encodedData.end(), it->second.begin(), it->second.end());
        }
    }

    for (size_t i = 0; i < encodedData.size(); i += 8) {
        uint8_t byte = 0;
        for (size_t j = 0; j < 8 && i + j < encodedData.size(); ++j) {
            if (encodedData[i + j]) {
                byte |= (1 << (7 - j));
            }
        }
        outputFile.put(byte);
    }
}

int main() {
    std::ifstream bmpFile("input.bmp", std::ios::binary);
    if (!bmpFile.is_open()) {
        std::cerr << "Error opening BMP file." << std::endl;
        return 1;
    }

    BMPHeader bmpHeader = readBMPHeader(bmpFile);
    bmpHeader.dataSize = bmpHeader.width * bmpHeader.height * 3;

    std::vector<uint8_t> bmpData = readBMPData(bmpFile, bmpHeader);

    std::map<uint8_t, int> frequencies;
    for (const uint8_t byte : bmpData) {
        frequencies[byte]++;
    }

    HuffmanNode* huffmanTree = buildHuffmanTree(frequencies);

    std::map<uint8_t, std::vector<bool>> huffmanCodes;
    buildHuffmanCodes(huffmanTree, std::vector<bool>(), huffmanCodes);

    for (const auto& pair : huffmanCodes) {
        std::cout << "Symbol: " << static_cast<int>(pair.first) << " Code: ";
        for (bool bit : pair.second) {
            std::cout << bit;
        }
        std::cout << std::endl;
    }

      std::ofstream outputFile("output.huffman", std::ios::binary);
    if (!outputFile.is_open()) {
        std::cerr << "Error opening output file." << std::endl;
        return 1;
    }

    outputFile.write(reinterpret_cast<const char*>(&bmpHeader), sizeof(bmpHeader));

    writeHuffmanEncodedData(outputFile, bmpHeader,huffmanCodes, bmpData);

    outputFile.close();

    return 0;
}