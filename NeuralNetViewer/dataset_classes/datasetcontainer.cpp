
#include "datasetcontainer.h"

// MNIST
// EACH image is 28x28 = 784 pixels, each pixel is an unsigned byte (0-255)
//

namespace {

uint32_t read_be_uint32(std::ifstream& stream) {
    uint32_t val;
    stream.read(reinterpret_cast<char*>(&val), 4);
    return ((val >> 24) & 0xFF) | ((val >> 8) & 0xFF00) |
           ((val << 8) & 0xFF0000) | ((val << 24) & 0xFF000000);
}

Eigen::MatrixXf load_mnist_images_eigen(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) throw std::runtime_error("Could not open file: " + filename);

    uint32_t magic = read_be_uint32(file);
    if (magic == 2049){
        throw std::runtime_error("Inputted File is a lavel file, not an image file. ");
    } else if(magic == 2051){
        uint32_t num_images = read_be_uint32(file);
        uint32_t num_rows = read_be_uint32(file);
        uint32_t num_cols = read_be_uint32(file);
        uint32_t image_size = num_rows * num_cols;

        Eigen::MatrixXf images(num_images, image_size);

        for (uint32_t i = 0; i < num_images; ++i) {
            for (uint32_t j = 0; j < image_size; ++j) {
                unsigned char pixel = 0;
                file.read(reinterpret_cast<char*>(&pixel), 1);
                images(i, j) = static_cast<float>(pixel) / 255.0f;
            }
        }

        return images; // Each row = one image (flattened)
    } else {
        throw std::runtime_error("Invalid magic number, not an MNIST file.");
    }
}

Eigen::VectorXi load_mnist_labels_eigen(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) throw std::runtime_error("Could not open file: " + filename);

    uint32_t magic = read_be_uint32(file);
    if (magic == 2051){
        throw std::runtime_error("Expected Label file, got image file. ");
    } else if(magic == 2049){
        uint32_t num_labels = read_be_uint32(file);

        Eigen::VectorXi labels(num_labels);

        for (uint32_t i = 0; i < num_labels; ++i) {
            unsigned char label = 0;
            file.read(reinterpret_cast<char*>(&label), 1);
            labels(i) = static_cast<int>(label);
        }

        return labels;
    } else {
        throw std::runtime_error("Invalid magic number, not an MNIST file.");
    }
}

}

DataSetContainer::DataSetContainer()
{

}

void DataSetContainer::loadMNSITDataSet(){

    // training_features shape is (60000, 784) .e.g 60k rows, each row has 784 features. Each feature is an unsigned byte (0-255)
    m_training_features = load_mnist_images_eigen("datasets/datasets/train-images-idx3-ubyte.gz");
    // training labels shape is (60000). e.g. 60k rows, and an integer class label for each image.
    m_training_labels = load_mnist_labels_eigen("datasets/datasets/train-labels-idx1-ubyte.gz");

    // shape (10000, 784)
    m_testing_features = load_mnist_images_eigen("datasets/datasets/t10k-images-idx3-ubyte.gz");
    // shape (10000)
    m_testing_labels = load_mnist_labels_eigen("datasets/datasets/t10k-labels-idx1-ubyte.gz");
}

