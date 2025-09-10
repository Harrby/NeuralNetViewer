
#ifndef NERUALNETWORK_H
#define NERUALNETWORK_H

#include "neuralnetoptionsdata.h"
#include "layer.h"
#include "loss.h"
#include "optimiser.h"
#include <QObject>
#include "epochstats.h"
#include "metrics.h"
#include <atomic>
#include <utility>
#include <chrono>
#include "predictionresults.h"
#include "testingbatchresults.h"
#include "samplelogmessagestats.h"
#include <QElapsedTimer>
#include "dropout.h"

class NeuralNetwork : public QObject
{
    Q_OBJECT

public:
    NeuralNetwork(NeuralNetOptionsData& network_parameters, QObject* parent = nullptr);
    void initialise_network();
    void train(const Eigen::MatrixXf& inputs, const Eigen::VectorXi& labels);
    int predict(const Eigen::VectorXf& inputs);
    std::pair<Metrics, Eigen::MatrixXf> forward(const Eigen::MatrixXf& inputs, const Eigen::VectorXi& labels, bool training=false) const;
    void test(const Eigen::MatrixXf& inputs, const Eigen::VectorXi& labels);

    void requestCancel();
    bool isCancelled() const;
    void resetCancel();

private:
    NeuralNetOptionsData& m_network_parameters;
    std::vector<std::unique_ptr<Layer>> m_layers;
    std::vector<std::unique_ptr<ActivationFunction>> m_activation_functions;
    std::vector<std::unique_ptr<Dropout>> m_dropout_layers;
    const LossFunction& m_loss_function;
    std::unique_ptr<Optimiser> m_optimiser;
    std::atomic<bool> m_cancel_requested { false };

    double regularisation_loss(const int batch_size) const;
    void apply_l1_l2_regularisation(const int batch_size);


signals:
    void epochDataChanged(EpochStats);
    void predictionFinished(PredictionResults&); //pass by ref, because emitted in same thread.

    void batchSamplesFinished(TestingBatchResults);



};

#endif // NERUALNETWORK_H
