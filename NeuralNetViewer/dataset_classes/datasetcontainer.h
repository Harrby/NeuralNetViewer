
#ifndef DATASETCONTAINER_H
#define DATASETCONTAINER_H


#include <Eigen/Dense>
#include <fstream>
#include <stdexcept>
#include <cstdint>

class DataSetContainer
{
public:
    DataSetContainer();

    void loadMNSITDataSet();

    Eigen::MatrixXf m_training_features;
    Eigen::MatrixXf m_testing_features;

    Eigen::VectorXi m_training_labels;
    Eigen::VectorXi m_testing_labels;
};

#endif // DATASETCONTAINER_H
