#ifndef MLP_H
#define MLP_H

#include <vector>
#include <string>
#include <memory>

#include "ndarray.h"
#include "util.h"
#include "transfer.h"

#include "linalg1.h"
#include "linalg2.h"

struct Layer {
  const int num_inputs;
  const int num_outputs;
  const TransferFunction transfer_fn;

  NDArray W, b;
  NDArray x, y;
  //NDArray delta;

  Layer(const int num_inputs, const int num_outputs, const TransferFunction transfer_fn)
    : num_inputs(num_inputs)
    , num_outputs(num_outputs)
    , transfer_fn(transfer_fn)
    , W({num_inputs, num_outputs})
    , b({num_outputs})
    , x({num_inputs})
    , y({num_outputs}) {

    fill(x, 0.0);
    fill(y, 0.0);
    normal(b, 0.0, 1.0);
    normal(W, 0.0, 1.0);
  }

  void forward() {
    matmul(y, x, W); // y = x*W + b
    add(y, b); // y += b
    apply<float>(y, [=](float &a) { a = evaluate(transfer_fn, a); });
  }
};

class MultilayerPerceptron
{
  const int num_inputs;
  const int num_outputs;
  const int num_layers;

  std::vector<std::shared_ptr<Layer>> layers;

public:
  MultilayerPerceptron(
    const int num_inputs,
    const int num_outputs,
    const std::vector<int> layer_sizes,
    const std::vector<TransferFunction> transfer_fns
  ) 
    : num_inputs(num_inputs)
    , num_outputs(num_outputs)
    , num_layers(layer_sizes.size())
  {
    check(num_inputs >= 1, "!!!");
    check(num_outputs >= 1, "!!!");
    check(layer_sizes.size() == transfer_fns.size(), "!!!");

    if (num_layers == 1) {
      layers.emplace_back(new Layer(num_inputs, num_outputs, transfer_fns[0]));
    } else if (num_layers > 1) {
      layers.emplace_back(new Layer(num_inputs, layer_sizes[0], transfer_fns[0]));
      for (int l=1; l<num_layers-1; ++l) {
        layers.emplace_back(new Layer(layer_sizes[l-1], layer_sizes[l], transfer_fns[l]));
      }
      layers.emplace_back(new Layer(layer_sizes[num_layers-1], num_outputs, transfer_fns[num_layers-1]));
    }
  }

//  void forward(NDArray x) {
//    // TODO: Copy x to layer[0].x
//    layers[0]->forward();
//    for (int l=1; l<num_layers; ++l) {
//      layers[l]->forward(layers[l-1].y);
//    }
//  }

  std::string describe() const;
};

#endif

