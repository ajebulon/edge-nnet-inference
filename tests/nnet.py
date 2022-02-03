# -*- coding: utf-8 -*-
"""
Created on Thu Feb  3 12:17:50 2022

@author: azebc
"""

import numpy as np
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense

# gate = input("Which gate: ")

gate_list = ["and", "nand", "or", "nor", "xor", "xnor"]
for gate in gate_list:

    if gate.lower() == "and":
        table = np.array([[0, 0], [0, 1], [1, 0], [1, 1]])
        logic = np.array([[0], [0], [0], [1]])
        deep = False
        
    elif gate.lower() == "nand":
        table = np.array([[0, 0], [0, 1], [1, 0], [1, 1]])
        logic = np.array([[1], [1], [1], [0]])
        deep = False
    
    elif gate.lower() == "or":
        table = np.array([[0, 0], [0, 1], [1, 0], [1, 1]])
        logic = np.array([[0], [1], [1], [1]])
        deep = False
    
    elif gate.lower() == "nor":
        table = np.array([[0, 0], [0, 1], [1, 0], [1, 1]])
        logic = np.array([[1], [0], [0], [0]])
        deep = False
    
    elif gate.lower() == "xor":
        table = np.array([[0, 0], [0, 1], [1, 0], [1, 1]])
        logic = np.array([[0], [1], [1], [0]])
        deep = True
    
    elif gate.lower() == "xnor":
        table = np.array([[0, 0], [0, 1], [1, 0], [1, 1]])
        logic = np.array([[1], [0], [0], [1]])
        deep = True
    
    
    # Initialising the ANN
    classifier = Sequential()
    
    # Adding layer
    if deep:
        NEURON = 6
        classifier.add(Dense(units = NEURON, kernel_initializer = 'uniform', activation = 'relu', input_dim=2))
        classifier.add(Dense(units = NEURON, kernel_initializer = 'uniform', activation = 'relu'))
        classifier.add(Dense(units = 1, kernel_initializer = 'uniform', activation = 'sigmoid'))
    else:
        classifier.add(Dense(units = 1, kernel_initializer = 'uniform', activation = 'sigmoid', input_dim=2))
    
    # Compiling the ANN
    EPOCH = 3000
    classifier.compile(loss='binary_crossentropy', metrics=['accuracy'], optimizer='adam')
    classifier.fit(table, logic, epochs=EPOCH, verbose=False)
    
    # Final result
    result = classifier.evaluate(table, logic)
    print("Accuracy: {}".format(result[-1]))
    
    # Save weights to file
    weights = classifier.get_weights()
    weights_fname = 'weights_{}.txt'.format(gate.lower())
    with open(weights_fname, 'w') as f:
        for weight in weights:
            f.write("%s\n" % weight.tolist())
            
    # Save activation to file
    acts = classifier.get_config()['layers']
    acts_fname = 'acts_{}.txt'.format(gate.lower())
    with open(acts_fname, 'w') as f:
        for act in acts:
            f.write("%s\n" % act['config']['activation'])