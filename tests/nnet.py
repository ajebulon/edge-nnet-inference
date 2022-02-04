# -*- coding: utf-8 -*-
"""
Created on Thu Feb  3 12:17:50 2022

@author: azebc
"""

import numpy as np
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense

# gate = input("Which gate: ")

# gate_list = ["and", "nand", "or", "nor", "xor", "xnor"]
gate_list = ["mix"]
for gate in gate_list:

    if gate.lower() == "and":
        table = np.array([[0, 0], [0, 1], [1, 0], [1, 1]])
        logic = np.array([[0], [0], [0], [1]])
        depth = 1
        
    elif gate.lower() == "nand":
        table = np.array([[0, 0], [0, 1], [1, 0], [1, 1]])
        logic = np.array([[1], [1], [1], [0]])
        depth = 1
    
    elif gate.lower() == "or":
        table = np.array([[0, 0], [0, 1], [1, 0], [1, 1]])
        logic = np.array([[0], [1], [1], [1]])
        depth = 1
    
    elif gate.lower() == "nor":
        table = np.array([[0, 0], [0, 1], [1, 0], [1, 1]])
        logic = np.array([[1], [0], [0], [0]])
        depth = 1
    
    elif gate.lower() == "xor":
        table = np.array([[0, 0], [0, 1], [1, 0], [1, 1]])
        logic = np.array([[0], [1], [1], [0]])
        depth = 2
    
    elif gate.lower() == "xnor":
        table = np.array([[0, 0], [0, 1], [1, 0], [1, 1]])
        logic = np.array([[1], [0], [0], [1]])
        depth = 2
        
    elif gate.lower() == "mix":
        table = np.array([[0, 0, 0], [0, 0, 1], [0, 1, 0], [0, 1, 1], [1, 0, 0], [1, 0, 1], [1, 1, 0], [1, 1, 1], [2, 0, 0], [2, 0, 1], [2, 1, 0], [2, 1, 1], [3, 0, 0], [3, 0, 1], [3, 1, 0], [3, 1, 1], [4, 0, 0], [4, 0, 1], [4, 1, 0], [4, 1, 1], [5, 0, 0], [5, 0, 1], [5, 1, 0], [5, 1, 1]])
        logic = np.array([[0], [0], [0], [1], [1], [1], [1], [0], [0], [1], [1], [1], [1], [0], [0], [0], [0], [1], [1], [0], [1], [0], [0], [1]])
        depth = 3
    
    
    # Initialising the ANN
    classifier = Sequential()
    
    # Adding layer
    if depth == 1:
        classifier.add(Dense(units = 1, kernel_initializer = 'uniform', activation = 'sigmoid', input_dim=2))
    elif depth == 2:
        NEURON = 16
        classifier.add(Dense(units = NEURON, kernel_initializer = 'uniform', activation = 'relu', input_dim=2))
        classifier.add(Dense(units = 1, kernel_initializer = 'uniform', activation = 'sigmoid'))
    elif depth == 3:
        NEURON = 32
        classifier.add(Dense(units = NEURON, kernel_initializer = 'uniform', activation = 'relu', input_dim=3))
        classifier.add(Dense(units = NEURON, kernel_initializer = 'uniform', activation = 'relu'))
        classifier.add(Dense(units = NEURON, kernel_initializer = 'uniform', activation = 'relu'))
        classifier.add(Dense(units = 1, kernel_initializer = 'uniform', activation = 'sigmoid'))        
    
    # Compiling the ANN
    EPOCH = 5000
    classifier.compile(loss='binary_crossentropy', metrics=['accuracy'], optimizer='adam')
    classifier.fit(table, logic, epochs=EPOCH, verbose=False)
    
    # Final result
    result = classifier.evaluate(table, logic)
    print("Accuracy: {}".format(result[-1]))
    
    # Validate dense network 
    layer_list = [act['class_name'] for act in classifier.get_config()['layers']]
    skip_input = 'InputLayer' in layer_list
    if skip_input:
        if not np.all(np.array(layer_list[1::]) == 'Dense'):
            continue
    else:
        if not np.all(np.array(layer_list) == 'Dense'):
            continue
    
    # Save weights to file
    weights = classifier.get_weights()
    weights_fname = 'weights_{}.txt'.format(gate.lower())
    with open(weights_fname, 'w') as f:
        for weight in weights:
            if len(weight.shape) < 2:
                weight = weight.reshape(1, -1)
            f.write("%s\n" % weight.tolist())
            
    # Save activation to file
    acts = classifier.get_config()['layers']
    acts = acts[1::] if skip_input else acts
    acts_fname = 'acts_{}.txt'.format(gate.lower())
    with open(acts_fname, 'w') as f:
        for act in acts:
            f.write("%s\n" % act['config']['activation'])