# Neural Network Viewer & Builder.
**a C++ QT desktop application where you can create your own FNN, tune hyperparameters, train it with live feedback, and test it against a dataset or your own input.**
### Demo Video: [Neural Network Viewer Demo - Youtube](https://www.youtube.com/watch?v=B_80S-gMQDM&t=2s&ab_channel=Graphica3D)

### Features Include:
- 5 Optimisers (SGD, Momentum, RMS Prop, Adam, AdaGrad)
- per layer customization of neurons, dropout, L1 & L2 regularisation, activation and weight init. (currently only supports dense layers.)
- 6 Activation Functions (ReLU, Leaky ReLU, Identity, Sigmoid, Tanh, Softmax)
- 5 Weight initialisation methods (He, Xavier, Normal, Uniform, Zero)
- live training feedback.
- testing against the dataset or your own input. (only has MNIST 28*28 digits currently)


## Installation
# Requirements:
- CMAKE 3.16+
- C++17 (or higher)
- Qt6.x +

# Windows:
1.   git clone https://github.com/Harrby/NeuralNetViewer.git
2.   cd NeuralNetViewer
3.   mkdir build
4.   cd build
5.   cmake .. -DCMAKE_PREFIX_PATH="C:\Qt\6.x\msvc2019_64"      //replace with path to your Qt installation
6.   cmake --build . --config Release

# Linux:
1.   git clone https://github.com/Harrby/NeuralNetViewer.git
2.   cd NeuralNetViewer
3.   mkdir build && cd build
4.   cmake .. -DCMAKE_PREFIX_PATH=/path/to/Qt/6.x/gxx_64      //replace with path to your Qt installation
5.   make -j$(nproc)

(replace /path/to/Qt/6.x/gxx_64 with your local Qt installation path)
