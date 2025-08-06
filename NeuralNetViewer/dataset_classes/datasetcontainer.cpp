
#include "datasetcontainer.h"

// MNIST
// EACH image is 28x28 = 784 pixels, each pixel is an unsigned byte (0-255)
//

namespace {

uint32_t read_be_uint32(QDataStream& stream) {
    quint32 val;
    stream >> val;
    return val;
}

Eigen::MatrixXf load_mnist_images_eigen(const QString& resourcePath) {
    QFile file(resourcePath);
    if (!file.open(QIODevice::ReadOnly))
        throw std::runtime_error("Could not open file: " + resourcePath.toStdString());

    QDataStream stream(&file);
    stream.setByteOrder(QDataStream::BigEndian);

    uint32_t magic = read_be_uint32(stream);
    if (magic == 2049) {
        throw std::runtime_error("Inputted file is a label file, not an image file.");
    } else if (magic == 2051) {
        uint32_t num_images = read_be_uint32(stream);
        uint32_t num_rows   = read_be_uint32(stream);
        uint32_t num_cols   = read_be_uint32(stream);
        uint32_t image_size = num_rows * num_cols;


        QByteArray buffer = file.readAll();
        const auto expected_img_bytes = num_images * image_size;
        if (buffer.size() < static_cast<qint64>(expected_img_bytes))
            throw std::runtime_error("MNIST image file truncated");
        //const uchar* raw = reinterpret_cast<const uchar*>(buffer.constData() + 16); // skip header
        const uchar* raw = reinterpret_cast<const uchar*>(buffer.constData());
        Eigen::MatrixXf images(num_images, image_size);

        for (uint32_t i = 0; i < num_images; ++i) {
            for (uint32_t j = 0; j < image_size; ++j) {
                images(i, j) = static_cast<float>(raw[i * image_size + j]) / 255.0f;
            }
        }

        return images;
    } else {
        throw std::runtime_error("Invalid magic number — not an MNIST image file.");
    }
}

Eigen::VectorXi load_mnist_labels_eigen(const QString& resourcePath) {
    QFile file(resourcePath);
    if (!file.open(QIODevice::ReadOnly))
        throw std::runtime_error("Could not open file: " + resourcePath.toStdString());

    QDataStream stream(&file);
    stream.setByteOrder(QDataStream::BigEndian);

    uint32_t magic = read_be_uint32(stream);
    if (magic == 2051) {
        throw std::runtime_error("Expected label file, got image file.");
    } else if (magic == 2049) {
        uint32_t num_labels = read_be_uint32(stream);

        Eigen::VectorXi labels(num_labels);
        QByteArray buffer = file.readAll();
        if (buffer.size() < static_cast<qint64>(num_labels))
            throw std::runtime_error("MNIST label file truncated");

        const uchar* raw = reinterpret_cast<const uchar*>(buffer.constData()); // skip header

        for (uint32_t i = 0; i < num_labels; ++i) {
            labels(i) = static_cast<int>(raw[i]);
        }

        return labels;
    } else {
        throw std::runtime_error("Invalid magic number — not an MNIST label file.");
    }
}

}
DataSetContainer::DataSetContainer()
{

}

void DataSetContainer::loadMNSITDataSet(){
    try{


    // training_features shape is (60000, 784) .e.g 60k rows, each row has 784 features. Each feature is an unsigned byte (0-255)
    m_training_features = load_mnist_images_eigen(":/datasets/datasets/MNIST/train-images-idx3-ubyte");
    // training labels shape is (60000). e.g. 60k rows, and an integer class label for each image.
    m_training_labels = load_mnist_labels_eigen(":/datasets/datasets/MNIST/train-labels-idx1-ubyte");

    // shape (10000, 784)
    m_testing_features = load_mnist_images_eigen(":/datasets/datasets/MNIST/t10k-images-idx3-ubyte");
    // shape (10000)
    m_testing_labels = load_mnist_labels_eigen(":/datasets/datasets/MNIST/t10k-labels-idx1-ubyte");
    } catch (const std::exception& ex){
    qCritical() << "Error loading dataset:" << ex.what();
    return;
    }
}

